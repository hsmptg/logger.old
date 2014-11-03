#include "main.h"
#include <stdio.h>

int tick;
uint32_t timeDif;
uint32_t last;

void initClock() {
	tick = 0;
	timeDif = 0;
}

uint8_t char2dec (char *p) {
	return 10*(p[0]-'0') + (p[1]-'0');
}

void printClock() {
	uint32_t t = (millis() + timeDif) / 1000;
	uint8_t ss = t % 60;
	t = t / 60;
	uint8_t mm = t % 60;
	t = t / 60;
	uint8_t hh = t % 24;

	char str[16];
	sprintf(str, "Clock: %02d:%02d:%02d", hh, mm, ss);
	sendMsg(str);
}

void cmdClock(char *cmd) {
	if (cmd[1] == '\0') {
		// send clock info
		printClock();
	}
	else if (cmd[2] == '\0') {
		// tick on (c1) or off (c0)
		tick = cmd[1]=='1' ? 1 : 0;
		last = millis();
	}
	else {
		// set clock with hh hours, mm minutes and ss seconds
		uint8_t hh = char2dec(cmd+1);
		uint8_t mm = char2dec(cmd+3);
		uint8_t ss = cmd[5]=='\0' ? 0 : char2dec(cmd+5);
		timeDif = ((60L * hh + mm)*60 + ss)*1000 - millis();
	}
}

void procClock() {
	uint32_t t = millis();
	if (tick)
		if (t > last + 1000) {
			last += 1000;
			printClock();
		}
}
