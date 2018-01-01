#pragma once
#include "..\..\..\JBROSE_Common\Packet.h"

class ServerListResponsePacket : public ResponsePacket {
private:
	const static uint16_t DEFAULT_SIZE_WITH_EMPTY_STRING = 16;
	uint32_t requestedServerId;
	uint8_t channelAmount;
	uint8_t channelId;
	uint8_t unknown1;
	uint8_t unknown2;
	uint16_t channelStatus;
	std::shared_ptr<char> channelName;

protected:
	virtual uint16_t getDefaultLength() const {
		return DEFAULT_SIZE_WITH_EMPTY_STRING;
	}
	virtual void appendContentToSendable(SendablePacket& sendable) const;
public:
	ServerListResponsePacket();
	virtual ~ServerListResponsePacket();

	void setChannelName(const char *name);
	virtual std::string toPrintable() const;

	__inline uint32_t getRequestedServerId() const {
		return requestedServerId;
	}

	__inline void setRequestedServerId(const uint32_t serverId) {
		requestedServerId = serverId;
	}
	__inline void setChannelAmount(const uint8_t amountOfChannels) {
		channelAmount = amountOfChannels;
	}
	__inline void setChannelId(const uint8_t channel) {
		channelId = channel;
	}

	__inline void setChannelStatus(const uint16_t status) {
		channelStatus = status;
	}
};