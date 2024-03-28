#include "MKL25Z4.h"                    // Device header
#include "audio.h"
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#define PTB0_Pin 0 // Port B Pin 0
#define MASK(x) (1 << (x))

int main_song[] = {
	E5, REST, E5, REST, E5, REST, C5, REST, E5, REST, G5, REST, G4, // Melody 1
	
	// Melody 2
	C5, G4, E4, A4, B4, A4, Ab4, G4, E5, G5, A5, F5, G5, E5, C5, D5, B4, REST,
	C5, G4, E4, A4, B4, A4, Ab4, G4, E5, G5, A5, F5, G5, E5, C5, D5, B4, REST,
	
	//Melody 3
	G5, Gb5, F5, Eb5, E5, Ab4, A4, C5, A4, C5, D5, G5, Gb5, F5, Eb5, E5, C6, REST, C6, REST, C6, REST,
	G5, Gb5, F5, Eb5, E5, Ab4, A4, C5, A4, C5, D5, Eb5, D5, C5, REST,
	G5, Gb5, F5, Eb5, E5, Ab4, A4, C5, A4, C5, D5, G5, Gb5, F5, Eb5, E5, C6, REST, C6, REST, C6, REST,
	G5, Gb5, F5, Eb5, E5, Ab4, A4, C5, A4, C5, D5, Eb5, D5, C5, REST,
	
	// Melody 4
	C5, REST, C5, REST, C5, REST, C5, REST, D5, REST, E5, REST, C5, REST, A4, REST, G4, REST, C5, REST, C5, REST, C5, REST, C5, REST, D5, REST, E5, REST,
	C5, REST, C5, REST, C5, REST, C5, REST, D5, REST, E5, REST, C5, REST, A4, REST, G4, REST,

	// Melody 1
	E5, REST, E5, REST, E5, REST, C5, REST, E5, REST, G5, REST, G4,

	// Melody 2
	C5, G4, E4, A4, B4, A4, Ab4, G4, E5, G5, A5, F5, G5, E5, C5, D5, B4, REST,
	C5, G4, E4, A4, B4, A4, Ab4, G4, E5, G5, A5, F5, G5, E5, C5, D5, B4, REST,
	
	// Melody 5
	E5, C5, G4, Ab4, A4, F5, REST, F5, REST, A4, B4, A5, REST, A5, REST, A5, REST, G5, F5, E5, C5, A4, G4,
	E5, C5, G4, Ab4, A4, F5, REST, F5, REST, A4, B4, F5, REST, F5, REST, F5, REST, E5, REST, D5, C5, G4, E4, C4,
	E5, C5, G4, Ab4, A4, F5, REST, F5, REST, A4, B4, A5, REST, A5, REST, A5, REST, G5, F5, E5, C5, A4, G4,
	E5, C5, G4, Ab4, A4, F5, REST, F5, REST, A4, B4, F5, REST, F5, REST, F5, REST, E5, REST, D5, C5, G4, E4, C4,
	
	// Melody 4
	C5, REST, C5, REST, C5, REST, C5, REST, D5, REST, E5, REST, C5, REST, A4, REST, G4, REST, C5, REST, C5, REST, C5, REST, C5, REST, D5, REST, E5, REST,
	C5, REST, C5, REST, C5, REST, C5, REST, D5, REST, E5, REST, C5, REST, A4, REST, G4, REST,
	};

