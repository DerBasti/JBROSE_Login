#include "ChannelServerRequestPacket.h"

ChannelServerRequestPacket::ChannelServerRequestPacket(const Packet* packet) {
	const char *data = packet->getRawData();

	serverId = *(uint32_t*)data;
	data += 4;

	channelId = *data;
}

ChannelServerRequestPacket::~ChannelServerRequestPacket() {

}