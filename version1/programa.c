#include <stdio.h>
#include "collection.h"
#include "menu.h"
#include "directorio.h"
#include "input_program.h"
#include "item.h"
#include "senhal.h"
#include "util_files.h"
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  inicialize_signal_handlers();
  my_collection=initialize_collection();
  print_menu();
  comandos_t comando;

while (comando.comando!=EXIT) {
  comando= ask_command();

  switch(comando.comando){

  case LOAD_DIR:
    printf("LOAD DIR introduced\n");
    printf("Parameters: %s\n", comando.opcional.arg_opt_char);
    clear_comando(comando);

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
    clear_comando(comando);
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

}
  clean_module_input_program();

   // esto es importante para eliminar de la memoria dinámica las cadenas
  clean_module_collection();
  return 0;

}