int main_delay[] = {
	// Melody 1
	100, 60, 100, 200, 100, 190, 140, 80, 140, 200, 140, 540, 680,

	// Melody 2
	450, 450, 570, 270, 270, 200, 300, 250, 200, 200, 300, 220, 300, 300, 130, 190, 400, 100,
	450, 450, 570, 270, 270, 200, 300, 250, 200, 200, 300, 220, 300, 300, 130, 190, 400, 200,

	// Melody 3
	150, 150, 150, 320, 270, 130, 200, 300, 150, 170, 480, 150, 150, 150, 320, 270, 250, 130, 120, 10, 250, 670,
	150, 150, 150, 320, 270, 130, 200, 300, 150, 170, 480, 480, 480, 480, 900,
	150, 150, 150, 320, 270, 130, 200, 300, 150, 170, 480, 150, 150, 150, 320, 270, 250, 130, 120, 10, 250, 670,
	150, 150, 150, 320, 270, 130, 200, 300, 150, 170, 480, 480, 480, 480, 900,
	
	// Melody 4
	100, 50, 100, 190, 100, 270, 100, 50, 100, 240, 100, 130, 100, 180, 100, 70, 100, 580, 100, 50, 100, 270, 100, 270, 100, 80, 100, 80, 100, 1230,
	100, 50, 100, 190, 100, 270, 100, 50, 100, 240, 100, 130, 100, 180, 100, 70, 100, 520,

	// Melody 1
	100, 60, 100, 200, 100, 190, 140, 80, 140, 200, 140, 540, 680,

	// Melody 2
	450, 450, 570, 270, 270, 200, 300, 250, 200, 200, 300, 220, 300, 300, 130, 190, 400, 100,
	450, 450, 570, 270, 270, 200, 300, 250, 200, 200, 300, 220, 300, 300, 130, 190, 400, 200,
	
	// Melody 5
	140, 300, 510, 270, 150, 100, 200, 100, 50, 680, 170, 100, 100, 100, 100, 100, 100, 220, 150, 200, 230, 180, 660,
	140, 300, 510, 270, 150, 100, 200, 100, 50, 680, 230, 100, 150, 100, 50, 100, 50, 100, 140, 240, 240, 200, 160, 620,
	140, 300, 510, 270, 150, 100, 200, 100, 50, 680, 170, 100, 100, 100, 100, 100, 100, 220, 150, 200, 230, 180, 660,
	140, 300, 510, 270, 150, 100, 200, 100, 50, 680, 230, 100, 150, 100, 50, 100, 50, 100, 140, 240, 240, 200, 160, 620,
	
	// Melody 4
	100, 50, 100, 190, 100, 270, 100, 50, 100, 240, 100, 130, 100, 180, 100, 70, 100, 580, 100, 50, 100, 270, 100, 270, 100, 80, 100, 80, 100, 1230,
	100, 50, 100, 190, 100, 270, 100, 50, 100, 240, 100, 130, 100, 180, 100, 70, 100, 520,
	};

void initAudio(void) {
	// Enable Clock Gating for PortB
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	// Configure Mode 3 for the PWM pin operation
	PORTB->PCR[PTB0_Pin] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[PTB0_Pin] |= PORT_PCR_MUX(3);
	
	// Enable Clock Gating for Timer1
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
	
	// Select clock for TPM module (internal/external clock)
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // MCGFLLCLK or MCGPLLCLK
	
	// Set Modulo Value 20971520 / 128 = 163840 / 3276 = 50 Hz
	//TPM->MOD = 3276;
	
	// Set C0V value to off the buzzer
	TPM1_C0V = 0;
	
	// Set Modulo Value 48000000 / 128 = 375000 / 7500 = 50 Hz
	TPM1->MOD = 7500;
	
	/* Edge-Aligned PWM */
	// Update SnC register: CMOD = 01, PS = 111 (128)
	TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM1->SC &= ~TPM_SC_CPWMS_MASK;
	
	// Enable PWM on TPM1 Channel 0 -> PTB0 (edge-aligned)
	TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM1_C0SC |= TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1);
}

void winMusic(void) {
	TPM1_C0V = 0;
	osDelay(220);
	TPM1_C0V = 10;
	TPM1->MOD = G3;
	osDelay(140);
	TPM1->MOD = C4;
	osDelay(140);
	TPM1->MOD = E4;
	osDelay(140);
	TPM1->MOD = G4;
	osDelay(140);
	TPM1->MOD = C5;
	osDelay(140);
	TPM1->MOD = E5;
	osDelay(140);
	TPM1->MOD = G5;
	osDelay(420);
	TPM1->MOD = E5;
	osDelay(420);
	// Part 2
	TPM1->MOD = Ab3;
	osDelay(140);
	TPM1->MOD = C4;
	osDelay(140);
	TPM1->MOD = Eb4;
	osDelay(140);
	TPM1->MOD = Ab4;
	osDelay(140);
	TPM1->MOD = C5;
	osDelay(140);
	TPM1->MOD = Eb5;
	osDelay(140);
	TPM1->MOD = Ab5;
	osDelay(420);
	TPM1->MOD = Eb5;
	osDelay(420);
	// Part 3
	TPM1->MOD = Bb3;
	osDelay(140);
	TPM1->MOD = D4;
	osDelay(140);
	TPM1->MOD = F4;
	osDelay(140);
	TPM1->MOD = Bb4;
	osDelay(140);
	TPM1->MOD = D5;
	osDelay(140);
	TPM1->MOD = F5;
	osDelay(140);
	TPM1->MOD = Bb5;
	osDelay(420);
	TPM1_C0V = 0;
	osDelay(10);
	TPM1_C0V = 10;
	TPM1->MOD = Bb5;
	osDelay(130);
	TPM1_C0V = 0;
	osDelay(10);
	TPM1_C0V = 10;
	TPM1->MOD = Bb5;
	osDelay(130);
	TPM1_C0V = 0;
	osDelay(10);
	TPM1_C0V = 10;
	TPM1->MOD = Bb5;
	osDelay(130);
	TPM1->MOD = C6;
	osDelay(1000);
	TPM1_C0V = 0;
}
