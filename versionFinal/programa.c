#include <stdio.h>
#include "collection.h"
#include "menu.h"
#include "directorio.h"
#include "input_program.h"
#include "item.h"
#include "senhal.h"
#include "util_files.h"


int main(int argc, char const *argv[]) {
  int error;

  inicialize_signal_handlers();
  my_collection=initialize_collection();
  print_menu();
  comandos_t comando;
  comando.comando=HELP;

while (comando.comando!=EXIT) {
  comando = ask_command();

  switch(comando.comando){

  case LOAD_DIR:

    my_collection = add_all_directory(my_collection,comando.opcional.arg_opt_char,&error);

    break;

  case ADD_FILE:

    my_collection = add_file(my_collection,".",comando.opcional.arg_opt_char ,&error);

    break;

  case DEL_FILE:

    my_collection = delete_item_id(my_collection,comando.opcional.arg_opt_long, &error);

    break;

  case SORT:
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

    break;
  case INFO_FILE:

    print_item_id(my_collection, comando.opcional.arg_opt_long,&error);

    break;
  case INFO_ALL:

    print_collection(my_collection);

    break;
  case HELP:
      print_help();
    break;

  case EXIT:

    break;

  }
  clear_comando(comando);
}
  clean_module_input_program();
  clean_module_collection();
  delete_collection(my_collection);
  return 0;

}
