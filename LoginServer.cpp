#include "LoginServer.h"
#include "LoginPackets\LoginPacketFactory.h"

LoginServer::LoginServer(uint16_t port) : ROSEServer(port) {
	loadEncryption();
	setPacketFactoryCreatorFunction([]() {
		return std::shared_ptr<PacketFactory>(new LoginPacketFactory());
	});
}


LoginServer::~LoginServer()
{
}

void LoginServer::loadEncryption() {
	ENCRYPTION_TABLE = std::shared_ptr<CryptTable>(new LoginCryptTable());
	ENCRYPTION_TABLE->generateCryptTables();
}

void LoginServer::onNewROSEClient(std::shared_ptr<ROSEClient>& roseClient) {
	LoginClient* client = new LoginClient(roseClient);
	clientList.insert(make_pair(roseClient, client));
}

void LoginServer::onROSEClientDisconnecting(std::shared_ptr<ROSEClient>& client) {
	auto it = clientList.find(client);
	if (it != clientList.cend()) {
		LoginClient *loginClient = (*it).second;
		clientList.erase(it);

		delete loginClient;
		loginClient = nullptr;
	}
}

bool LoginServer::onPacketsReady(std::shared_ptr<ROSEClient>& client, std::queue<std::shared_ptr<Packet>>& packetQueue) {
	LoginClient* loginClient = findLoginClientByROSEClient(client);
	bool packetsSuccessfullyHandled = true;
	if (loginClient != nullptr) {
		while (!packetQueue.empty()) {
			std::shared_ptr<Packet> p = packetQueue.front();
			packetsSuccessfullyHandled &= loginClient->handlePacket(p.get());
			packetQueue.pop();
		}
	}
	return loginClient != nullptr && packetsSuccessfullyHandled;
}

LoginClient* LoginServer::findLoginClientByROSEClient(std::shared_ptr<ROSEClient>& parent) {
	LoginClient *result = nullptr;
	auto it = clientList.find(parent);
	if (it != clientList.cend()) {
		result = (*it).second;
	}
	return result;
}