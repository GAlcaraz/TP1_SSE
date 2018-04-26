/*
 * tp1.c
 *
 *  Created on: Apr 19, 2018
 *      Author: galca
 */


#include "sapi.h"
#include "tp1.h"

#ifdef TP1_1



int main(void){
   boardConfig();
   while(1) {
      gpioWrite( LEDB, ON );
      delay(LED_TOGGLE_MS);
      gpioWrite( LEDB, OFF );
      delay(LED_TOGGLE_MS);
   }
   return 0 ;
}
#endif

#ifdef TP1_2

int main(void){
   boardConfig();

   gpioConfig( GPIO0, GPIO_INPUT );

   gpioConfig( GPIO1, GPIO_OUTPUT );

   bool_t valor;
   while(1) {

      valor = !gpioRead( TEC1 );
      gpioWrite( LEDB, valor );

      valor = !gpioRead( TEC2 );
      gpioWrite( LED1, valor );

      valor = !gpioRead( TEC3 );
      gpioWrite( LED2, valor );

      valor = !gpioRead( TEC4 );
      gpioWrite( LED3, valor );

      valor = !gpioRead( GPIO0 );
      gpioWrite( GPIO1, valor );
   }
	return 0 ;
}

#endif


#ifdef TP1_3

#define TICKRATE_MS	500	//10 100
#define LED_TOGGLE_MS 1000 //	100	500

/* FUNCION que se ejecuta cada vez que ocurre un Tick. */
void myTickHook( void *ptr ){

   static bool_t ledState = OFF;

   gpioMap_t led = (gpioMap_t)ptr;

   if( ledState ){
      ledState = OFF;
   }
   else{
      ledState = ON;
   }
   gpioWrite( led, ledState );
}

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* The DEBUG* functions are sAPI debug print functions.
   Code that uses the DEBUG* functions will have their I/O routed to
   the sAPI DEBUG UART. */
   DEBUG_PRINT_ENABLE;
   /* UART for debug messages. */
   debugPrintConfigUart( UART_USB, 115200 );
   debugPrintString( "DEBUG c/sAPI\r\n" );
   debugPrintString( "LED Toggle\n" );



   /* Inicializar el conteo de Ticks con resolucion de 50ms (se ejecuta
      periodicamente una interrupcion cada 50ms que incrementa un contador de
      Ticks obteniendose una base de tiempos). */
   tickConfig( TICKRATE_MS );

   /* Se agrega ademas un "tick hook" nombrado myTickHook. El tick hook es
      simplemente una funcion que se ejecutara peri�odicamente con cada
      interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
      a una interrupcion.
      El segundo parametro es el parametro que recibe la funcion myTickHook
      al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
   */
   tickCallbackSet( myTickHook, (void*)LEDR );
   delay(LED_TOGGLE_MS);

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      tickCallbackSet( myTickHook, (void*)LEDG );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LEDB );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LED1 );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LED2 );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LED3 );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LEDR );
      delay(LED_TOGGLE_MS);
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}



#endif


