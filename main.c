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
#include "audio.h"
#define MAIN_MUSIC_LEN 362

#include "onboardLED.h"	// FOR TESTING RTOS SYNC

/*----------------------------------------------------------------------------
 * Global sync
 *---------------------------------------------------------------------------*/


uint16_t x = 10000;
uint16_t motor_thread_loop = 0;
osMessageQueueId_t rxDataQ, motorMsg, ledFMsg, ledRMsg, audioMsg;
osEventFlagsId_t mainMusicFlag, winMusicFlag;
 
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
		// Set flags for win music
		if (rx_data == 0x50) {
			osEventFlagsClear(mainMusicFlag, 0x0001);
			osEventFlagsSet(winMusicFlag, 0x0001);
		}
	}
	
	// Error
	if (UART2->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK)) {
		// Clear error flag by reading UART_D
		uint8_t error_data = UART2->D;
	}
	
}
 
void brain_thread (void *argument) {
	osEventFlagsSet(mainMusicFlag, 0x0001);
	
	for (;;) {
		// Get data from rxDataQ
		uint8_t rx_data;
		osMessageQueueGet(rxDataQ, &rx_data, NULL, osWaitForever);
	
		// Process and send data
		osMessageQueuePut(motorMsg, &rx_data, NULL, 0);
		osMessageQueuePut(ledFMsg, &rx_data, NULL, 0);	
		osMessageQueuePut(ledRMsg, &rx_data, NULL, 0);
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
		motor_thread_loop++;
		switch (motor_data) {
		case 0x10:	// FRONT
			x++;
			forwards();
			break;
		case 0x20:	// BACK
			backwards();
			break;
		case 0x30:	// LEFT
			left_stationary();
			break;
		case 0x31:	// LEFT DIAG
			left_diag(1);									// TODO
			break;
		case 0x40:	// RIGHT
			right_stationary();
			break;	
		case 0x41:	// RIGHT DIAG
			right_diag(1);								// TODO
			break;	
		default:		// STOP - 0x00, 0x50
			x--;
			stop();
		}
	}
}
 
 /*----------------------------------------------------------------------------
 * Application led thread
 * Control the LEDs
 *---------------------------------------------------------------------------*/
void led_front_thread(void *argument) {

	uint8_t ledIndex = 0;
	uint8_t ledF_data = 0x00;
	// Read data from led queue
	for (;;) {
		osMessageQueueGet(ledFMsg, &ledF_data, NULL, 0);
		if (ledF_data != 0x00 && ledF_data != 0x50) { 
			offFrontLED();
			runningGREEN_Moving(ledIndex);
			ledIndex = (ledIndex + 1) % 8;
		} else {
			ledIndex = 0;
			solidGREEN_Stationery();
		}
		
	}
}

void led_rear_thread(void *argument) {
	
	uint8_t ledR_data = 0x00;
	// Read data from led queue
	for (;;) {
		osMessageQueueGet(ledRMsg, &ledR_data, NULL, 0);
		if (ledR_data != 0x00 && ledR_data != 0x50) {
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

void main_music_thread(void *argument) {
	for (;;) {
		for (int i = 0; i < MAIN_MUSIC_LEN; i++) {
			osEventFlagsWait(mainMusicFlag, 0x0001, osFlagsNoClear, osWaitForever);
			TPM1_C0V = (main_song[i] > 0) ? 10 : 0;
			TPM1->MOD = main_song[i];
			osDelay(main_delay[i]);
		}
	}
}

void win_music_thread(void *argument) {
	for (;;) {
		osEventFlagsWait(winMusicFlag, 0x0001, osFlagsWaitAny, osWaitForever);
		winMusic();
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
	initAudio();
	//initGPIO(); // FOR TESTING RTOS SYNC
	
	// Start multi-threaded environment 	
	osKernelInitialize();                 						// Initialize CMSIS-RTOS
		
	// Message queues
	rxDataQ = osMessageQueueNew(10, sizeof(uint8_t), NULL);
	motorMsg = osMessageQueueNew(10, sizeof(uint8_t), NULL);
	ledFMsg = osMessageQueueNew(10, sizeof(uint8_t), NULL);
	ledRMsg = osMessageQueueNew(10, sizeof(uint8_t), NULL);
	
	// Event flags
	mainMusicFlag = osEventFlagsNew(NULL);
	winMusicFlag = osEventFlagsNew(NULL);
	
	// Threads
	osThreadNew(brain_thread, NULL, NULL);						// Brain
	osThreadNew(motor_control_thread, NULL, NULL);    // Motors
	osThreadNew(led_front_thread, NULL, NULL); 				// Create led_front_thread
	osThreadNew(led_rear_thread, NULL, NULL);  				// Create led_rear_thread
	osThreadNew(main_music_thread, NULL, NULL); 			// Create main_music_thread
	osThreadNew(win_music_thread, NULL, NULL); 				// Create win_music_thread
	osKernelStart();                      						// Start thread execution
	
  for (;;) {}
}
