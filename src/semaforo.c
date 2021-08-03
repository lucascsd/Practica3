/*
 * semaforo.c
 *
 *  Created on: 2 ago. 2021
 *      Author: lucascsd
 */

#include "semaforo.h"

/*Arreglo del tipo gpioMap_t para leds */
const gpioMap_t ledArray[] = { LED1, LED2, LED3 };

ledFSM_t initSemaforoFSM ( ){

	ledFSM_t led = {RED_LED, NORMAL_ON_TIME_RED};

	return led;
}

bool_t updateSemaforoFSM ( ledFSM_t * led ){

	static delay_t noBloqRetardo;
	static bool_t iniciarRetardo = TRUE;

	if ( iniciarRetardo ){

		delayInit ( &noBloqRetardo, led->retardoLed );
		iniciarRetardo = FALSE;
	}

	switch ( led->secuenciaLed ){

	case RED_LED:
		if ( delayRead( &noBloqRetardo ) ){
			led->secuenciaLed = RED_YELLOW_LED;
			delayWrite ( &noBloqRetardo, led->retardoLed );
		}else{
			if ( !ledsOff( ledArray, 3 ) ) return FALSE;
			if ( !ledOn ( ledArray[0] ) ) return FALSE;
		}

		break;

	case RED_YELLOW_LED:

		break;

	case GREEN_LED:

		break;

	case YELLOW_LED:

		break;

	default:

		break;
	}
	return 1;
}