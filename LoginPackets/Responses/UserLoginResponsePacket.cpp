#include "UserLoginResponsePacket.h"

UserLoginResponsePacket::UserLoginResponsePacket() : ResponsePacket(0x708, DEFAULT_SIZE_WITH_EMPTY_STRING) {
	unknown1 = 0;
	unknown2 = 0x0C;
	unknown3 = 0x31;
}

UserLoginResponsePacket::~UserLoginResponsePacket() {

}

void UserLoginResponsePacket::appendContentToSendable(SendablePacket& sendable) const {
	sendable.addData(loginResponseId);
	sendable.addData(unknown1);
	sendable.addData(unknown2);
	sendable.addData(unknown3);
	sendable.addString(serverName.get());
	sendable.addData(serverId);
}

std::string UserLoginResponsePacket::toPrintable() const {
	char buf[0x100] = { 0x00 };
	sprintf_s(buf, "[UserLoginPacket - %i]:\n\t* Login Response: %i\n\t* ServerNumber: %c\n\t* ServerName: %s\n\t* ServerId: %i", getLength(),
		loginResponseId, serverNumberAsCharacter, serverName.get(), serverId);
	return std::string(buf);
}

void UserLoginResponsePacket::setServerName(const char *name) {
	uint16_t nameLen = static_cast<uint16_t>(strlen(name));

	serverName = std::shared_ptr<char>(new char[nameLen + 1], std::default_delete<char[]>());
	memcpy(serverName.get(), name, nameLen);
	serverName.get()[nameLen] = 0x00;
}