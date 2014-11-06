#ifndef _logger_H_
#define _logger_H_

void initLogger();
void cmdAcquire(char *cmd);
void startLog();
void stopLog();
void tickLog();
void tick1_100(boolean start);

#endif /* _logger_H_ */
