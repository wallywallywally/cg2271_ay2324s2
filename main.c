/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

/*----------------------------------------------------------------------------
 * MKL25Z4 + our libraries
 *---------------------------------------------------------------------------*/

#include "MKL25Z4.h"

#include "motor.h"
 
/*----------------------------------------------------------------------------
 * Application motor_control thread
 *---------------------------------------------------------------------------*/
void motor_control (void *argument) {
 
  // ...
  for (;;) {}
}

/*----------------------------------------------------------------------------
 * Application xxxxxx thread
 *---------------------------------------------------------------------------*/
void xxxxx (void *argument) {
 
  // ...
  for (;;) {}
}
 

/*----------------------------------------------------------------------------
 * MAIN
 *---------------------------------------------------------------------------*/

int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
	
	// Initialise components
	initMotor();
	
	
	// Testing normally
	// Test digital GPIO out
//	PTD->PSOR = MASK(TEST_MOTOR);

	// PWM for TPM0
	// Forwards
	TPM0_C0V = 3750;   // Left: A2, B2
	TPM0_C2V = 1875;   // Right: A1, B1
	
	// Backwards
//	TPM0_C1V = 6000;   // Left: A1, B1
//	TPM0_C3V = 3000;   // Right: A2, B2


	// Start multi-threaded environment 
//  osKernelInitialize();                 // Initialize CMSIS-RTOS
//  osThreadNew(motor_control, NULL, NULL);    // Create motor_control thread
//  osKernelStart();                      // Start thread execution
	
	
	
  for (;;) {}
}
