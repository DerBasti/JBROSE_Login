#include "LoginServer.h"


LoginServer::LoginServer(uint16_t port) : ROSEServer(port) {
	loadEncryption();
}


LoginServer::~LoginServer()
{
}

void LoginServer::loadEncryption() {
	ENCRYPTION_TABLE = std::shared_ptr<CryptTable>(new LoginCryptTable());
	ENCRYPTION_TABLE->generateCryptTables();
}

void LoginServer::onNewROSEClient(ROSEClient* roseClient) {
	LoginClient* client = new LoginClient(roseClient);
	clientList.insert(make_pair(roseClient, client));
}

bool LoginServer::onPacketsReady(ROSEClient* client, std::queue<std::shared_ptr<Packet>>& packetQueue) {
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

LoginClient* LoginServer::findLoginClientByROSEClient(ROSEClient* parent) {
	LoginClient *result = nullptr;
	auto it = clientList.find(parent);
	if (it != clientList.cend()) {
		result = (*it).second;
	}
	return result;
}