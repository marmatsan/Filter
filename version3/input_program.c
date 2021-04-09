#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "input_program.h"

#define NUM_INPUT_ERROR_MSGS 4

static const char *error_map[NUM_INPUT_ERROR_MSGS +1] =
  {
    "Success",
    "No digits were found",
    "Further characters after number",
    "CTRL+D was pressed (EOF)",
    "Unknown error"
  };

  char *cadena = NULL;
  size_t number_alloc=0;

void clean_module_input_program(){
  if (cadena!=NULL) {
    free(cadena);
    cadena= NULL;
    number_alloc=0;
  }
}

const char *get_error_msg_input(int error){
  if (error<=0) {
    if (-error<NUM_INPUT_ERROR_MSGS) {
      return error_map[-error];
    }else{
      return error_map[4];
    }
  }else{
    return strerror(error);
  }
}

char *get_string(int *error){
  if (getline(&cadena,&number_alloc,stdin)==-1) {
    if (errno!=0) {
      *error= errno;
    }else{
      if (feof(stdin)) {
        *error=ERR_CTRLD_INPUT;
      }else{
        *error=-NUM_INPUT_ERROR_MSGS;
      }
    }
    return NULL;
  }else{
    if (cadena[0]=='\n') {
      *error=ERR_NO_NUMBERS_INPUT;
      return NULL;
    }else{
      *error=SUCCESS_INPUT;
      cadena[strlen(cadena)-1] = '\0';
      return cadena;
    }
  }
}

long get_number(int base, int *error){
  long input=-1;
  char *string_part=NULL;
  cadena= get_string(error);
  if (cadena!=NULL) {
    input=strtol(cadena,&string_part,base);
  }
    return input;
}
