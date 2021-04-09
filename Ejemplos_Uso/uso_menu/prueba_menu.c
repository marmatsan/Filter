/*******************************************************************

  Fichero     prueba_menu.c

  Resumen     Fichero para probar el módulo menu.

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

#include "menu.h"
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

  print_menu();

  comandos_t comando;

  /* Este es el ejemplo que debéis usar para implementar (añadiendo cosas)
     vuestro programa.c
     en programa.c deberéis, además, inicializar las señales y la colección
     y al finalizar borrar lo que fuere menester
  */

  /* Nótese que en este ejemplo sólo se pregunta una vez
     En el programa (este código deberá ir en programa.c) deberéis hacer un bucle
     Hasta que el usuario introduzca un CTRL+D o un 0
     (en ambos casos ask_command devuelve EXIT en comando.comando)
     Podéis comprobar también que la función ask_command no vuelve
     hasta que se presiona CTRL+D o un 0

     En este ejemplo de prueba la señal CTRL+C no es capturada
     para eso, deberéis inicializar el módulo de las señales
     usando las funciones del módulo senhal
  */


  comando = ask_command();

  switch(comando.comando){

  case LOAD_DIR:
    printf("LOAD DIR introduced\n");
    printf("Parameters: %s\n", comando.opcional.arg_opt_char);

    /*
       Aquí deberás usar en tu programa la función add_all_directory,
    */

    /*Ejemplo de uso (comprueba también el archivo prueba_collection.c):
      my_collection = add_all_directory(my_collection,
      comando.opcional.arg_opt_char,
      &error);
     */
    break;
  case ADD_FILE:
    printf("ADD FILE introduced\n");
    printf("Parameters: %s\n", comando.opcional.arg_opt_char);
    /* Aquí deberás usar en tu programa la función add_file,
       en collection.h tienes el prototipo de la función */

    /* Ejemplo de uso:
    my_collection = add_file(my_collection, comando.opcional.arg_opt_char,
			     &error);
    */
    break;
  case DEL_FILE:
    printf("DEL FILE introduced\n");
    printf("Parameters: %ld\n", comando.opcional.arg_opt_long);
    /* Ejemplo de uso:
    my_collection = delete_item_id(my_collection,
                                   comando.opcional.arg_opt_long, &error);
    */
    break;

  case SORT:
    printf("SORT introduced: \n");
    printf("Parameters: %d\n", comando.opcional.arg_opt_sort_t);
    /* Ejemplo de uso
    switch(comando.opcional.arg_opt_sort_t){
    case SORT_ID:
      my_collection = sort_collection(my_collection, compare_id);
      break;
    case SORT_NAME:
      my_collection = sort_collection(my_collection, compare_filename);
      break;
    case SORT_LAST_MODIFIED:
      my_collection = sort_collection(my_collection, compare_last_modified);
      break;
    case SORT_SIZE:
      my_collection = sort_collection(my_collection, compare_size);
      break;
    case SORT_INODE:
      my_collection = sort_collection(my_collection, compare_inode);
      break;

    default:
      printf("No sorting criteria\n");
    }
    */

    break;
  case INFO_FILE:
    printf("INFO FILE introduced\n");
    printf("Parameters: %ld\n", comando.opcional.arg_opt_long);
    /* Ejemplo de uso
    print_item_id(my_collection, comando.opcional.arg_opt_long,&error);
    */
    break;
  case INFO_ALL:
    printf("INFO ALL introduced\n");
    /*
      Ejemplo de uso
    print_collection(my_collection);
    */
    break;
  case HELP:
    printf("HELP introduced\n");
    /*
      Ejemplo de uso
      print_menu();
    */
    break;
  case EXIT:
    printf("EXIT introduced\n");
    break;
  }
  clear_comando(comando);
  clean_module_input_program(); // esto es importante para eliminar de la memoria dinámica las cadenas

  return 0; // para indicar que no ha habido errores se devuelve un 0
}
