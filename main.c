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
#include "myLED.h"
#include "serialComm.h"

#include "onboardLED.h"	// FOR TESTING RTOS SYNC

/*----------------------------------------------------------------------------
 * Global sync
 *---------------------------------------------------------------------------*/

static volatile int isMoving = 0;

osMessageQueueId_t rxDataQ, motorMsg, ledFMsg, ledRMsg, audioMsg;
 
 /*----------------------------------------------------------------------------
 * Serial communications
 * 1. UART2 IRQ handler
 * 2. Application brain thread
 * 		Decode the data from the Serial Port and perform the necessary action
 *---------------------------------------------------------------------------*/
  
 void UART2_IRQHandler(void) {
	// Clear pending IRQs
	NVIC_ClearPendingIRQ(UART2_IRQn);
	
	// RX ready
	if (UART2->S1 & UART_S1_RDRF_MASK) {
		uint8_t rx_data = UART2->D;
		osMessageQueuePut(rxDataQ, &rx_data, NULL, 0);
	}
	
	// Error
	if (UART2->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK)) {
		// Clear error flag by reading UART_D
		uint8_t error_data = UART2->D;
	}
	
}
 
void brain_thread (void *argument) {

  for (;;) {
		// Get data from rxDataQ
		uint8_t rx_data;
		osMessageQueueGet(rxDataQ, &rx_data, NULL, osWaitForever);
	
		// Process and send data
		osMessageQueuePut(motorMsg, &rx_data, NULL, 0);
		
		uint8_t ledData, audioData;
		switch (rx_data) {
		case 0x00:	// STOP
		osMessageQueuePut(ledFMsg, &rx_data, NULL, 0);	
		osMessageQueuePut(ledRMsg, &rx_data, NULL, 0);	
			break;
		case 0x10:	// FRONT
		osMessageQueuePut(ledFMsg, &rx_data, NULL, 0);	
		osMessageQueuePut(ledRMsg, &rx_data, NULL, 0);	
			break;
		case 0x20:	// BACK
		osMessageQueuePut(ledFMsg, &rx_data, NULL, 0);	
		osMessageQueuePut(ledRMsg, &rx_data, NULL, 0);	
			break;
		case 0x30:	// LEFT
		osMessageQueuePut(ledFMsg, &rx_data, NULL, 0);	
		osMessageQueuePut(ledRMsg, &rx_data, NULL, 0);	
			break;
		case 0x31:	// LEFT DIAG
		osMessageQueuePut(ledFMsg, &rx_data, NULL, 0);	
		osMessageQueuePut(ledRMsg, &rx_data, NULL, 0);	
			break;
		case 0x40:	// RIGHT
		osMessageQueuePut(ledFMsg, &rx_data, NULL, 0);	
		osMessageQueuePut(ledRMsg, &rx_data, NULL, 0);	
			break;	
		case 0x41:	// RIGHT DIAG
		osMessageQueuePut(ledFMsg, &rx_data, NULL, 0);	
		osMessageQueuePut(ledRMsg, &rx_data, NULL, 0);	
			break;
		case 0x50:	// END
		osMessageQueuePut(ledFMsg, &rx_data, NULL, 0);	
		osMessageQueuePut(ledRMsg, &rx_data, NULL, 0);	
			break;
		default:
			stop();
		}
		
//		osMessageQueuePut(ledMsg, &ledData, NULL, 0);
//		osMessageQueuePut(audioMsg, &audioData, NULL, 0);
	}
}
 
/*----------------------------------------------------------------------------
 * Application motor_control thread
 * Control the action of the motors
 *---------------------------------------------------------------------------*/
void motor_control_thread (void *argument) {
 
  for (;;) {
		// Read data from motor queue
		uint8_t motor_data;
		osMessageQueueGet(motorMsg, &motor_data, NULL, osWaitForever);
		
		switch (motor_data) {
		case 0x10:	// FRONT
			forwards();
			//TPM0_C0V = 3000;		// leftside back
			break;
		case 0x20:	// BACK
			backwards();
			//TPM0_C1V = 3000;     // leftside front
			break;
		case 0x30:	// LEFT
			left_stationary();
			//TPM0_C2V = 3000;		// rightside front
			break;
		case 0x31:	// LEFT DIAG
			left_diag(0);
			break;
		case 0x40:	// RIGHT
			right_stationary();
			//TPM0_C3V = 3000;		// rightside back
			break;	
		case 0x41:	// RIGHT DIAG
			right_diag(0);
			break;	
		default:		// STOP - 0x00, 0x50
			stop();
//			TPM0_C0V = 0;
//			TPM0_C1V = 0;
//			TPM0_C2V = 0;
//			TPM0_C3V = 0;
		}
	}
}
 
 /*----------------------------------------------------------------------------
 * Application led thread
 * Control the LEDs
 *---------------------------------------------------------------------------*/
void led_front_thread(void *argument) {

	uint8_t ledIndex = 0;
	// Read data from led queue
	uint8_t ledF_data;
	for (;;) {
		osMessageQueueGet(ledFMsg, &ledF_data, NULL, osWaitForever);
		if (ledF_data) { 
			runningGREEN_Moving(ledIndex);
			ledIndex = (ledIndex + 1) % 8;
		} else {
			ledIndex = 0;
			solidGREEN_Stationery();
		}
	}
}

void led_rear_thread(void *argument) {
	
	// Read data from led queue
	uint8_t ledR_data;
	for (;;) {
		osMessageQueueGet(ledRMsg, &ledR_data, NULL, osWaitForever);
		if (ledR_data) {
			flashRED_Moving();
		} else {
			flashRED_Staionery();
		}	
	}
}
 
/*----------------------------------------------------------------------------
 * Application audio thread
 * Provide audio output
 *---------------------------------------------------------------------------*/
void audio_thread (void *argument) {
 
  // Run from start
	// ... CONTINUOUS SONG TUNE
	
  for (;;) {
		// Stop once we finish the course
		uint8_t rx_data;
		osMessageQueueGet(audioMsg, &rx_data, NULL, osWaitForever);
		// ... UNIQUE TONE
	}
}

/*----------------------------------------------------------------------------
 * MAIN
 *---------------------------------------------------------------------------*/

int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
	
	// Initialise components
	initMotor();
	initLedPins();
	initUART2();
	//initGPIO(); // FOR TESTING RTOS SYNC
	
	// Start multi-threaded environment 	
  osKernelInitialize();                 						// Initialize CMSIS-RTOS
		
	// Message queues
	rxDataQ = osMessageQueueNew(10, sizeof(uint8_t), NULL);
	motorMsg = osMessageQueueNew(10, sizeof(uint8_t), NULL);
	ledFMsg = osMessageQueueNew(10, sizeof(uint8_t), NULL);
	ledRMsg = osMessageQueueNew(10, sizeof(uint8_t), NULL);
	audioMsg = osMessageQueueNew(10, sizeof(uint8_t), NULL);
	
	osThreadNew(brain_thread, NULL, NULL);						// Brain
  osThreadNew(motor_control_thread, NULL, NULL);    // Motors
  osThreadNew(led_front_thread, NULL, NULL); // Create led_front_thread
  osThreadNew(led_rear_thread, NULL, NULL);  // Create led_rear_thread
//	osThreadNew(audio_thread, NULL, NULL);
  osKernelStart();                      						// Start thread execution
	
  for (;;) {}
}
