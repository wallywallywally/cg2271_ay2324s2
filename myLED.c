#include "MKL25Z4.h"                    // Device header
#include "myLED.h"





// LED starts blinking from PTE20 in line to PTE23	*************UPDATE THIS AFTER SOLDERING THE OTHER OTHER HEADER PINS ONTO KL25Z
static  uint8_t green_led[8] = {PTE2_LEDPin, PTE3_LEDPin, PTE4_LEDPin, PTE5_LEDPin, PTB8_LEDPin, PTB9_LEDPin, PTB10_LEDPin, PTB11_LEDPin};
static uint8_t red_led[8] = {PTC4_LEDPin, PTC5_LEDPin, PTC6_LEDPin, PTC7_LEDPin, PTC10_LEDPin, PTC11_LEDPin, PTC12_LEDPin, PTC13_LEDPin};

static uint8_t ledIndex = 0;

static void delay(volatile uint32_t nof);

void initLedPins(void)
{
	// enable clock to the respective ports
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

	// enable GPIO function to the various pins
	PORTE->PCR[PTE2_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[PTE2_LEDPin] |= PORT_PCR_MUX(1);

	PORTE->PCR[PTE3_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[PTE3_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTE->PCR[PTE4_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[PTE4_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTE->PCR[PTE5_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[PTE5_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[PTB8_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB8_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[PTB9_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB9_LEDPin] |= PORT_PCR_MUX(1);

	PORTB->PCR[PTB10_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB10_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[PTB11_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB11_LEDPin] |= PORT_PCR_MUX(1);

	
	
	
	
	PORTC->PCR[PTC4_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC4_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[PTC5_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC5_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[PTC6_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC6_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[PTC7_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC7_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[PTC10_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC10_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[PTC11_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC11_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[PTC12_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC12_LEDPin] |= PORT_PCR_MUX(1);
	
	PORTC->PCR[PTC12_LEDPin] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[PTC13_LEDPin] |= PORT_PCR_MUX(1);
	
	
	
	////// add the rest for the other LEDs
	
	// Set Data Direction Registers for various pins
	PTE->PDDR |= (MASK(PTE2_LEDPin) | MASK(PTE3_LEDPin) | MASK(PTE4_LEDPin) | MASK(PTE5_LEDPin));
	PTC->PDDR |= (MASK(PTC4_LEDPin) | MASK(PTC5_LEDPin) | MASK(PTC6_LEDPin) | MASK(PTC7_LEDPin) | MASK(PTC10_LEDPin) | MASK(PTC11_LEDPin) | MASK(PTC12_LEDPin) | MASK(PTC13_LEDPin));
	PTB->PDDR |= (MASK(PTB8_LEDPin) | MASK(PTB9_LEDPin) | MASK(PTB10_LEDPin) | MASK(PTB11_LEDPin));
	
}

//// Off LED
//void offLED(void) {

//}


//// Off LED
//void onLED(void) {

//}


void offFrontLED() {
	PTE->PCOR |= (MASK(PTE2_LEDPin) | MASK(PTE3_LEDPin) | MASK(PTE4_LEDPin) | MASK(PTE5_LEDPin));
	PTB->PCOR |= (MASK(PTB8_LEDPin) | MASK(PTB9_LEDPin) | MASK(PTB10_LEDPin) | MASK(PTB11_LEDPin));
}

void offRearLED() {
	PTC->PCOR |= (MASK(PTC4_LEDPin) | MASK(PTC5_LEDPin) | MASK(PTC6_LEDPin) | MASK(PTC7_LEDPin) | MASK(PTC10_LEDPin) | MASK(PTC11_LEDPin) | MASK(PTC12_LEDPin) | MASK(PTC13_LEDPin));
}

void runningGREEN_Moving(uint8_t k) {	
	offFrontLED();
	if (k < 4) {
		PTE->PSOR |= MASK(green_led[k]);
		delay(running_mode_delay_front);
		PTE->PCOR |= MASK(green_led[k]);
	} else {
		PTB->PSOR |= MASK(green_led[k]);
		delay(running_mode_delay_front);
		PTB->PCOR |= MASK(green_led[k]);
	}
}

void solidGREEN_Stationery() {
	PTE->PSOR |= (MASK(PTE2_LEDPin) | MASK(PTE3_LEDPin) | MASK(PTE4_LEDPin) | MASK(PTE5_LEDPin));
	PTB->PSOR |= (MASK(PTB8_LEDPin) | MASK(PTB9_LEDPin) | MASK(PTB10_LEDPin) | MASK(PTB11_LEDPin));
}

void flashRED_Moving() {
		PTE->PSOR |= (MASK(PTC4_LEDPin) | MASK(PTC5_LEDPin) | MASK(PTC6_LEDPin) | MASK(PTC7_LEDPin) | MASK(PTC10_LEDPin) | MASK(PTC11_LEDPin) | MASK(PTC12_LEDPin) | MASK(PTC13_LEDPin));
		delay(flash_moving_mode_delay_rear);
		PTE->PCOR |= (MASK(PTC4_LEDPin) | MASK(PTC5_LEDPin) | MASK(PTC6_LEDPin) | MASK(PTC7_LEDPin) | MASK(PTC10_LEDPin) | MASK(PTC11_LEDPin) | MASK(PTC12_LEDPin) | MASK(PTC13_LEDPin));
	  delay(flash_moving_mode_delay_rear);
}

void flashRED_Staionery() {
		PTE->PSOR |= (MASK(PTC4_LEDPin) | MASK(PTC5_LEDPin) | MASK(PTC6_LEDPin) | MASK(PTC7_LEDPin) | MASK(PTC10_LEDPin) | MASK(PTC11_LEDPin) | MASK(PTC12_LEDPin) | MASK(PTC13_LEDPin));
		delay(flash_stationery_mode_delay_rear);
		PTE->PCOR |= (MASK(PTC4_LEDPin) | MASK(PTC5_LEDPin) | MASK(PTC6_LEDPin) | MASK(PTC7_LEDPin) | MASK(PTC10_LEDPin) | MASK(PTC11_LEDPin) | MASK(PTC12_LEDPin) | MASK(PTC13_LEDPin));
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
