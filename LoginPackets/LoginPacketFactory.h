#pragma once

#include "..\..\JBROSE_Common\PacketFactory.h"

class LoginPacketFactory : public PacketFactory {
public:
	LoginPacketFactory();
	virtual ~LoginPacketFactory();

	virtual void init();
};