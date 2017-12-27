#pragma once
#include "..\..\Common\Packet.h"

class EncryptionResponsePacket : public ResponsePacket {
private:
	uint8_t actionId;
	uint32_t additionalStep;
	const static uint16_t DEFAULT_MINIMUM_SIZE = 11;
protected:
	__inline virtual uint16_t getDefaultLength() const {
		return EncryptionResponsePacket::DEFAULT_MINIMUM_SIZE;
	}
	virtual void appendContentToSendable(SendablePacket& packet) const;
public:
	EncryptionResponsePacket();
	virtual ~EncryptionResponsePacket() {

	}
	__inline void setAdditionalValuePerStep(uint32_t newValue) {
		additionalStep = newValue;
	}

	__inline void setActionId(uint8_t value) {
		actionId = value;
	}
};