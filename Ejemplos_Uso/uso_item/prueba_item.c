/*******************************************************************

  Fichero     prueba_item.c

  Resumen     Fichero para probar el módulo item. No se prueban las funciones
              de comparación, esto se deja como trabajo del alumno.

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

#include "item.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main (int argc, char **argv){

  char *fichero,*directorio;

#ifdef DEBUG
  printf("Depurando... Usando printf\n");
  // esto no es lo más recomendable. Usad gdb para depurar
#endif


  if (argc == 3){
    directorio = argv[1];
    fichero = argv[2];
  } else{
    printf("Número argumentos incorrecto\n");
    printf("Llamada: %s nombreDirectorio nombreFichero\n",argv[0]);
    exit(1);
  }

  char dirAbs[PATH_MAX];
  struct stat info;
  realpath(directorio, dirAbs);
  strcat(dirAbs,"/");
  strcat(dirAbs, fichero);

  if (lstat(fichero, &info) == -1){
    printf("Ha ocurrido un error\n");
    perror(strerror(errno));
    exit(1);
  }

  struct item nuevo_item;
  int error = 0;

  nuevo_item = create_item(".", fichero, dirAbs, info, &error);

  if (error){
    printf("Ha ocurrido un error\n");
    perror(strerror(error));
    exit(1);
  }

  print_item(nuevo_item);

  /*
     Debes liberar la memoria que se ha pedido (directa o indirectamente)
     SIEMPRE
  */

  free_item(&nuevo_item);

  return 0; // para indicar que no ha habido errores se devuelve un 0
}
