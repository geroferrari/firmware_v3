/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// File creation date: 2016-12-11

//==================[inclusions]===============================================

#include "sapi.h"     // <= sAPI header

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. ============
int main(void){

   // ------------- INICIALIZACIONES -------------

   // Inicializar la placa
   boardInit();

   // Inicializar UART_USB a 115200 baudios
   uartInit( UART_USB, 115200 );

   char miTexto[] = "hola como le va";

   bool_t received = FALSE;

   uartWriteString( UART_USB, "Se espera a que el usuario escriba \"hola como le va\",\r\n" );
   uartWriteString( UART_USB, "o sale por timeout (10 segundos) y vuelve a esperar\r\n" );
   uartWriteString( UART_USB, "a que se escriba el mensaje.\r\n" );

   // ------------- REPETIR POR SIEMPRE -------------
   while(1) {

      received = waitForReceiveStringOrTimeoutBlocking(
                    UART_USB,
                    miTexto,
                    strlen(miTexto),
                    10000
                 );

      // Si recibe el string almacenado en miTexto indica que llego el
      // mensaje esperado.
      if( received ){
         uartWriteString( UART_USB, "\r\nLlego el mensaje esperado\r\n" );
      }
      // Si no lo recibe indica que salio de la funcion
      // waitForReceiveStringOrTimeoutBlocking  por timeout.
      else{
         uartWriteString( UART_USB, "\r\nSalio por timeout\r\n" );
      }

   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
   // por ningun S.O.
   return 0;
}

//==================[end of file]==============================================
