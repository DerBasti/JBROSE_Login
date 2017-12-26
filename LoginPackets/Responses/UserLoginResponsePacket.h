#pragma once
#include "..\..\Common\Packet.h"

class UserLoginResponsePacket : public ResponsePacket {
private:
	const static uint16_t DEFAULT_SIZE_WITH_EMPTY_STRING = 17;
	uint16_t unknown;
	uint16_t loginResponseId;
	uint8_t serverNumberAsCharacter;
	std::shared_ptr<char> serverName;
	uint32_t channelId;
protected:
	virtual void appendContentToSendable(SendablePacket& sendable) const;

	__inline virtual uint16_t getDefaultLength() const {
		return DEFAULT_SIZE_WITH_EMPTY_STRING;
	}
public:
	enum LoginResponse : uint8_t {
		MAINTENANCE,
		GENERAL_ERROR,
		ACCOUNT_DOES_NOT_EXIST,
		INCORRECT_PASSWORD,
		ACCOUNT_ALREADY_LOGGED_IN,
		ACCOUNT_BANNED,
		NO_MORE_GAMETIME,
		SERVER_UNREACHABLE,
		ACCOUNT_UNVERIFIED,
		LOGIN_FAILED,
		IP_CAPACITY_FULL,
		LOGIN_FAILED_OTHER,
		OKAY
	};

	UserLoginResponsePacket();
	virtual ~UserLoginResponsePacket();
	virtual std::string toPrintable() const;

	__inline void setLoginResponse(const LoginResponse& response) {
		loginResponseId = (uint16_t)response;
	}
	__inline void setServerNumber(const uint8_t numberAsCharacter) {
		serverNumberAsCharacter = numberAsCharacter;
	}

	void setServerName(const char *name);

	__inline void setChannelId(const uint32_t channel) {
		channelId = channel;
	}
};