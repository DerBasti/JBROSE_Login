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
	bool handleServerRequest(const Packet* packet);
	bool handleLoginRequest(const Packet* packet);
public:
	LoginClient(ROSEClient* networkClient);
	~LoginClient();

	bool handlePacket(const Packet* packet);
};

