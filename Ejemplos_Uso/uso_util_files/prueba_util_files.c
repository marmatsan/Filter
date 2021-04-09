/*******************************************************************

  Fichero     prueba_util_files.c

  Resumen     Fichero para probar el módulo util_files

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
#include "util_files.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main (int argc, char **argv){

  char *fichero, *directorio;

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

  int error = 0;
  char *dirAbs = NULL;
  struct stat bufStat;

  /*
     Nótese que como hay que cambiar dirAbs y bufStat dentro de
     la función, se pasan como parámetros las direcciones de memoria
  */
  error = info_file(directorio, fichero, &dirAbs, &bufStat);

  if (error){
    printf("Ha ocurrido un error\n");
    perror(strerror(error));
    exit(1);
  }

  char buffer[PATH_MAX];
  int nchars;

  printf("Datos del fichero: \n");
  printf("Path: %s \t Nombre: %s \n",directorio, fichero);
  printf("Dir absoluta: %s\n", dirAbs);
  printf("Número de inodo: %lu\n", bufStat.st_ino);
  printf("Tamaño: %lu\n", bufStat.st_size);

  if ((S_ISLNK(bufStat.st_mode))){
    nchars = readlink (dirAbs, buffer, PATH_MAX);
    buffer[nchars]=0;

    printf("Es un enlace simbólico:\n");
    printf("%s --> %s",dirAbs, buffer);
    printf((access(buffer,F_OK)==0) ? "\n" : "\n \t\t El fichero al que apunta no existe\n");
  }

  /*
     Debes liberar la memoria que se ha pedido (directa o indirectamente)
     SIEMPRE
  */
  if (dirAbs)
    free(dirAbs);

  return 0; // para indicar que no ha habido errores se devuelve un 0
}
