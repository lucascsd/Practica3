/*=============================================================================
 * Ejercicio 3
 * Authors: Martin Rios <jrios@fi.uba.ar> - Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/07/12
 * Version: 1.0
 *===========================================================================*/

#include "ejercicio3.h"

/* FUNCION PRINCIPAL */
int main( void )
{

	// INICIALIZAR Y CONFIGURAR PLATAFORMA
    boardInit();

    /* Verificación TICK_RATE rango permitido de tiempo: 1 a 50 ms */
    if ( ( TICK_RATE < TICK_RATE_MIN ) || ( TICK_RATE > TICK_RATE_MAX ) )  blinkError( ERROR_TIME );
    if ( !tickConfig ( TICK_RATE ) )  blinkError( ERROR_TIME );

    // DEFINICION DE VARIABLES
    // Se define la estructura para el control de la secuencia de LEDs
    controlSequence_t controlSequenceLeds = { NULL, 0, 0, false, NULL};

    const gpioMap_t sequence2[] = {RED_LED, RED_YELLOW_LED, GREEN_LED, YELLOW_LED};
    uint16_t onTimeSequence2[] = {NORMAL_ON_TIME_RED, NORMAL_ON_TIME_RED_YELLOW, NORMAL_ON_TIME_GREEN, NORMAL_ON_TIME_RED_YELLOW};

    // Se inicializan los parametros de la estructura
    controlSequenceLeds.ledSequence = sequence2;
    controlSequenceLeds.lastLed = sizeof ( sequence2 ) / sizeof ( gpioMap_t );
    controlSequenceLeds.onTime = onTimeSequence2;

    // Se inicializa la MEF de las teclas
    teclaUNO 	= inicializarKeyFSM ( TEC1 );
    teclaDOS 	= inicializarKeyFSM ( TEC2 );
    teclaTRES 	= inicializarKeyFSM ( TEC3 );
    teclaCUATRO = inicializarKeyFSM ( TEC4 );

    // Se inicializa la MEF de las teclas
	ledSecuencia = initSemaforoFSM ();
	
	/* Apagado de leds y captura de errores de apagado */
    if ( !ledsOff( controlSequenceLeds.ledSequence, controlSequenceLeds.lastLed) ) blinkError ( ERROR_OFF );

   // ----- Repeat for ever -------------------------
    while( true ) {
    	/* Se activa la secuencia correspondiente. En caso de error el programa se bloquea quedando el led rojo parpadeando. */
    	if(!ledSequenceOn(&controlSequenceLeds)) blinkError ( ERROR_SEQ );
    }
    return 0;
}
