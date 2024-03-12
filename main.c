/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 * + MKL25Z4
 * + Component libraries
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "MKL25Z4.h"
#include "motor.h"
 
 /*----------------------------------------------------------------------------
 * Application brain thread
 * Decode the data from the Serial Port and perform the necessary action
 *---------------------------------------------------------------------------*/
void brain_thread (void *argument) {
 
  // ...
  for (;;) {}
}
 
/*----------------------------------------------------------------------------
 * Application motor_control thread
 * Control the action of the motors
 *---------------------------------------------------------------------------*/
void motor_control_thread (void *argument) {
 
  // ...
  for (;;) {}
}
 
 /*----------------------------------------------------------------------------
 * Application led thread
 * Control the LEDs
 *---------------------------------------------------------------------------*/
void led_thread (void *argument) {
 
  // ...
  for (;;) {}
}
 
/*----------------------------------------------------------------------------
 * Application audio thread
 * Provide audio output
 *---------------------------------------------------------------------------*/
void audio_thread (void *argument) {
 
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
	
	// MOTORS
	
	// PWM for TPM0
	// Forwards
//	TPM0_C0V = 3750;   // Left: A2, B2
//	TPM0_C2V = 1875;   // Right: A1, B1
	
	// Backwards
//	TPM0_C1V = 6000;   // Left: A1, B1
//	TPM0_C3V = 3000;   // Right: A2, B2




	// Start multi-threaded environment 
//  osKernelInitialize();                 // Initialize CMSIS-RTOS
//  osThreadNew(motor_control, NULL, NULL);    // Create motor_control thread
//  osKernelStart();                      // Start thread execution
	
  for (;;) {}
}
