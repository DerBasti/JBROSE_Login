#include "UserLoginRequestPacket.h"

UserLoginRequestPacket::UserLoginRequestPacket(const Packet* packet) : Packet(packet->getCommandId(), packet->getLength()) {
	hashedPassword = std::shared_ptr<char>(new char[0x21], std::default_delete<char[]>());
	memset(hashedPassword.get(), 0x00, 0x21);
	userName = std::shared_ptr<char>(new char[0x21], std::default_delete<char[]>());
	memset(userName.get(), 0x00, 0x21);

	const char *rawData = packet->getRawData();
	memcpy(hashedPassword.get(), rawData, 0x20);
	memcpy(userName.get(), &rawData[0x20], packet->getLength() - 0x20 - UserLoginRequestPacket::DEFAULT_MINIMUM_SIZE - 1);
}