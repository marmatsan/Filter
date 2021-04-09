/*******************************************************************

  Fichero     menu.h

  Resumen     Módulo para la gestión de los menús con el usuario

  Descripción Módulo para la gestión de los menús con el usuario. 

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
#ifndef MENU_H
#define MENU_H

/*---------------------------------------------------------------------------*/
/* Declaración de tipos                                                      */
/*---------------------------------------------------------------------------*/

enum comandos_type{EXIT, LOAD_DIR, ADD_FILE, DEL_FILE, SORT, INFO_FILE,INFO_ALL, HELP};

enum sort_type{SORT_ID, SORT_NAME, SORT_LAST_MODIFIED,SORT_SIZE,SORT_INODE};

/*---------------------------------------------------------------------------*/
/* Declaración de estructuras                                                */
/*---------------------------------------------------------------------------*/

union opcional_t{
  char *arg_opt_char;
  long arg_opt_long;
  enum sort_type arg_opt_sort_t;
};

struct comandos{
  enum comandos_type comando;
  union opcional_t opcional;
};

typedef struct comandos comandos_t;

/*****************************************************************************

  Resumen      Imprime el menú

******************************************************************************/
void print_menu();

/*****************************************************************************

  Resumen      Entrada de una opción válida por parte del usuario

  Descripción  Espera la entrada de una opción válida por parte del usuario.
               Devuelve el comando introducido y su parámetro opcional si 
               lo hubiere en una estructura de tipo comandos_t. 

  Efec. Colat. Si el comando tiene como parámetro opcional una cadena y 
               sólo en ese caso, se crea una cadena en el módulo que 
               deberá ser liberada llamando a la función clear_comando nada
               más terminar de usar el parámetro devuelto.

  Ver también  clear_comando

******************************************************************************/
comandos_t ask_command();

/*****************************************************************************

  Resumen      Libera la cadena de parámetros generada al usar ask_command

  Ver también  ask_command

******************************************************************************/
void clear_comando(comandos_t comando);

/* 
   Os copio también los prototipos de las funciones internas al módulo usadas
   por las otras funciones.
   Al ser internas NO deben ser declaradas en el .h
   
   comandos_t ask_char_opt(char *msg, enum comandos_type cte_comando, int *opt_desired);
   comandos_t ask_long_opt(char *msg, enum comandos_type cte_comando, int *opt_desired);

   IMPORTANTE: aunque yo he usado estas funciones internamente NO es obligatorio
   implementarlas, podéis implementar otras. Lo importante es que ask_command funcione como debe

*/

#endif
