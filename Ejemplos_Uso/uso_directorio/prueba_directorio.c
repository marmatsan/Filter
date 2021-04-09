/*******************************************************************

  Fichero     prueba_directorio.c

  Resumen     Fichero para probar el módulo directorio

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
#include "directorio.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv){

  char *path;

#ifdef DEBUG
  printf("Depurando... Usando printf\n");
  // esto no es lo más recomendable. Usad gdb para depurar
#endif

  if (argc == 1){
    path = ".";

  } else if (argc == 2){

    path = argv[1];

  } else{
    printf("Número argumentos incorrecto\n");
    printf("Llamada: %s [nombreDirectorio]\n",argv[0]);
    exit(1);
  }

  struct dirent **info = NULL;
  int numero = 0;
  int error = 0;

  /*
     Nótese que como hay que cambiar info_files y error dentro de
     la función, se pasan como parámetros las direcciones de memoria
  */
  numero = info_all_files_dir(path, &info, &error);

  if (error){
    printf("Ha ocurrido un error\n");
    perror(strerror(error));
    exit(1);
  }

  /*
    Importante: i debe estar definido fuera del for.
    C no soporta la definición de variables dentro del for
  */
  int i;
  printf("Número de archivos: %i\n",numero );
  for (i=0; i< numero; i++){
    printf("[%i] %s\n",i,info[i]->d_name);
  }

  /*
     Debes liberar la memoria que se ha pedido (directa o indirectamente)
     SIEMPRE
  */
  free_info_files_array(info,numero);

  return 0; // para indicar que no ha habido errores se devuelve un 0
}
