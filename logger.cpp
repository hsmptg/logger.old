#include "main.h"
#include <SD.h>
#include <EEPROM.h>
#include <stdio.h>

File dataFile;
uint32_t last_tick;
char filename[16];

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

void printDouble( double val, byte precision){
	// http://forum.arduino.cc/index.php/topic,44216.0.html#11
 // prints val with number of decimal places determine by precision
 // precision is a number from 0 to 6 indicating the desired decimial places
 // example: printDouble( 3.1415, 2); // prints 3.14 (two decimal places)

 Serial.print (int(val));  //prints the int part
 if( precision > 0) {
   Serial.print("."); // print the decimal point
   unsigned long frac;
   unsigned long mult = 1;
   byte padding = precision -1;
   while(precision--)
      mult *=10;

   if(val >= 0)
     frac = (val - int(val)) * mult;
   else
     frac = (int(val)- val ) * mult;
   unsigned long frac1 = frac;
   while( frac1 /= 10 )
     padding--;
   while(  padding--)
     Serial.print("0");
   Serial.print(frac,DEC) ;
 }
}

void cmdAcquire(char *cmd) {
	int N, n, i, v;
	int static cnt = 0;

	N = cmd[1]-'0';
	for(n=i=v=0; n<N; n++) {
		i += analogRead(4);
		v += analogRead(5);
	}
	char str[32];
//	sprintf(str, "%d: I= %d, V= %d", cnt, i/N, v/N);
	sprintf(str, "%5d: I= %4d (%02.2fA)", cnt/10.0, i/N, (A6-511)*30.0/512);
	sendMsg(str);

	if (bLog) {
		pinMode(2, OUTPUT);
		digitalWrite(2, LOW);
		pinMode(3, OUTPUT);
		digitalWrite(3, LOW);

		digitalWrite(2, HIGH);
		if ((cnt % 10) == 0)
			dataFile = SD.open(filename, FILE_WRITE);
		if (dataFile) {
			digitalWrite(3, HIGH);
			dataFile.println(str);
			digitalWrite(3, LOW);
			if ((cnt % 10) == 9)
				dataFile.close();
			digitalWrite(2, LOW);
		}
		else
			Serial.println("error opening datalog.txt");
		cnt++;
	}
}

void startLog() {

	int nFile = (EEPROM.read(0) << 8) + EEPROM.read(1);
	sprintf(filename, "file%04d.txt", nFile);
	Serial.println(filename);
	nFile++;
	EEPROM.write(0, nFile >> 8);
	EEPROM.write(1, nFile & 0xFF);
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
}
