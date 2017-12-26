#include "UserLoginResponsePacket.h"

UserLoginResponsePacket::UserLoginResponsePacket() : ResponsePacket(0x708, DEFAULT_SIZE_WITH_EMPTY_STRING) {
	unknown = 0;
}

UserLoginResponsePacket::~UserLoginResponsePacket() {

}

void UserLoginResponsePacket::appendContentToSendable(SendablePacket& sendable) const {
	sendable.addData(unknown);
	sendable.addData<uint8_t>(0x00);
	sendable.addData(loginResponseId);
	sendable.addData(serverNumberAsCharacter);
	sendable.addString(serverName.get());
	sendable.addData(channelId);
}

std::string UserLoginResponsePacket::toPrintable() const {
	char buf[0x100] = { 0x00 };
	sprintf_s(buf, "[UserLoginPacket - %i]:\n\t* Login Response: %i\n\t* ServerNumber: %c\n\t* ServerName: %s\n\t* ChannelId: %i", getLength(),
		loginResponseId, serverNumberAsCharacter, serverName.get(), channelId);
	return std::string(buf);
}

void UserLoginResponsePacket::setServerName(const char *name) {
	uint16_t nameLen = static_cast<uint16_t>(strlen(name));

	serverName = std::shared_ptr<char>(new char[nameLen + 1], std::default_delete<char[]>());
	memcpy(serverName.get(), name, nameLen);
	serverName.get()[nameLen] = 0x00;

	setLength(getDefaultLength() + nameLen);
}