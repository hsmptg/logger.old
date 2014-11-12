// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _main_H_
#define _main_H_

#include "Arduino.h"

//add your includes for the project here
#include "server.h"
#include "ledbut.h"
#include "clock.h"
#include "logger.h"
extern boolean bLog;

//end of add your includes here

#ifdef __cplusplus
extern "C" {
#endif

void loop();
void setup();

#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project here
#define VERSION_STR "v1.1 Logger"
extern boolean bLog;

//Do not add code below this line

#endif /* _main_H_ */


