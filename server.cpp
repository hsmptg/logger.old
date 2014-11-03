#include "main.h"

void initServer() {
	Serial.begin(115200);
	sendMsg(VERSION_STR);
}

#define CMD_SIZE 10

char *getCmd(void) {
	int c;
	int static index;
	char static cmd[CMD_SIZE+1];

	if ((c = Serial.read()) != -1) {
		if (index && ((char) c == '\r')) {
			cmd[index] = '\0';
			index = 0;
			return cmd;
		}
		else {
			if (index < CMD_SIZE)
				cmd[index++] = (char) c;
			return 0;
		}
	}
	return 0;
}

void sendMsg(const char *msg) {
	Serial.println(msg);
}
