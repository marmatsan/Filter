/*******************************************************************

  Fichero     prueba_input_program.c

  Resumen     Fichero para probar el módulo input_program. 

  Autor       Iria Estévez Ayres

  Copyright   [Copyright (c) 2017 Universidad Carlos III de Madrid

  Se concede, sin necesidad de acuerdo por escrito y sin ningún tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentación para cualquier propósito siempre y cuando esta advertencia
  y los siguientes dos párrafos aparezcan en las copias.

  EN NINGÚN CASO SE RECONOCERÁ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
  DIRECTA, INDIRECTA, ESPECIAL, O SUBSIDIARIA DE LOS POSIBLES DAÑOS Y PERJUICIOS
  QUE PUEDAN DERIVARSE DEL USO DE ESTE PROGRAMA Y DE SU DOCUMENTACIÓN, INCLUSO
  EN EL CASO DE QUE LA UNIVERSIDAD CARLOS III DE MADRID HAYA SIDO ADVERTIDA DE
  TALES DAÑOS Y PERJUICIOS.

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÍFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÍAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

#include "input_program.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main (int argc, char **argv){


#ifdef DEBUG
  printf("Depurando... Usando printf\n");
  // esto no es lo más recomendable. Usad gdb para depurar
#endif

  long value;
  int error;
  char *cadena = NULL;
  
  printf("Tell me a number (base 10): ");
  value = get_number(10, &error);
  if (error)
    printf("An error happened (2): %s\n",get_error_msg_input(error));
  else
    printf("Number: %ld\n",value);

  printf("Tell me a number (base 16): ");
  value = get_number(16, &error);
  if (error)
    printf("An error happened (3): %s\n",get_error_msg_input(error));
  else
    printf("Number: %ld\n",value);

  printf("Tell me a number (base 2): ");

  value = get_number(2, &error);
  if (error)
    printf("An error happened (3): %s\n",get_error_msg_input(error));
  else
    printf("Number: %ld\n",value);

  printf("Give me an string: ");

  cadena = get_string(&error);

  if (error)
    printf("An error happened (3): %s\n",get_error_msg_input(error));
  else
    printf("String: %s\n",cadena);

  printf("Give me another string: ");

  cadena = get_string(&error);

  if (error)
    printf("An error happened (3): %s\n",get_error_msg_input(error));
  else
    printf("String: %s\n",cadena);

  /*
    Fijaos que en el ejemplo anterior no he liberado la cadena cadena,
    el módulo me devuelve una referencia a cadena (que es la misma que
    guarda el módulo internamente y luego la libera usando 
    clean_module_input_program*/
  clean_module_input_program(); // importante para que no haya fugas de memoria
  
  return 0; // para indicar que no ha habido errores se devuelve un 0
}
