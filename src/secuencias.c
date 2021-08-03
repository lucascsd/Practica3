/*=============================================================================
 * Ejercicio 3
 * file: secuencias.c
 * Authors: Martin Rios <jrios@fi.uba.ar> - Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/07/12
 * Version: 1.0
 *===========================================================================*/

#include "secuencias.h"

// ********************* FUNCIÓN QUE ACTIVA LA SECUENCIA DE LEDS *******************************
// Recibe: un puntero a la estructura de la secuencia de LEDs que se quiere activar.
// Devuelve: TRUE en caso de encender correctamente el LED o FALSE en caso contrario.
// *********************************************************************************************
bool_t ledSequenceOn(controlSequence_t *controlSequence)
{
	static delay_t ledDelay; /* Variable del tipo tick para retardos */
	static bool_t firstRun = true;  /* Variable para comprobar si es la primera vez que se corre la secuencia */
	static modeSt_t mode = NORMAL;
    const gpioMap_t keyArray[] = { TEC1, TEC2, TEC3, TEC4 };	/*Arreglo del tipo gpioMap_t para teclas */
    const modeSt_t modeSequence[] = {NORMAL, DESCONECTADO, ALARMA}; /* Modos de la secuencia */
    static uint8_t modeSeqIndex = 0;

	if(firstRun){
		delayInit ( &ledDelay, controlSequence->onTime[0] ); /*Configuración del retardo no bloqueante inicial que determina el tiempo de transicion entre un led y el siguiente en la secuencia*/

		/* Se enciende el primer LED de la secuencia */
		if ( !ledOn ( controlSequence->ledSequence[0] ) ) return FALSE;

		firstRun = false;
	}

	if(controlSequence->ledSequence == NULL) return FALSE;  // Se comprueba que se haya asignado algo al puntero de la secuencia

	int8_t ledIndex = controlSequence->ledIndex;

	if( ledIndex >= controlSequence->lastLed ) return FALSE;  // Se comprueba que el indice del LED este dentro de los valores posibles de la secuencia

	if ( actualizarKeyFSM ( &teclaDOS ) ){
		modeSeqIndex += 1;
		if(modeSeqIndex > ((sizeof(modeSequence)/sizeof(modeSt_t)) - 1)) modeSeqIndex = 0;

		mode = modeSequence[modeSeqIndex];
		if(mode == NORMAL) controlSequence->ledIndex = 0;
	}

	/* Sentido normal de la secuencia */
	else if( actualizarKeyFSM ( &teclaUNO ) ){
		controlSequence->inverted = FALSE;
	}

	/* Sentido inverso de la secuencia */
	else if( actualizarKeyFSM ( &teclaCUATRO ) ){
		controlSequence->inverted = TRUE;
	}

	switch(mode){

	case NORMAL:
		if ( controlSequence->inverted ) ledIndex--;  /* Secuencia invertida */
		else ledIndex++;  /* Secuencia normal */

		/* ledIndex no debe exceder limite superior lastLed */
		if ( ledIndex >= controlSequence->lastLed ) ledIndex = 0;
		/* ledIndex no debe exceder limite inferior 0 */
		else if ( ledIndex < 0 ) ledIndex = controlSequence->lastLed - 1;

		if(delayRead(&ledDelay)){
			/* Se apagan todos los LEDs de la secuencia*/
			if ( !ledsOff(controlSequence->ledSequence, controlSequence->lastLed) ) return FALSE;
			/* Para encender en simultaneo el led rojo y amarillo */
			if ( ledIndex == RED_YELLOW_LED ) {
				if ( !ledOn ( controlSequence->ledSequence[ledIndex-1] ) ) return FALSE;
			}

			/* Se enciende el LED correspondiente de la secuencia */
			if ( !ledOn ( controlSequence->ledSequence[ledIndex] ) ) return FALSE;

			controlSequence->ledIndex = ledIndex;  // Se actualiza el indice del led que fue activado
			if ( !updateSemaforoFSM ( ledSecuencia ) )  return FALSE;
			delayInit ( &ledDelay, controlSequence->onTime[ledIndex] );
		}
		break;

	case DESCONECTADO:
		controlSequence->ledIndex = 1;
		delayInit ( &ledDelay, DISCONECTED_BLINK_TIME);

		/* Se apagan todos los LEDs de la secuencia*/
		if ( !ledsOff(controlSequence->ledSequence, controlSequence->lastLed) ) return FALSE;

		mode = BLINKING;
		break;

	case ALARMA:
		controlSequence->ledIndex = 0;
		delayInit ( &ledDelay, ALARM_BLINK_TIME);

		/* Se apagan todos los LEDs de la secuencia*/
		if ( !ledsOff(controlSequence->ledSequence, controlSequence->lastLed) ) return FALSE;

		mode = BLINKING;
		break;

	case BLINKING:
		if(delayRead(&ledDelay)){
			if(!ledToggle(controlSequence->ledSequence[ledIndex])) return FALSE;
		}
		break;

	}

	return TRUE;
}
