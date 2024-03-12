#define MASK(x) (1 << (x))

#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL

void initMotor(void);

void forwards(void);
void backwards(void);
void left(int deg);
void left_stationary(void);
void right(void);
void right_stationary(void);

#endif
