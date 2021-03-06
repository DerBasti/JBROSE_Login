#include "ServerListResponsePacket.h"

ServerListResponsePacket::ServerListResponsePacket() : ResponsePacket(0x704, DEFAULT_SIZE_WITH_EMPTY_STRING) {
	unknown1 = unknown2 = 0;
	channelStatus = 0; //Not busy
}

ServerListResponsePacket::~ServerListResponsePacket() {

}

void ServerListResponsePacket::appendContentToSendable(SendablePacket& sendable) const {
	sendable.addData(requestedServerId);
	sendable.addData(channelAmount);
	sendable.addData(channelId);
	sendable.addData(unknown1);
	sendable.addData(unknown2);
	sendable.addData(channelStatus);
	sendable.addString(channelName.get());
}

void ServerListResponsePacket::setChannelName(const char *name) {
	uint16_t nameLength = static_cast<uint16_t>(name != nullptr ? strlen(name) : 0);
	channelName = std::shared_ptr<char>(new char[nameLength + 1], std::default_delete<char[]>());
	memcpy(channelName.get(), name, nameLength);
	channelName.get()[nameLength] = 0x00; //Null-Terminator des Strings, ansonsten lesen wir immer weiter Mist ein.
}

std::string ServerListResponsePacket::toPrintable() const {
	char buf[0x100] = { 0x00 };
	sprintf_s(buf, "[ServerListPacket - %i]:\n\t* ServerId: %i\n\t* ChannelId: %i\n\t* ChannelName: %s\n\t* ChannelStatus: %i", getLength(), requestedServerId, channelId, channelName.get(), channelStatus);
	return std::string(buf);
}