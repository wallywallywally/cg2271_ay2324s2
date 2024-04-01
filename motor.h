#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL

void initMotor(void);

// Percentage is a double ranging from 0 - 1
void leftSide_forwards(double percentage);
void rightSide_forwards(double percentage);
void leftSide_backwards(double percentage);
void rightSide_backwards(double percentage);

void stop(void);
void forwards(void);
void backwards(void);
void left_stationary(void);
void right_stationary(void);

void left_diag(void);
void right_diag(void);



#endif
