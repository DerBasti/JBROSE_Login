#include "LoginPacketFactory.h"
#include "RequestPackets.h"

LoginPacketFactory::LoginPacketFactory() {
	PacketFactory::addCommand<EncryptionRequestPacket>(0x703);
	PacketFactory::addCommand<ServerListRequestPacket>(0x704);
	PacketFactory::addCommand<UserLoginRequestPacket>(0x708);
	PacketFactory::addCommand<ChannelServerRequestPacket>(0x70A);
}

LoginPacketFactory::~LoginPacketFactory() {

}