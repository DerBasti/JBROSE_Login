#pragma once
#include "..\JBROSE_Common\ROSEServer.h"
#include "LoginClient.h"
class LoginServer : public ROSEServer
{
private:
	std::unordered_map<ROSEClient*, LoginClient*> clientList;
	LoginClient* findLoginClientByROSEClient(ROSEClient* parent);
public:
	LoginServer(uint16_t port);
	virtual ~LoginServer();

	virtual void loadEncryption();
	virtual bool onPacketsReady(ROSEClient* client, std::queue<std::shared_ptr<Packet>>& packetQueue);
	virtual void onNewROSEClient(ROSEClient* roseClient);
	virtual void onROSEClientDisconnecting(ROSEClient* client);

};

