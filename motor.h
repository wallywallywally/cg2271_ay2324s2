#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL

void initMotor(void);

// Percentage is a double ranging from 0 - 1
void leftSide_forwards(double percentage);
void rightSide_forwards(double percentage);
void leftSide_backwards(double percentage);
void rightSide_backwards(double percentage);

void forwards(void);
void backwards(void);
void left(int level);
void left_stationary(void);
void right(int level);
void right_stationary(void);

#endif
