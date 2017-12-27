#pragma once
#include "..\..\Common\Packet.h"

class ChannelServerResponsePacket : public ResponsePacket {
private:
	const static uint16_t DEFAULT_SIZE_WITH_EMPTY_STRING = 16;
	uint8_t channelStatus;
	uint32_t userAccountId;
	uint32_t encryptionValue;
	std::shared_ptr<char> channelIpAsString;
	uint16_t port;
protected:
	virtual void appendContentToSendable(SendablePacket& sendable) const;

	__inline virtual uint16_t getDefaultLength() const {
		return DEFAULT_SIZE_WITH_EMPTY_STRING;
	}
public:
	ChannelServerResponsePacket();
	virtual ~ChannelServerResponsePacket();

	void setChannelStatus(const uint8_t status) {
		channelStatus = status;
	}
};