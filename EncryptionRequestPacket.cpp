#include "EncryptionRequestPacket.h"

EncryptionRequestPacket::EncryptionRequestPacket(const Packet* packet) : Packet(packet->getCommandId(), packet->getLength()) {

}