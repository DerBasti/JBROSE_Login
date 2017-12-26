#include "LoginServer.h"

int main() {
	LoginServer ns(29000);
	std::cout << "Starting to accept clients...\n";
	ns.startAcceptingClients();
	while (true) {
		Sleep(1);
	}
	return 0;
}