#pragma once
#include "..\..\..\JBROSE_Common\Packet.h"

class EncryptionRequestPacket : public Packet {
public:
	EncryptionRequestPacket(const Packet* p);
	virtual ~EncryptionRequestPacket() { }
};
