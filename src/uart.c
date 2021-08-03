/*
 * uart.c
 *
 *  Created on: 2 ago. 2021
 *      Author: lucascsd
 */

#include "uart.h"

bool_t initUART(){
	
	bool_t printOk = FALSE;
	uartInit ( UART_USB, 115200 );
	debugPrintlnString	( "UART_USB configurada.\n\r" );
	return TRUE;
}

bool_t infoUART(){
	
	debugPrintlnString( menu );
	return TRUE;
}

bool_t printStateDebounce( stateKey_t estadoTeclas ){

	return TRUE;
}
bool_t printStateKey( teclaFSM teclaPresionada ){

	return TRUE;
}
	
bool_t printModeSeq( modeSt_t ){

	return TRUE;
}