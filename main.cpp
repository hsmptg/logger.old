#include "main.h"

void setup() {
	initServer();
	initLedBut();
	initClock();
	initLogger();
}

void loop() {
	char *cmd;
	if ((cmd = getCmd()) != 0) {
		switch(cmd[0]) {
			case 'v':
				sendMsg(VERSION_STR);
				break;
			case 'l':
				cmdLed(cmd);
				break;
			case 'b':
				cmdBut();
				break;
			case 'c':
				cmdClock(cmd);
				break;
			case 'a':
				cmdAcquire(cmd);
				break;
		}
	}
	procBut();
	procClock();
	if (bLog) tickLog();
}
