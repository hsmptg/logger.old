#include "main.h"
#include <SD.h>
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

	dataFile = SD.open("mydata.txt", FILE_WRITE);
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
	last_tick = millis();

	char filename[16];
	sprintf(filename, "file%03d.txt", last_tick % 1000);
	dataFile = SD.open(filename, FILE_WRITE);
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
