#include "main.h"
#include <SD.h>
#include <EEPROM.h>
#include <stdio.h>

File dataFile;
uint32_t last_tick;
int sample;

void initLogger() {
	if (!SD.begin(10)) {
	    Serial.println("Card failed, or not present");
	    // don't do anything more:
	    return;
	}
	Serial.println("card initialized.");

	bLog = true;
	digitalWrite(LED, bLog);
	if (bLog)
		startLog();
	else
		stopLog();
}

void cmdAcquire(char *cmd) {
	int N, n, i, v;

	N = cmd[1]-'0';
	for(n=i=v=0; n<N; n++) {
		i += analogRead(4);
	}
//	char fstr[32], str[32];
//	dtostrf((i/N-511)/13.2, 5, 2, fstr);
	char str[32];
	sprintf(str, "%5d,%4d", sample, i/N);
	sendMsg(str);

	if (bLog) {
		if (dataFile) {
			dataFile.println(str);
			if ((sample % 10) == 0)
				dataFile.flush();
		}
		else
			Serial.println("error opening datalog.txt");
		sample++;
	}
}

#define PERIOD 100

void startLog() {
	char filename[16];

	last_tick = millis() - PERIOD;
	sample = 1;

	// set filename
	int nFile = (EEPROM.read(0) << 8) + EEPROM.read(1);
	sprintf(filename, "file%04d.csv", nFile);
	nFile++;
	EEPROM.write(0, nFile >> 8);
	EEPROM.write(1, nFile & 0xFF);

	Serial.println(filename);
	dataFile = SD.open(filename, FILE_WRITE);
	dataFile.println("t(1/10s),I(0..1023)");

}

void tickLog() {
	uint32_t t = millis();
	if (t > last_tick + PERIOD) {
		last_tick += PERIOD;
		cmdAcquire("a4");
	}
}

void stopLog() {
	dataFile.close();
	sample = 0;
}
