#include "main.h"

void setup() {
	initServer();
}

void loop() {
	char *cmd;
	if ((cmd = getCmd()) != 0) {
		switch(cmd[0]) {
			case 'v':
				sendMsg(VERSION_STR);
				break;
		}
	}
}
