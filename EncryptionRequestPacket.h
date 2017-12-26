#pragma once
#include ""..\Common\PacketPacket.h"

class EncryptionRequestPacket : public Packet {
public:
	EncryptionRequestPacket(const Packet* p);
	virtual ~EncryptionRequestPacket() { }
};
