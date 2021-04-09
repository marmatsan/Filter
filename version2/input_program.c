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
  }
  if (error>0) {
    return strerror(error);
  }
  return error_map[4];
}

char *get_string(int *error){
  if (getline(&cadena,&number_alloc,stdin)==-1) {
    if (errno!=0) {
      printf("%s\n","An error ocurred" );
      *error= errno;
      return NULL;
    }
    /*else{
      *error=ERR_CTRLD_INPUT;
      printf("%s\n","ctrl+D pressed" );
      return cadena;
    }
    */
  }else{
  *error=0;
  cadena[strlen(cadena)-1] = '\0';
  return cadena;
  }
  return cadena;
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
