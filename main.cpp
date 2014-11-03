#include "main.h"

void setup() {
	initServer();
	initLedBut();
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
		}
	}
	procBut();
}
