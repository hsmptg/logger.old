#include "main.h"

int but;

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

void procBut() {
	int b = digitalRead(BUT);
	if (b != but) {
		but = b;
		cmdBut();
	}
}
