#pragma once
#include "..\JBROSE_Common\ROSEServer.h"
#include "LoginClient.h"
class LoginServer : public ROSEServer
{
private:
	std::unordered_map<std::shared_ptr<ROSEClient>, LoginClient*> clientList;
	LoginClient* findLoginClientByROSEClient(std::shared_ptr<ROSEClient>& parent);
public:
	LoginServer(uint16_t port);
	virtual ~LoginServer();

	virtual void loadEncryption();
	virtual bool onPacketsReady(std::shared_ptr<ROSEClient>& client, std::queue<std::shared_ptr<Packet>>& packetQueue);
	virtual void onNewROSEClient(std::shared_ptr<ROSEClient>& roseClient);
	virtual void onROSEClientDisconnecting(std::shared_ptr<ROSEClient>& client);

};

