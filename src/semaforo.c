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
	const uint8_t cantidadLeds = sizeof ( ledArray ) / sizeof ( gpioMap_t );

	if ( iniciarRetardo ){

		delayInit ( &noBloqRetardo, led->retardoLed );
		iniciarRetardo = FALSE;
	}

	switch ( led->secuenciaLed ){

	case RED_LED:
		if ( delayRead( &noBloqRetardo ) ){
			led->secuenciaLed = RED_YELLOW_LED;
			led->retardoLed = NORMAL_ON_TIME_RED_YELLOW;
			delayWrite ( &noBloqRetardo, led->retardoLed );
		}else{
			if ( !ledsOff( ledArray, cantidadLeds ) ) return FALSE;
			if ( !ledOn ( ledArray[LED1] ) ) return FALSE;
		}
		break;

	case RED_YELLOW_LED:
		if ( delayRead( &noBloqRetardo ) ){
			led->secuenciaLed = GREEN_LED;
			led->retardoLed = NORMAL_ON_TIME_GREEN;
			delayWrite ( &noBloqRetardo, led->retardoLed );
		}else{
			if ( !ledsOff( ledArray, cantidadLeds ) ) return FALSE;
			if ( !ledOn ( ledArray[LED1] ) ) return FALSE;
			if ( !ledOn ( ledArray[LED2] ) ) return FALSE;
		}
		break;

	case GREEN_LED:
		if ( delayRead( &noBloqRetardo ) ){
			led->secuenciaLed = YELLOW_LED;
			led->retardoLed = NORMAL_ON_TIME_YELLOW;
			delayWrite ( &noBloqRetardo, led->retardoLed );
		}else{
			if ( !ledsOff( ledArray, cantidadLeds ) ) return FALSE;
			if ( !ledOn ( ledArray[LED2] ) ) return FALSE;
		}
		break;

	case YELLOW_LED:
		if ( delayRead( &noBloqRetardo ) ){
			led->secuenciaLed = RED_LED;
			led->retardoLed = NORMAL_ON_TIME_RED;
			delayWrite ( &noBloqRetardo, led->retardoLed );
		}else{
			if ( !ledsOff( ledArray, cantidadLeds ) ) return FALSE;
			if ( !ledOn ( ledArray[LED3] ) ) return FALSE;
		}
		break;

	default:
		break;
	}
	return TRUE;
}
