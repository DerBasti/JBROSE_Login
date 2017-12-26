#include <iostream>
#include "LoginClient.h"
#include "Common\ROSEMessageHandler.h"
#include "LoginPackets\RequestPackets.h"
#include "LoginPackets\ResponsePackets.h"


LoginClient::LoginClient(ROSEClient* networkClient) {
	this->networkClient = networkClient;
}


LoginClient::~LoginClient()
{
	networkClient = nullptr;
}

bool LoginClient::handlePacket(const Packet* packet) {
	switch (packet->getCommandId()) {
	case 0x703:
		return handleEncryptionRequest(packet);
	case 0x704:
		return handleServerRequest(packet);
	case 0x708:
		return handleLoginRequest(packet);
	}
	std::cout << "Expected to handle 0x" << std::hex << packet->getCommandId() << std::dec << " with length: " << packet->getLength() << "\n";
	return false;
}

bool LoginClient::handleEncryptionRequest(const Packet* packet) {
	EncryptionResponsePacket encryptionPacket;

	unsigned long encryptionValue = rand() | (rand() << 16);
	encryptionPacket.setAdditionalValuePerStep(encryptionValue);
	ROSEMessageHandler* msgHandler = dynamic_cast<ROSEMessageHandler*>(this->getWrappedNetworkInterface()->getMessageHandler());
	msgHandler->setEncryptionValue(encryptionValue);

	return this->getWrappedNetworkInterface()->sendData(encryptionPacket);
}

bool LoginClient::handleServerRequest(const Packet* packet) {
	const ServerListRequestPacket* requestPacket = dynamic_cast<const ServerListRequestPacket*>(packet);
	ServerListResponsePacket serverListPacket;

	serverListPacket.setRequestedServerId(requestPacket->getRequestedServerId());
	serverListPacket.setChannelId(0x01);
	serverListPacket.setChannelStatus(0x00);
	serverListPacket.setChannelName("Testchannel");
	
	return getWrappedNetworkInterface()->sendData(serverListPacket);
}

bool LoginClient::handleLoginRequest(const Packet* packet) {
	const UserLoginRequestPacket *sentData = dynamic_cast<const UserLoginRequestPacket*>(packet);
	
	UserLoginResponsePacket loginPacket;

	loginPacket.setServerNumber('1');
	loginPacket.setServerName("Test Server");
	loginPacket.setLoginResponse(UserLoginResponsePacket::LoginResponse::OKAY);
	loginPacket.setChannelId(0x01);

	return getWrappedNetworkInterface()->sendData(loginPacket);
}