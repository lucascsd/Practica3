/*=============================================================================
 * Ejercicio 3
 * file: led.c
 * Authors: Martin Rios <jrios@fi.uba.ar> - Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/07/12
 * Version: 1.0
 *===========================================================================*/
#include "led.h"

//***** FUNCIÓN DE APAGADO DE LEDS *************************************************************
// Recibe: un puntero a la secuencia de LEDs y la cantidad de elementos en la secuencia.
// Devuelve: TRUE si pudo apagar correctamente los LEDs o FALSE en caso contrario.
// *********************************************************************************************
bool_t ledsOff ( const gpioMap_t* _ledSequence, const uint8_t _sequenceLength )
{
	int8_t i = 0;

	for ( i = 0; i < _sequenceLength; i++ ) {
		/* Se apaga cada led disponible en la secuencia */
		if ( !gpioWrite ( _ledSequence[i], OFF ) ) return FALSE;
		/* Se verifica el apagado de leds, leyendo el estado GPIO de cada leds */
		if ( gpioRead ( _ledSequence[i] ) == ON ) return FALSE;
	}

	return TRUE;
}

//***** FUNCIÓN DE ENCENDIDO DE LEDS ***********************************************************
// Recibe: el numero de pin correspondiente a la GPIO del LED que se quiere encender
// Devuelve: TRUE en caso de encender correctamente el LED o FALSE en caso contrario.
// *********************************************************************************************
bool_t ledOn ( gpioMap_t led )
{
	/* Se enciende led pasado por argumento */
	if ( !gpioWrite ( led, ON ) ) return FALSE;
	/* Se verifica el apagado del led, leyendo el estado GPIO */
	if ( gpioRead ( led ) == OFF ) return FALSE;
	else return TRUE;

}

//***** FUNCIÓN PARA CAMBIAR EL ESTADO DE UN LED ***********************************************************
// Recibe: el numero de pin correspondiente a la GPIO del LED que se quiere cambiar
// Devuelve: TRUE en caso de cambiar el estado del LED correctamente o FALSE en caso contrario.
// *********************************************************************************************
bool_t ledToggle( gpioMap_t led )
{
	return(gpioToggle ( led ));
}

//***** FUNCIÓN INDICACIÓN DE ERROR ************************************************************
// Recibe: El tiempo de encendido y apagado del led segun el tipo de error que se quiera mostrar
// Devuelve: Nada
// *********************************************************************************************
void blinkError ( tick_t delayError )
{
	/* El programa se queda aca PARA SIEMPRE */
	while ( true ) {
		/* Parpadeo de led Rojo */
		gpioToggle ( LEDR );
		/* Retardo bloqueante segun tipo de error */
		delay ( delayError );
	}
}
