#include "ROSEClient.h"
#include "ROSEMessageHandler.h"
#include <iostream>

ROSEClient::ROSEClient(NetworkClient* networkInterface) {
	this->networkInterface = networkInterface;
	messageHandlerForIncomingData = std::unique_ptr<NetworkMessageHandler>(new ROSEMessageHandler());
}


ROSEClient::~ROSEClient()
{
	networkInterface = nullptr;
}

bool ROSEClient::handleIncomingDataFragment(const NetworkMessageFragment& data) {
	std::cout << "Incoming data of size: " << data.getLength() << "\n";
	messageHandlerForIncomingData->accept(data);
	if (messageHandlerForIncomingData->isHandlingFinished()) {
		std::cout << "Handling is finished. Creating packet from data...\n";
		ROSEMessageHandler *roseMessageHandler = dynamic_cast<ROSEMessageHandler*>(messageHandlerForIncomingData.get());
		std::shared_ptr<Packet> packet = roseMessageHandler->createPacketFromReceivedData();
		if (!packet) {
			std::cout << "Packet creation failed!\n";
			return false;
		}
		threadSafeAppendingOfPacketToQueue(packet);
		resetToDefaultState();
	}
	return true;
}

void ROSEClient::resetToDefaultState() {
	std::cout << "Resetting to default state...\n";
	ROSEMessageHandler *roseMessageHandler = dynamic_cast<ROSEMessageHandler*>(messageHandlerForIncomingData.get());
	roseMessageHandler->reset();
	getNetworkInterface()->setMaxAllowedBytesToReceive(roseMessageHandler->getExpectedAmountOfBytes());
}

std::queue<std::shared_ptr<Packet>> ROSEClient::getQueuedPackets() {
	std::queue<std::shared_ptr<Packet>> resultQueue;
	std::lock_guard<std::mutex> mutexLock(packetQueueMutex);
	resultQueue.swap(packetQueue);
	return resultQueue;
}

bool ROSEClient::sendData(const ResponsePacket& packet) {
	std::cout << "Sending packet " << packet.toPrintable().c_str() << "\n";
	std::shared_ptr<unsigned char> packetData = packet.toSendable();
	unsigned char *packetAsPointer = packetData.get();

	unsigned long actualLength = packet.getLength();

	EncryptionHandler encrypter;
	encrypter.encryptBuffer(packetAsPointer);

	const char* encryptedPacket = (const char*)packetAsPointer;
	bool successfullySent = this->getNetworkInterface()->send(encryptedPacket, actualLength);
	return successfullySent;
}
