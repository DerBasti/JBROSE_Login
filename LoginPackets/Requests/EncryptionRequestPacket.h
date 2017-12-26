#pragma once
#include "..\..\Common\Packet.h"

class EncryptionRequestPacket : public Packet {
public:
	EncryptionRequestPacket(const Packet* p);
	virtual ~EncryptionRequestPacket() { }
};
