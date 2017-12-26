#pragma once

#define LOGINSERVER_CRYPTTABLE_START_VALUE 0x0042D266
#define CRYPTTABLE_START_VALUE_DEFAULT 0x87654321	

class CryptTable {
protected:
	unsigned int** tables;
	uint16_t* additionalTables;

	unsigned int startValue;

	virtual void freeCryptTables();
public:
	CryptTable() {
	}
	virtual ~CryptTable() {
		freeCryptTables();
	}
	virtual void generateCryptTables();

	unsigned int **getTables() const {
		return tables;
	}
	uint16_t *getAdditionalTables() const {
		return additionalTables;
	}
	unsigned int getStartValue() const {
		return startValue;
	}
};

class LoginCryptTable : public CryptTable {
public:
	LoginCryptTable() {
	}
	virtual ~LoginCryptTable() {
	}
	virtual void generateCryptTables();
};

struct CryptStatus {
	unsigned int currentValue;
	unsigned int additionalValuePerStep;
};


class EncryptionHandler
{
private:
	CryptStatus *cryptStatus;
public:
	EncryptionHandler();
	~EncryptionHandler();

	__inline void setEncryptionValue(unsigned long encryptionValue) {
		cryptStatus->additionalValuePerStep = encryptionValue;
	}

	uint16_t decryptHeader(unsigned char *Buffer);
	bool decryptBuffer(unsigned char *Buffer);
	void encryptBuffer(unsigned char *Buffer);
};