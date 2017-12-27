#include "ChannelServerRequestPacket.h"

ChannelServerRequestPacket::ChannelServerRequestPacket(const Packet* packet) : Packet(packet->getCommandId(), packet->getLength()) {
	const char *data = packet->getRawData();

	serverId = *(uint32_t*)data;
	data += sizeof(uint32_t);

	channelId = *data;
}

ChannelServerRequestPacket::~ChannelServerRequestPacket() {

}