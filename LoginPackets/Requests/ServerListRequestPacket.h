#pragma once
#include "..\..\Common\Packet.h"

class ServerListRequestPacket : public Packet {
private:
	uint32_t requestedServerId;
public:
	ServerListRequestPacket(const Packet* packet);
	virtual ~ServerListRequestPacket() {}

	__inline uint32_t getRequestedServerId() const {
		return requestedServerId;
	}
};