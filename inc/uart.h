/*
 * semaforo.h
 *
 *  Created on: 2 ago. 2021
 *      Author: lucascsd
 */

#ifndef EJERCICIOPROPUESTO_PRACTICA3_INC_UART_H_
#define EJERCICIOPROPUESTO_PRACTICA3_INC_UART_H_

#include "sapi.h"
//VARIABLES

static uint8_t menu[] =
		"\n\r"
		"********************* Practica 4 - Prog. de uP ********************\n\r"
		"\n\r"
		"Alumnos: Rios - Zalazar									\n\r"
		"Led Rojo: 	Alarma Armada								\n\r"
		"Led Verde: Alarma Desarmada							\n\r"
		"Led Azul 	Parpadeante: Ingreso de contraseña			\n\r"
		"Led Rojo 	Parpadeante: Intruso						\n\r"
		"*******************************************************************\n\r"
		;

//FUNCIONES PARA LA UART
bool_t initUART();
bool_t printStateDebounce( stateKey_t estadoTeclas )
bool_t printStateKey( teclaFSM teclaPresionada );
bool_t printModeSeq( modeSt_t );


#endif /* EJERCICIOPROPUESTO_PRACTICA3_INC_UART_H_ */