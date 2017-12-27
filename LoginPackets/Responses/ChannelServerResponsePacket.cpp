#include "ChannelServerResponsePacket.h"

ChannelServerResponsePacket::ChannelServerResponsePacket() : ResponsePacket(0x70A, DEFAULT_SIZE_WITH_EMPTY_STRING) {
}

ChannelServerResponsePacket::~ChannelServerResponsePacket() {

}

std::string ChannelServerResponsePacket::toPrintable() const {
	char buffer[0x200] = { 0x00 };
	sprintf_s(buffer, "[ChannelServerResponse - %i]:\n\t* ChannelStatus: %i\n\t* UserAccountID: %i\n\t* ChannelIP: %s\n\t* Port: %i",
		getLength(), channelStatus, userAccountId, channelIpAsString.get(), port);
	return std::string(buffer);
}

void ChannelServerResponsePacket::appendContentToSendable(SendablePacket& sendable) const {
	sendable.addData(channelStatus);
	sendable.addData(userAccountId);
	sendable.addData(encryptionValue);
	sendable.addString(channelIpAsString.get());
	sendable.addData(port);
}