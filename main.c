#include "MKL25Z4.h"

/* LIBRARIES */
#include "motor.h"


/* MAIN */
int main(void) {
	SystemCoreClockUpdate();
	
	initMotor();
	
	// Test digital GPIO out
//	PTD->PSOR = MASK(TEST_MOTOR);

	// PWM for TPM0
	// Forwards
	TPM0_C0V = 3750;   // Left: A2, B2
	TPM0_C2V = 1875;   // Right: A1, B1
	
	// Backwards
//	TPM0_C1V = 6000;   // Left: A1, B1
//	TPM0_C3V = 3000;   // Right: A2, B2
	
}


