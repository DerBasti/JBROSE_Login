#include "ServerListRequestPacket.h"

ServerListRequestPacket::ServerListRequestPacket(const Packet* packet) : Packet(packet->getCommandId(), packet->getLength()) {
	const char* rawData = packet->getRawData();
	requestedServerId = *((const uint32_t*)rawData);
}
