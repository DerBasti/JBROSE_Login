#include "EncryptionResponsePacket.h"

EncryptionResponsePacket::EncryptionResponsePacket() : ResponsePacket(0x7FF, 11) {
	actionId = 0x02;
}

void EncryptionResponsePacket::appendContentToSendable(SendablePacket& packet) const {
	packet.addData(actionId);
	packet.addData(additionalStep);
}