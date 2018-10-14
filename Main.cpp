#include "LoginServer.h"

int main() {
	LoginServer ns(29000);
	ns.startAcceptingClients();
	while (true) {
		Sleep(1);
	}
	return 0;
}