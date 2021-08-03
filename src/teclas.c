/*=============================================================================
 * Ejercicio 3
 * file: teclas.c
 * Authors: Martin Rios <jrios@fi.uba.ar> - Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/07/12
 * Version: 1.0
 *===========================================================================*/
#include "teclas.h"

/*Arreglo del tipo gpioMap_t para teclas */
const gpioMap_t keyArray[] = { TEC1, TEC2, TEC3, TEC4 };

//***** FUNCION QUE DETERMINA SI UNA TECLA FUE PRESIONADA **************************************
// Recibe: el numero de tecla que se quiere consultar
// Devuelve: TRUE si la tecla fue presionada o FALSE en caso contrario
// *********************************************************************************************

//***** LECTURA DE TECLAS CON FUNCION ANTIRREBOTE **********************************************
// Recibe: el arreglo de teclas y el indice correspondiente de la tecla dentro del arreglo
// Devuelve: TRUE si la tecla fue presionada o FALSE en caso contrario
// *********************************************************************************************

//******************************************************************************//
//																				//
//						FUNCIONES DE LUCAS										//
//																				//
//******************************************************************************//

teclaFSM inicializarKeyFSM ( gpioMap_t key ){

	teclaFSM tecla = {key, TECLA_LIBERADA, 0};

	return tecla;
}

bool_t actualizarKeyFSM ( teclaFSM * tecla ){

	static bool_t keyPressed = FALSE;

	switch ( tecla->estadoTecla ){

	case TECLA_PRESIONADA:
		if ( gpioRead ( tecla->teclaPosicion ) ) {
			tecla->estadoTecla = TECLA_ASCENDENTE;
			delayInit( &tecla->retardoNoBloqueante, DEBOUNCE_TIME );
		}
		else tecla->estadoTecla = TECLA_PRESIONADA;
		keyPressed = FALSE;
		break;

	case TECLA_ASCENDENTE:
		if ( delayRead ( &tecla->retardoNoBloqueante ) ) {
			if ( gpioRead ( tecla->teclaPosicion ) ){
				tecla->estadoTecla = TECLA_LIBERADA;
				buttonReleased ( tecla->teclaPosicion );
			}
			else {
				tecla->estadoTecla = TECLA_PRESIONADA;
			}
		}
		keyPressed = FALSE;
		break;

	case TECLA_LIBERADA:
		if ( !gpioRead ( tecla->teclaPosicion ) ){
			tecla->estadoTecla = TECLA_DESCENDENTE;
			delayInit( &tecla->retardoNoBloqueante, DEBOUNCE_TIME );
		}
		else tecla->estadoTecla = TECLA_LIBERADA;
		keyPressed = FALSE;
		break;

	case TECLA_DESCENDENTE:
		if ( delayRead ( &tecla->retardoNoBloqueante ) ) {
			if ( !gpioRead ( tecla->teclaPosicion ) ){
				tecla->estadoTecla = TECLA_PRESIONADA;
				keyPressed = buttonPressed ( tecla->teclaPosicion );
			}
			else{
				tecla->estadoTecla = TECLA_LIBERADA;
				keyPressed = FALSE;
			}
		} else keyPressed = FALSE;
		break;

	default:
		tecla->estadoTecla = TECLA_LIBERADA;
		break;
	}
	return keyPressed;
}

bool_t buttonPressed(gpioMap_t tecla){

	bool_t keyPressed;
	return keyPressed = TRUE;
}

bool_t buttonReleased(gpioMap_t tecla){

	return TRUE;
}

