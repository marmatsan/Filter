/*******************************************************************

  Fichero     prueba_collection.c

  Resumen     Fichero para probar el módulo collection. 

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

#include "collection.h"

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main (int argc, char **argv){

  char *directorio;
  
#ifdef DEBUG
  printf("Depurando... Usando printf\n");
  // esto no es lo más recomendable. Usad gdb para depurar
#endif

  if (argc == 2){
    directorio = argv[1];
  } else{
    printf("Número argumentos incorrecto\n");
    printf("Llamada: %s nombreDirectorio\n",argv[0]);
    exit(1);
  }
  /*
    Nótese que my_collection es una variable definida en el módulo 
    Esto se ha hecho así para poder gestionar mejor las senhales
    del módulo senhal
   */
  int error;
  
  my_collection=initialize_collection();
  my_collection = add_all_directory(my_collection, directorio, &error);
  if (error){
    printf("An error happened (1): %s\n",get_error_msg_collection(error));
  }


  print_collection(my_collection);

  printf("Sort by size\n");
  my_collection = sort_collection(my_collection, compare_size);
  print_collection(my_collection);

  printf("Sort by id\n");
  my_collection = sort_collection(my_collection, compare_id);
  print_collection(my_collection);


  printf("Delete an item from the collection by id\n");
  my_collection = delete_item_id(my_collection, 2, &error);
  if (error)
    printf("An error happened (COLL): %s\n",get_error_msg_collection(error));

  print_collection(my_collection);

  printf("Attempting to delete the same id\n");
  my_collection = delete_item_id(my_collection, 2, &error);
  if (error)
    printf("An error happened (COLL): %s\n",get_error_msg_collection(error));

  printf("Print an item from the collection by id\n");
  print_item_id(my_collection, 3,&error);
  if (error)
    printf("An error happened (COLL): %s\n",get_error_msg_collection(error));


  /* 
     Debes liberar la memoria que se ha pedido (directa o indirectamente)
     SIEMPRE
  */
  
  my_collection = delete_collection(my_collection);
    
  return 0; // para indicar que no ha habido errores se devuelve un 0
}
