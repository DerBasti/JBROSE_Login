#include "ChannelServerResponsePacket.h"

ChannelServerResponsePacket::ChannelServerResponsePacket() : ResponsePacket(0x70A, DEFAULT_SIZE_WITH_EMPTY_STRING) {
}

ChannelServerResponsePacket::~ChannelServerResponsePacket() {

}

void ChannelServerResponsePacket::appendContentToSendable(SendablePacket& sendable) const {

}