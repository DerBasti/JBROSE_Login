#include <iostream>
#include "LoginClient.h"
#include "..\JBROSE_Common\EncryptionHandler.h"
#include "..\JBROSE_Common\ROSEMessageHandler.h"
#include "LoginPackets\RequestPackets.h"
#include "LoginPackets\ResponsePackets.h"


LoginClient::LoginClient(std::shared_ptr<ROSEClient>& networkClient) {
	this->networkClient = networkClient;
}


LoginClient::~LoginClient()
{
}

bool LoginClient::handlePacket(const Packet* packet) {
	switch (packet->getCommandId()) {
		case 0x703:
			return handleEncryptionRequest(packet);
		case 0x704:
			return handleServerListRequest(packet);
		case 0x708:
			return handleLoginRequest(packet);
		case 0x70A:
			return handleConnectToCharServer(packet);
	}
	logger.logDebug("Expected to handle 0x", packet->getCommandIdAsHex().get(), " with length: ", packet->getLength());
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

bool LoginClient::handleServerListRequest(const Packet* packet) {
	const ServerListRequestPacket* requestPacket = dynamic_cast<const ServerListRequestPacket*>(packet);
	ServerListResponsePacket serverListPacket;

	serverListPacket.setRequestedServerId(requestPacket->getRequestedServerId());
	serverListPacket.setChannelAmount(0x01);
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
	loginPacket.setServerId(0x01);

	return getWrappedNetworkInterface()->sendData(loginPacket);
}

bool LoginClient::handleConnectToCharServer(const Packet* packet) {
	const ChannelServerRequestPacket* requetsPacket = dynamic_cast<const ChannelServerRequestPacket*>(packet);
	ChannelServerResponsePacket response;

	response.setChannelIp("127.0.0.1");
	response.setChannelStatus(0x00);
	response.setEncryptionValue(CryptTable::DEFAULT_CRYPTTABLE_START_VALUE);
	response.setPort(29100);
	response.setUserAccountId(0x01);

	logger.logTrace(response.toPrintable().c_str());
	
	return getWrappedNetworkInterface()->sendData(response);
}