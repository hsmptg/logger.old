#include "main.h"
#include <SD.h>
#include <EEPROM.h>
#include <stdio.h>

File dataFile;
uint32_t last_tick;

void initLogger() {
	if (!SD.begin(10)) {
	    Serial.println("Card failed, or not present");
	    // don't do anything more:
	    return;
	}
	Serial.println("card initialized.");
}

void cmdAcquire(char *cmd) {
	int N, n, i, v;

	N = cmd[1]-'0';
	for(n=i=v=0; n<N; n++) {
		i += analogRead(4);
		v += analogRead(5);
	}
	char str[16];
	sprintf(str, "I= %d, V= %d", i/N, v/N);
	sendMsg(str);

	if (bLog)
		if (dataFile)
			dataFile.println(str);
		else
			Serial.println("error opening datalog.txt");
}

void startLog() {
	char filename[16];
	int nFile = (EEPROM.read(0) << 8) + EEPROM.read(1);
	sprintf(filename, "file%04d.txt", nFile);
	Serial.println(filename);
	dataFile = SD.open(filename, FILE_WRITE);
	nFile++;
	EEPROM.write(0, nFile >> 8);
	EEPROM.write(1, nFile & 0xFF);
}

#define PERIOD 100

void tickLog() {
	uint32_t t = millis();
	if (t > last_tick + PERIOD) {
		last_tick += PERIOD;
		cmdAcquire("a1");
	}
}

void stopLog() {
	dataFile.close();
}
