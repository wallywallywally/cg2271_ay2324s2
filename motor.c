#include "MKL25Z4.h"
#include "motor.h"

// PORTD - for TPM0 with 6 channels 
#define PTD0_LEFT_FRONT 0
#define PTD1_LEFT_BACK 1
#define PTD2_RIGHT_FRONT 2
#define PTD3_RIGHT_BACK 3

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
	
	// MOD for 50 Hz
	// 48M / 128 = 375k
	// 375k / 50 = 7500
	TPM0->MOD = 7500;
	
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
// full power just max -> since we are PWM, we cannot use digital

void forwards() {
	// Forwards
//	TPM0_C0V = 3750;   // Left: A2, B2
//	TPM0_C2V = 1875;   // Right: A1, B1
}

void backwards() {
	// Backwards
//	TPM0_C1V = 6000;   // Left: A1, B1
//	TPM0_C3V = 3000;   // Right: A2, B2
}

void left(int deg) {
	// 3 angles of straight + left
	// Small, medium, large
	
}

void left_stationary(void) {
	
}

void right() {
	
}

void right_stationary(void) {
	
}
