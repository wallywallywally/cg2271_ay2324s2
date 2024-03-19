#ifndef LED_CONTROL
#define LED_CONTROL

#include "MKL25Z4.h"                    // Device header
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

//green
#define PTE2_LEDPin 2
#define PTE3_LEDPin 3
#define PTE4_LEDPin 4
#define PTE5_LEDPin 5
#define PTB8_LEDPin 8
#define PTB9_LEDPin 9
#define PTB10_LEDPin 10
#define PTB11_LEDPin 11 

//red
//#define PTC4_LEDPin 4
//#define PTC5_LEDPin 5
//#define PTC6_LEDPin 6
#define PTC7_LEDPin 7
//#define PTC10_LEDPin 10
//#define PTC11_LEDPin 11
//#define PTC12_LEDPin 12
//#define PTC13_LEDPin 13 

#define MASK(x) (1 << (x))

#define running_mode_delay_front 100
#define flash_moving_mode_delay_rear 500
#define flash_stationery_mode_delay_rear 250


void initLedPins(void);
void offFrontLED(void);
void offRearLED(void);
void runningGREEN_Moving(uint8_t k);
void solidGREEN_Stationery(void);
void flashRED_Moving(void);
void flashRED_Staionery(void);
void tFrontLED(void);
void tRearLED(void);


#endif