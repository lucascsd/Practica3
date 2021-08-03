/*=============================================================================
 * Authors: Martin Rios <jrios@fi.uba.ar> - Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/07/12
 * Version: 1.0
 *===========================================================================*/

#ifndef EJERCICIOPROPUESTO_PRACTICA3_INC_LED_H_
#define EJERCICIOPROPUESTO_PRACTICA3_INC_LED_H_

#include "sapi.h"

// TIEMPOS DE ERROR (ms)
#define ERROR_OFF		500
#define ERROR_ON		1000
#define ERROR_SEQ		2000
#define ERROR_TIME		4000

// FUNCIONES DE CONTROL DE LEDS
bool_t ledsOff ( const gpioMap_t* _ledSequence, const uint8_t _sequenceLength );
bool_t ledOn ( gpioMap_t led );
bool_t ledToggle( gpioMap_t led );
void blinkError ( tick_t delayError );

#endif /* EJERCICIOPROPUESTO_PRACTICA3_INC_LED_H_ */
