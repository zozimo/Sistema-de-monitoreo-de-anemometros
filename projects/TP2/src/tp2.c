/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones

#include "../inc/tp2.h"         // <= Su propia cabecera
//#include "sapi.h"        // <= Biblioteca sAPI
#include "sapi_board.h"
#include "sapi_delay.h"
#include "../inc/myGpio.h"

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig(); //Configura todo como GPIO
   //Despues piso los puertos en funcion de mi necesidad.


   // Crear varias variables del tipo booleano
   bool_t buttonValue = OFF;
   bool_t ledValue    = OFF;
   // Crear variable del tipo tick_t para contar tiempo
   tick_t timeCount   = 0;

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {

      /* Retardo bloqueante durante 100ms */
      
      delay( 100 );
      
      /* Si pasaron 10 segundos comienza a funcionar el programa que copia las
         acciones en BOTON al LED. Mientras espera titila el LED.  */
      
      timeCount++;      
      
      if( timeCount == 100 ){ // 100ms * 100 = 10s
         
         while( TRUE ) {
            
            /* Si se presiona CIAA_BOARD_BUTTON que esta cargado con TEC1 en sapi_peripheral_map.h, enciende el CIAA_BOARD_LED que esta cargado con LEDB en sapi_peripheral_map.h  */

            // Leer pin conectado al boton.
//            buttonValue = gpioRead( CIAA_BOARD_BUTTON );
            buttonValue = _mygpioRead( TEC4);
            // Invertir el valor leido, pues lee un 0 (OFF) con boton
            // presionado y 1 (ON) al liberarla.
            buttonValue = !buttonValue;
            // Escribir el valor leido en el LED correspondiente.
//            gpioWrite( CIAA_BOARD_LED, buttonValue );
            _mygpioWrite( LEDG, buttonValue );
            /* Enviar a la salida estandar (UART_DEBUG) el estado del LED */
            
            // Leer el estado del pin conectado al led
//            ledValue = gpioRead( CIAA_BOARD_LED );
            ledValue = _mygpioRead( LEDG );
            // Chequear si el valor leido es encedido
            if( ledValue == ON ) {
               // Si esta encendido mostrar por UART_USB "LED encendido."
               printf( "LED encendido.\r\n" );
            } else {
               // Si esta apagado mostrar por UART_USB "LED apagado."
               printf( "LED apagado.\r\n" );
            }
            delay( 250 );
            
         }
      } else {
         // Intercambiar el valor de CIAA_BOARD_LED
//         gpioToggle(CIAA_BOARD_LED);
         _mygpioToggle(LEDG);
      }
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
