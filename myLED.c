#include "MKL25Z4.h"                    // Device header
#include "myLED.h"

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


// LED starts blinking from PTE20 in line to PTE23	*************UPDATE THIS AFTER SOLDERING THE OTHER OTHER HEADER PINS ONTO KL25Z
static  uint8_t green_led[4] = {PTE20_LEDPin, PTE21_LEDPin, PTE22_LEDPin, PTE23_LEDPin};
static uint8_t red_led[4] = {PTC3_LEDPin, PTC4_LEDPin, PTC5_LEDPin, PTC6_LEDPin};

static uint8_t ledIndex = 0;

static void delay(volatile uint32_t nof);

void initLedPins(void)
{
	// enable clock to the respective ports
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

	// enable GPIO function to the various pins
	PORTE->PCR[PTE20_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[PTE20_LEDPin] |= PORT_PCR_MUX(1);

	PORTE->PCR[PTE21_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[PTE21_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTE->PCR[PTE22_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[PTE22_LEDPin] |= PORT_PCR_MUX(1);

	PORTE->PCR[PTE23_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[PTE23_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[PTC3_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC3_LEDPin] |= PORT_PCR_MUX(1);

	PORTC->PCR[PTC4_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC4_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[PTC5_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC5_LEDPin] |= PORT_PCR_MUX(1);

	PORTC->PCR[PTC6_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC6_LEDPin] |= PORT_PCR_MUX(1);
	
	
	////// add the rest for the other LEDs
	
	// Set Data Direction Registers for various pins
	PTE->PDDR |= (MASK(PTE20_LEDPin) | MASK(PTE21_LEDPin) | MASK(PTE22_LEDPin) | MASK(PTE23_LEDPin));
	PTC->PDDR |= (MASK(PTC3_LEDPin) | MASK(PTC4_LEDPin) | MASK(PTC5_LEDPin) | MASK(PTC6_LEDPin));

	
}

//// Off LED
//void offLED(void) {

//}


//// Off LED
//void onLED(void) {

//}


void offFrontLED() {
	PTE->PCOR |= (MASK(PTE20_LEDPin) | MASK(PTE21_LEDPin) | MASK(PTE22_LEDPin) | MASK(PTE23_LEDPin));

}

void runningGREEN_Moving(uint8_t k) {
	//offFrontLED();
	//if (k < 4) {
			PTE->PSOR |= MASK(green_led[k]);
			delay(running_mode_delay_front);
			PTE->PCOR |= MASK(green_led[k]);
//		} else if (k >= 4) {
////			PTB -> PSOR |= MASK(green_led[k]);
////			osDelay(DELAY_RUN);
////			PTB -> PCOR |= MASK(green_led[k]);
//		}
}

void solidGREEN_Stationery() {
	PTE->PSOR |= MASK(PTE20_LEDPin) | MASK(PTE21_LEDPin) | MASK(PTE22_LEDPin) | MASK(PTE23_LEDPin);
	
}

void flashRED_Moving() {
		PTE->PSOR |= (MASK(PTE20_LEDPin) | MASK(PTE21_LEDPin) | MASK(PTE22_LEDPin) | MASK(PTE23_LEDPin));
		delay(flash_moving_mode_delay_rear);
		PTE->PCOR |= (MASK(PTE20_LEDPin) | MASK(PTE21_LEDPin) | MASK(PTE22_LEDPin) | MASK(PTE23_LEDPin));
	  delay(flash_moving_mode_delay_rear);
}

void flashRED_Staionery() {
		PTE->PSOR |= (MASK(PTE20_LEDPin) | MASK(PTE21_LEDPin) | MASK(PTE22_LEDPin) | MASK(PTE23_LEDPin));
		delay(flash_stationery_mode_delay_rear);
		PTE->PCOR |= (MASK(PTE20_LEDPin) | MASK(PTE21_LEDPin) | MASK(PTE22_LEDPin) | MASK(PTE23_LEDPin));
		delay(flash_stationery_mode_delay_rear);
}

void tFrontLED() {
	for (;;) {
		//if (isMoving()) {
//			ledIndex = (ledIndex + 1)%4;
				  ledIndex = (ledIndex + 1) % 4;
			runningGREEN_Moving(ledIndex);
		//} else {
		//	ledIndex = 0;
		//	solidGREEN_Stationery();
		//}
	}
}

void tRearLED() {
	for (;;) {
		//if (isMoving()) {
			flashRED_Moving();
		//} else {
		//	flashRED_Stationery();
		//}
	}
}





static void delay(volatile uint32_t nof) {
	while(nof != 0) {
		__asm("NOP");
		nof--;
	}
}
