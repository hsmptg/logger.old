#include "main.h"

void setup() {
	initServer();
}

void loop() {
	char *msg;
	if ((msg = getMsg()) != 0) {
		switch(msg[0]) {
			case 'v':
				sendMsg("Arduino v1.0");
				break;
		}
	}
}
