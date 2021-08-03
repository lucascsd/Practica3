/*
 * semaforo.h
 *
 *  Created on: 2 ago. 2021
 *      Author: lucascsd
 */

#ifndef EJERCICIOPROPUESTO_PRACTICA3_INC_SEMAFORO_H_
#define EJERCICIOPROPUESTO_PRACTICA3_INC_SEMAFORO_H_

#include "led.h"
#include "teclas.h"
#include "sapi.h"

typedef enum
{
	RED_LED,
	RED_YELLOW_LED,
	GREEN_LED,
	YELLOW_LED,
}stateSemaforo_t;

typedef struct
{
	stateSemaforo_t secuenciaLed;
	tick_t 			retardoLed;
}ledFSM_t ;

ledFSM_t ledSecuencia;

#define NORMAL_ON_TIME_RED			3000
#define NORMAL_ON_TIME_RED_YELLOW	500
#define NORMAL_ON_TIME_YELLOW		500
#define NORMAL_ON_TIME_GREEN		1000

//FUNCIONES PARA LA MAQUINA DE ESTADO FINITO
//DE LAS TECLAS
ledFSM_t initSemaforoFSM ( );
bool_t updateSemaforoFSM ( ledFSM_t * led );


#endif /* EJERCICIOPROPUESTO_PRACTICA3_INC_SEMAFORO_H_ */
