#ifndef LEDBUT_H_
#define LEDBUT_H_

#define LED 9
#define BUT 8

void initLedBut();
void cmdLed(char *cmd);
void cmdBut();
void procBut();

#endif /* LEDBUT_H_ */
