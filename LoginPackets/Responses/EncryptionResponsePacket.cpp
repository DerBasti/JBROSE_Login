#include "EncryptionResponsePacket.h"

EncryptionResponsePacket::EncryptionResponsePacket() : ResponsePacket(0x7FF, DEFAULT_MINIMUM_SIZE) {
	actionId = 0x02;
}

void EncryptionResponsePacket::appendContentToSendable(SendablePacket& packet) const {
	packet.addData(actionId);
	packet.addData(additionalStep);
}