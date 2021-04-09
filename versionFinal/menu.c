#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "input_program.h"


void print_menu(){
  printf("%s\n","---------------------------------------");
  printf("%s","Management of a collection of files\n" );
  printf("%s\n","---------------------------------------");
  printf("%s\n","Select one of these different options:");
  printf("%s\n","1. Load a directory");
  printf("%s\n","2. Add a file to the collection");
  printf("%s\n","3. Delete a file from the collection");
  printf("%s\n","4. Sort");
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
  info.comando=EXIT;
  info.opcional.arg_opt_char=NULL;
  int option= -1;
  int error = -1;

  long identifier;
  int chosed;
  char *cadena = NULL;

  while (error) { //error!=0;

    printf("%s","Please, enter an option (help: 7): ");
    option= get_number(10,&error);
    if (error) {
      if (error==ERR_CTRLD_INPUT) {
        printf("%s\n",get_error_msg_input(error));
        info.comando=EXIT;
        error=0;
      }
    }else{
      info.comando=option;
    }
  switch (info.comando) {

    case LOAD_DIR:
    printf("%s ","Please, enter a directory name to load:" );
    cadena= get_string(&error);
      if (error){
        printf("An error happened: %s\n",get_error_msg_input(error));
      }else{
        info.opcional.arg_opt_char=strdup(cadena);
      }
    break;

    case ADD_FILE:
    printf("%s ","Please, enter a file name to add to the collection:" );
    cadena= get_string(&error);
      if (error){
        printf("An error happened: %s\n",get_error_msg_input(error));
      }else{
        info.opcional.arg_opt_char=strdup(cadena);
      }
    break;

    case DEL_FILE:
    printf("%s ","Please, enter an identifier to delete from the collection:" );
    identifier= get_number(10,&error);
      if (error){
        printf("An error happened: %s\n",get_error_msg_input(error));
      }else{
        info.opcional.arg_opt_long=identifier;
      }
    break;

    case SORT:
    printf("%s ","Please, introduce the type of shorting (0: by id; 1: by filename; 2: by modification time; 3: by size; 4: by inode number):" );
    chosed= get_number(10,&error);
      if (error){
        printf("An error happened: %s\n",get_error_msg_input(error));
      }else{
        info.opcional.arg_opt_sort_t=chosed;
      }
    break;

    case INFO_FILE:
      printf("%s ","Please, enter a file identifier to show its information:" );
      identifier= get_number(10,&error);
        if (error){
          printf("An error happened: %s\n",get_error_msg_input(error));
        }else{
          info.opcional.arg_opt_long=identifier;
        }

    break;

    case INFO_ALL:

    break;

    case HELP:

    break;

    case EXIT:

    break;

    default:
    printf("%s\n","The option must be between 0 and 7. Please, insert a valid option" );

    }
  }
  return info;
}

void clear_comando(comandos_t comando){
  if (comando.comando==LOAD_DIR || comando.comando== ADD_FILE) {
    if(comando.opcional.arg_opt_char!=NULL){
      free(comando.opcional.arg_opt_char);
      comando.opcional.arg_opt_char=NULL;
    }
  }
}

void print_help(){
printf("\n");
printf("%-30s\n","---------------------------------------------" );
printf("%s\n","Management of a collection of files by:");
printf("%s\n",">>>>>>>> Elena Herrero Zamora    100346783" );
printf("%s\n",">>>>>>>> Martín Mateos Sánchez   100346871" );
printf("%-30s\n","---------------------------------------------" );
printf("%s\n","This application allows to manage a collection of files that you have to include manually by yourself with the help of this short guide.");
printf("%s\n","After the files have been added to your collection, this program includes a set of functionalities. You will be asked" );
printf("%s\n","for a functionality from 0 to 7, despite 0 will be to exit the program. The functionalities are listed below:");
printf("\n");
printf("%s\n","1. Load a directory: Given a name of a directory (a folder) it will include in your collection all the files that are within" );
printf("%s\n","it, and every file will get a unique identifier. If you want to add the files in the directory you are running the program," );
printf("%s\n","insert '.' ");
printf("\n");
printf("%s\n","2. Add a file to the collection: This option will add a file to the collection from the folder you are running the program,");
printf("%s\n","specifying its name and extension (if you want to add a file which is a text file called 'name' you have to write name.txt");
printf("%s\n","to include it).");
printf("\n");
printf("%s\n","3. Delete a file from the collection: Given an identifier (ID) from the collection, it will erease it from your collection,");
printf("%s\n","but no from your computer. We recommend you to use the option '6' to know the identifiers of the files of your collection" );
printf("%s\n","in order to erease the desired one.");
printf("\n");
printf("%s\n", "4. Sort: This option allows you to sort your collection in 4 ways; by ID, by filename (alphabetically), by modification time");
printf("%s\n","(from oldest to newest), by size (from smaller to biggest) and by inode number (from smallest to bigest). Note: an inode number");
printf("%s\n","is an identifier of a file but this time the OS assign one to each file of a computer.");
printf("\n");
printf("%s\n","5. Info about a file: Given an identifier (ID) of a file, it will print its information.");
printf("\n");
printf("%s\n","6. Info of all files: This option will print the information of all the files from the collection.");
printf("\n");
printf("%s\n","7. Help: Displays this menu." );
printf("\n");
printf("%s\n","0. Exit program: The program exit in a controlled way.");
printf("\n");
printf("%s\n","Also, by pressing the sortcuts listed above (CTRL+D,CTRL+C and CTRL+Z) the functionalities explained are provided.");
printf("\n");

}
