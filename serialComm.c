#include "MKL25Z4.h"
#include "serialComm.h"

#define MASK(x) (1 << (x))

// PORTS - UART2
#define UART_RX_PTE23 23
#define UART_INT_PRIORITY 128
#define BAUD_RATE 9600

#define ESP_PTC13 13

// METHODS
void initUART2(void) {
	uint32_t divisor, bus_clk;
	
	// Enable clock to UART2 and PORTE
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	// Connect UART pins for PTE23
	PORTE->PCR[UART_RX_PTE23] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[UART_RX_PTE23] |= PORT_PCR_MUX(4);
	
	// Disable TX/RX before configuration
	UART2->C2 &= ~((UART_C2_TE_MASK)|(UART_C2_RE_MASK));
	
	// Set baud rate
	bus_clk = DEFAULT_SYSTEM_CLOCK / 2;
	divisor = bus_clk / (BAUD_RATE * 16);
	UART2->BDH = UART_BDH_SBR(divisor >> 8);
	UART2->BDL = UART_BDL_SBR(divisor);
	
	// No parity bits, no need to edit these registers
	// Our data packet is 8b
	UART2->C1 = 0;
	UART2->S2 = 0;
	UART2->C3 = 0;
	
	// UART2 interrupt setup
	NVIC_SetPriority(UART2_IRQn, UART_INT_PRIORITY);
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);

	// Enable Interrupts
	UART2->C2 &= ~(UART_C2_TIE_MASK | UART_C2_TCIE_MASK);
	UART2->C2 |= (UART_C2_RIE_MASK);		// Only enable RX
	
	// Enable TX and RX
	UART2->C2 |= (UART_C2_RE_MASK);
}
