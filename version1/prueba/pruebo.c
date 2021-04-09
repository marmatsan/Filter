#include <stdio.h>
#include "menu.h"
#include "input_program.h"

int main(){
  comandos_t comando;
  print_menu();
  comando= ask_command();
  return 0;
}
