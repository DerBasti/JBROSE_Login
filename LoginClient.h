#pragma once
#include "Common\ROSEClient.h"

class LoginClient
{
private:
	ROSEClient* networkClient;

	__inline ROSEClient* getWrappedNetworkInterface() const {
		return networkClient;
	}
	bool handleEncryptionRequest(const Packet* packet);
	bool handleServerListRequest(const Packet* packet);
	bool handleLoginRequest(const Packet* packet);
	bool handleConnectToCharServer(const Packet* packet);
public:
	LoginClient(ROSEClient* networkClient);
	virtual ~LoginClient();

	bool handlePacket(const Packet* packet);
};

