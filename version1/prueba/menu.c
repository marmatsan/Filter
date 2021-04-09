#include <stdio.h>
#include "menu.h"
#include "input_program.h"
#include <string.h>
#include <stdlib.h>

void print_menu(){
  printf("%s\n","---------------------------------------");
  printf("%s","Management of a collection of files\n" );
  printf("%s\n","---------------------------------------");
  printf("%s\n","Select one of these different options:");
  printf("%s\n","1. Load a directory");
  printf("%s\n","2. Add a file to the collection");
  printf("%s\n","3. Delete a file from the collection");
  printf("%s\n","4. Short");
  printf("%s\n","5. Info about a file");
  printf("%s\n","6. Info of all files");
  printf("%s\n","7. Help");
  printf("%s\n","0. Exit program\n");
  printf("%s\n","If you enter CTRL+D in this menu, the program will exit in a controlled way.");
  printf("%s\n","If you enter CTRL+D in a submenu, the program will return to this menu.");
  printf("%s\n","If you enter CTRL+C at any moment, the program will exit in a controlled way");
  printf("%s\n","If you enter CTRL+Z the collection will be sorted by inode number");
  printf("%s\n","If you send SIGUSR1 to the program, the collection will be sorted by filename");
}

comandos_t ask_command(){
  comandos_t info;
  int option;
  int error;
  printf("%s","Please, enter an option (help: 7): ");
  option= get_number(10,&error);
  if (error){
    printf("An error happened: %s\n",get_error_msg_input(error));
  }else{
    info.comando=option;
    char *cadena = NULL;
    switch (option) {

      case LOAD_DIR:{
      printf("%s ","Please, enter a directory name to load:" );
      cadena= get_string(&error);
        if (error){
          printf("An error happened: %s\n",get_error_msg_input(error));
        }else{
          info.opcional.arg_opt_char=strdup(cadena);
          printf("String: %s\n",cadena );
        }
      break;
    }
      case ADD_FILE:
      printf("%s ","Please, enter a file name to load:" );
      cadena= get_string(&error);
        if (error){
          printf("An error happened: %s\n",get_error_msg_input(error));
        }else{
          info.opcional.arg_opt_char=strdup(cadena);
          printf("String: %s\n",cadena );
        }
      break;

      case DEL_FILE:{
      long identifier;
      printf("%s ","Please, enter an identifier to delete from the collection:" );
      identifier= get_number(10,&error);
        if (error){
          printf("An error happened: %s\n",get_error_msg_input(error));
        }else{
          info.opcional.arg_opt_long=identifier;
          printf("Identifier: %ld\n",identifier );
        }
      break;
    }
      case SORT:{
      int chosed;
      printf("%s ","Please, introduce the type of shorting (0: by id; 1: by filename; 2: by modification time; 3: by size; 4: by inode number):" );
      chosed= get_number(10,&error);
        if (error){
          printf("An error happened: %s\n",get_error_msg_input(error));
        }else{
          info.opcional.arg_opt_sort_t=chosed;
          printf("Chosed: %i\n",chosed );
        }
      break;
    }
      case INFO_FILE:{
        long identifier;
        printf("%s ","Please, enter a file identifier to show its information:" );
        identifier= get_number(10,&error);
          if (error){
            printf("An error happened: %s\n",get_error_msg_input(error));
          }else{
            info.opcional.arg_opt_long=identifier;
            printf("Identifier (for info): %ld\n",identifier );
          }

      break;
    }
      case INFO_ALL:{
        printf("%s\n","The collection will be listed" );
      break;
}
      case HELP:{
        printf("%s\n","Here is the information for help" );
      break;
}
      case EXIT:{
        printf("%s\n","The program will exit" );
      break;
    }
      default:
      printf("%s\n","The option must be between 0 and 7. Please, insert a valid option" );
    }
  }
  return info;
}

void clear_comando(comandos_t comando){
  if(comando.opcional.arg_opt_char!=NULL){
    free(comando.opcional.arg_opt_char);
    comando.opcional.arg_opt_char = NULL;
  }
}
