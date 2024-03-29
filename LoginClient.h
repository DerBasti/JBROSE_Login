#pragma once
#include "..\JBROSE_Common\ROSEClient.h"

class LoginClient
{
private:
	std::shared_ptr<ROSEClient> networkClient;
	ROSEThreadedLogger logger;

	__inline std::shared_ptr<ROSEClient> getWrappedNetworkInterface() const {
		return networkClient;
	}
	bool handleEncryptionRequest(const Packet* packet);
	bool handleServerListRequest(const Packet* packet);
	bool handleLoginRequest(const Packet* packet);
	bool handleConnectToCharServer(const Packet* packet);
public:
	LoginClient(std::shared_ptr<ROSEClient>& networkClient);
	virtual ~LoginClient();

	bool handlePacket(const Packet* packet);
};

