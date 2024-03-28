#include "MKL25Z4.h"
#include "onboardLED.h"

#define RED_LED 18 // PortB Pin 18
#define GREEN_LED 19 // PortB Pin 19
#define BLUE_LED 1 // PortD Pin 1
#define MASK(x) (1 << (x))

typedef enum color_t {
	RED = RED_LED,
	GREEN = GREEN_LED,
	BLUE = BLUE_LED
} color_t;
 
void initGPIO(void)
{
	// Enable Clock to PORTB and PORTD
	SIM->SCGC5 |= ((SIM_SCGC5_PORTB_MASK) | (SIM_SCGC5_PORTD_MASK));
	
	// Configure MUX settings to make all 3 pins GPIO
	PORTB->PCR[RED_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[GREEN_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED] |= PORT_PCR_MUX(1);
	
	PORTD->PCR[BLUE_LED] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED] |= PORT_PCR_MUX(1);
	
	// Set Data Direction Registers for PortB and PortD
	PTB->PDDR |= (MASK(RED_LED) | MASK(GREEN_LED));
	PTD->PDDR |= MASK(BLUE_LED);
	
	// Switch off everything first
	PTB->PSOR = (MASK(RED_LED) | MASK(GREEN_LED));
	PTD->PSOR = MASK(BLUE_LED);
}

#define led_on 0
#define led_off 1
void led_control(int LED, int led_state) {
	if (led_state == led_off) {
		// OFF: 1
		// PSOR to set to 1
		PTB->PSOR = MASK(LED);
		PTD->PSOR = MASK(LED);
	} else {
		// ON: 0
		// PCOR to clear to 0
		PTB->PCOR = MASK(LED);
		PTD->PCOR = MASK(LED);
	}
}

void off_led(void) {
	PTB->PSOR = MASK(GREEN_LED) | MASK(RED_LED);
	PTD->PSOR = MASK(BLUE_LED);
}
