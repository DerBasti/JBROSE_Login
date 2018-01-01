#pragma once
#include "..\..\..\JBROSE_Common\Packet.h"

class UserLoginResponsePacket : public ResponsePacket {
private:
	const static uint16_t DEFAULT_SIZE_WITH_EMPTY_STRING = 17;
	uint8_t loginResponseId;
	uint16_t unknown1;
	uint16_t unknown2;
	uint8_t unknown3;
	uint8_t serverNumberAsCharacter;
	std::shared_ptr<char> serverName;
	uint32_t serverId;
protected:
	virtual void appendContentToSendable(SendablePacket& sendable) const;

	__inline virtual uint16_t getDefaultLength() const {
		return DEFAULT_SIZE_WITH_EMPTY_STRING;
	}
public:
	enum LoginResponse : uint8_t {
		OKAY,
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
	};

	UserLoginResponsePacket();
	virtual ~UserLoginResponsePacket();
	virtual std::string toPrintable() const;

	__inline void setLoginResponse(const LoginResponse& response) {
		loginResponseId = (uint8_t)response;
	}

	__inline void setServerNumber(const uint8_t numberAsCharacter) {
		serverNumberAsCharacter = numberAsCharacter;
	}

	void setServerName(const char *name);

	__inline void setServerId(const uint32_t channel) {
		serverId = channel;
	}
};