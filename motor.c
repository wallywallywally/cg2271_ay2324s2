#include "MKL25Z4.h"
#include "motor.h"

#define MASK(x) (1 << (x))

// PORTD - for TPM0 with 6 channels 
#define PTD0_LEFT_FRONT 0
#define PTD1_LEFT_BACK 1
#define PTD2_RIGHT_FRONT 2
#define PTD3_RIGHT_BACK 3

// MOD for 50 Hz
// 48M / 128 (PS) = 375k
// 375k / 50 = 7500
#define MOD_value 7500

// METHODS
void initMotor(void) {
	// Enable Clock to PORTD
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	// Enable clock for TPM0
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	
	// MUX for TPM0_CH0-3
	PORTD->PCR[PTD0_LEFT_FRONT] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[PTD0_LEFT_FRONT] |= PORT_PCR_MUX(4);
	PORTD->PCR[PTD1_LEFT_BACK] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[PTD1_LEFT_BACK] |= PORT_PCR_MUX(4);
	PORTD->PCR[PTD2_RIGHT_FRONT] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[PTD2_RIGHT_FRONT] |= PORT_PCR_MUX(4);
	PORTD->PCR[PTD3_RIGHT_BACK] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[PTD3_RIGHT_BACK] |= PORT_PCR_MUX(4);
		
	// TPM clock source
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);			// 48 MHz
	
	// 50 Hz
	TPM0->MOD = MOD_value;
	
	// Init edge-aligned PWM
	TPM0->SC &= ~(TPM_SC_CMOD_MASK | TPM_SC_PS_MASK);
	TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM0->SC &= ~TPM_SC_CPWMS_MASK;

	// Enable PWM for TPM0_CH0-3
	TPM0_C0SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
	TPM0_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	TPM0_C1SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
	TPM0_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	TPM0_C2SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
	TPM0_C2SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	TPM0_C3SC &= ~(TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK);
	TPM0_C3SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
}

// MOVEMENT

// these are currently not timed -> need to figure out how long to run these for

// Basic controls
void leftSide_forwards(double percentage) {
	TPM0_C0V = (uint32_t) (MOD_value * percentage);		// A2, B2
}

void rightSide_forwards(double percentage) {
	TPM0_C2V = (uint32_t) (MOD_value * percentage);		// A1, B1
}

void leftSide_backwards(double percentage) {
	TPM0_C1V = (uint32_t) (MOD_value * percentage);		// A1, B1
}

void rightSide_backwards(double percentage) {
	TPM0_C3V = (uint32_t) (MOD_value * percentage);		// A2, B2
}

void forwards() {
	leftSide_forwards(100);
	rightSide_forwards(100);
}

void backwards() {
	leftSide_backwards(100);
	rightSide_backwards(100);
}

void left(int level) {
	// 3 angles of straight + left
	// Small, medium, large
	
}

void left_stationary(void) {
	rightSide_forwards(100);
	leftSide_backwards(100);
}

void right(int level) {
	
}

void right_stationary(void) {
	leftSide_forwards(100);
	rightSide_backwards(100);
}
