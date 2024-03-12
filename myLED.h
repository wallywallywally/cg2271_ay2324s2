#include "MKL25Z4.h"                    // Device header
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"


#define PTE20_LEDPin 20
#define PTE21_LEDPin 21
#define PTE22_LEDPin 22
#define PTE23_LEDPin 23

#define PTC3_LEDPin 3
#define PTC4_LEDPin 4
#define PTC5_LEDPin 5
#define PTC6_LEDPin 6 

#define MASK(x) (1 << (x))

#define running_mode_delay_front 480000
#define flash_moving_mode_delay_rear 4800000
#define flash_stationery_mode_delay_rear 250


void initLedPins(void);
void offFrontLED(void);
void runningGREEN_Moving(uint8_t k);
void solidGREEN_Stationery(void);
void flashRED_Moving(void);
void flashRED_Staionery(void);
void tFrontLED(void);
void tRearLED(void);
