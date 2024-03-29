#pragma once
#include "..\..\..\JBROSE_Common\Packet.h"

class ChannelServerResponsePacket : public ResponsePacket {
private:
	const static uint16_t DEFAULT_SIZE_WITH_EMPTY_STRING = 17;
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

	virtual std::string toPrintable() const;

	__inline uint8_t getChannelStatus() const {
		return channelStatus;
	}
	__inline void setChannelStatus(const uint8_t status) {
		channelStatus = status;
	}
	__inline uint32_t getUserAccountId() const {
		return userAccountId;
	}
	__inline void setUserAccountId(const uint32_t accId) {
		userAccountId = accId;
	}
	__inline void setEncryptionValue(const uint32_t encryption) {
		encryptionValue = encryption;
	}
	__inline std::shared_ptr<char> getChannelIp() const {
		return channelIpAsString;
	}
	__inline void setChannelIp(const char* ip) {
		channelIpAsString = std::shared_ptr<char>(new char[0x10], std::default_delete<char[]>());
		size_t length = strlen(ip);
		memcpy(channelIpAsString.get(), ip, length);
		channelIpAsString.get()[length] = 0x00;
	}
	__inline uint16_t getPort() const {
		return port;
	}
	__inline void setPort(const uint16_t port) {
		this->port = port;
	}
};