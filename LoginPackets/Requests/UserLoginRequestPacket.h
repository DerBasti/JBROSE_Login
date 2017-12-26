#pragma once
#include "..\..\Common\Packet.h"

class UserLoginRequestPacket : public Packet {
private:
	std::shared_ptr<char> userName;
	std::shared_ptr<char> hashedPassword;
public:
	UserLoginRequestPacket(const Packet* packet);
	virtual ~UserLoginRequestPacket() {	}

	__inline const char* getUserName() const {
		return userName.get();
	}
	__inline const char* getHashedPassword() const {
		return hashedPassword.get();
	}
};