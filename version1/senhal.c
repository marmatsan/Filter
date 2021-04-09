#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "input_program.h"
#include "collection.h"
#include "item.h"

void signal_handlers(int senhal){

  if (senhal==SIGINT) { // ctrl+C
    printf("\n%s", "\nCTRL+C pressed: The program will exit\n");
    clean_module_input_program();
    clean_module_collection();
    exit(0);
  }

  if (senhal==SIGTSTP) { // ctrl+Z
    printf("\n%s","\nCTRL+Z pressed: The collection will be shorted by inode number\n");
    my_collection=sort_collection(my_collection,compare_inode);
  }

  if (senhal==SIGUSR1) {
    printf("%s\n","\nSIGUSR1 received: The collection will be shorted by file name\n");
    my_collection= sort_collection(my_collection,compare_filename);
  }

}

void inicialize_signal_handlers(){
  signal(SIGINT,signal_handlers);
  signal(SIGTSTP, signal_handlers);
  signal(SIGUSR1,signal_handlers);
}
