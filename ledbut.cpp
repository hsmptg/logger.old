#include "main.h"

int but;
boolean bLog;

void initLedBut() {
	pinMode(BUT, INPUT);
	digitalWrite(BUT, HIGH);
	but = digitalRead(BUT);

	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
}

void cmdLed(char *cmd) {
	if (cmd[1] == '1')
		digitalWrite(LED, HIGH);
	else
		digitalWrite(LED, LOW);
}

void cmdBut() {
	if (!but)
		sendMsg("b1");
	else
		sendMsg("b0");
}

// http://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files-in-c
void procBut() {
	int b = digitalRead(BUT);
	if (b != but) {
		if (!b) {
			bLog = not bLog;
			digitalWrite(LED, bLog);
			if (bLog)
				startLog();
			else
				stopLog();
		}
		but = b;
//		cmdBut();
	}
}
