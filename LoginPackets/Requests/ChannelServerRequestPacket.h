#pragma once

#include "..\..\Common\Packet.h"

class ChannelServerRequestPacket : public Packet {
private:
	uint32_t serverId;
	uint8_t channelId;
public:
	ChannelServerRequestPacket(const Packet* packet);
	virtual ~ChannelServerRequestPacket();

	__inline uint32_t getServerId() const {
		return serverId;
	}

	__inline uint8_t getChannelId() const {
		return channelId;
	}
};