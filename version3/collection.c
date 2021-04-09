#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "collection.h"
#include "util_files.h"
#include "item.h"
#include "directorio.h"

#define INI_SIZE 20
#define SUCCESS_INPUT 0
#define ERR_NO_COLLECTION -1
#define ERR_NO_FREE_SPACE_COLLECTION -2
#define ERR_ELEMENT_ALREADY_COLL -3
#define MORE_FILES_THAN_SPACE -4
#define FILE_DOES_NOT_EXIST -5
#define ELEMENT_NOT_FOUND -6

#define NUM_COLLECTION_ERROR_MSGS 7

static const char *error_map_coll[NUM_COLLECTION_ERROR_MSGS] =
  {
    "Success",
    "No elements within the collection",
    "Total Capacity Reached",
    "Element already in the collection",
    "There were more files than space in the collection",
    "File does not exist",
    "Element not found"
  };

struct collection my_collection;
int identifier=0;

const char *get_error_msg_collection(int error){
  if (error<=0) {
    if (-error<NUM_COLLECTION_ERROR_MSGS) {
      return error_map_coll[-error];
    }else{
      return strerror(error);
    }
  }else{
    return strerror(error);
  }
}

struct collection initialize_collection(){
  struct collection my_collection;
  my_collection.total_capacity=INI_SIZE;
  my_collection.number_occupied=0;
  my_collection.tabla = (struct item*) malloc(sizeof(struct item)*(my_collection.total_capacity));
  return my_collection;
}

void clean_module_collection(){
  int i;
  for (i = 0; i < my_collection.number_occupied; i++) {
    free_item(&my_collection.tabla[i]);
  }
  free(my_collection.tabla);
}

struct collection add_file(struct collection my_collection, char *path, char *nombre, int *error){
  struct stat bufStat;
  char *dirAbs=NULL;
  int error_file=info_file(path,nombre,&dirAbs,&bufStat);

  if (error_file!=0) {
    printf("Error: %s\n",get_error_msg_collection(error_file));
    return my_collection;
  }

  if(my_collection.number_occupied==my_collection.total_capacity){

      my_collection.tabla= (struct item*) realloc(my_collection.tabla, sizeof(struct item)*(my_collection.total_capacity)*2);

      my_collection.total_capacity = my_collection.total_capacity*2;

  }

  int i=0;

  for(i=0; i<my_collection.number_occupied; i++){
    if(strcmp(my_collection.tabla[i].data.filename,nombre)==0){
      *error= ERR_ELEMENT_ALREADY_COLL;
      printf("Element id: [%i] %s\n",i,get_error_msg_collection(*error));
      return my_collection;
    }
  }

  struct item item= create_item(path,nombre, dirAbs, bufStat, &error_file);

  item.id=identifier;
  identifier++;
  my_collection.tabla[my_collection.number_occupied]=item;
  my_collection.number_occupied++;
  printf("The file %s has been added to the collection\n",nombre);
  return my_collection;
}

struct collection add_all_directory(struct collection my_collection,char *path, int *error){

struct dirent **ptr = NULL;

 int all_files_num= info_all_files_dir(path, &ptr, error);

 if (all_files_num<=0) {
   printf("Error: %s\n",get_error_msg_collection(*error));
  return my_collection;
 }

  int i;

  for(i=0;i<all_files_num;i++){
    my_collection= add_file(my_collection,path,ptr[i]->d_name,error);
  }
  free_info_files_array(ptr,all_files_num);
  return my_collection;
}


struct collection delete_item_id(struct collection my_collection, int id, int *errnum){
  int i=0;
  int j=0;

  for (i = 0; i < my_collection.number_occupied; i++) {
    if (my_collection.tabla[i].id==id) {
      free_item(&my_collection.tabla[i]);
      for ( j=i; j < my_collection.number_occupied-1; j++) {
        my_collection.tabla[j] = my_collection.tabla[j+1];
      }
      my_collection.number_occupied--;
      return my_collection;
    }
  }
  *errnum=ELEMENT_NOT_FOUND;
  printf("Error: %s\n",get_error_msg_collection(*errnum));
return my_collection;
}

struct collection delete_collection(struct collection my_collection){
  my_collection=initialize_collection();
  free(my_collection.tabla);
  return my_collection;
}

struct collection sort_collection(struct collection my_collection, int (*compare)(const void *, const void *)){
  if (my_collection.number_occupied==0) {
    printf("Error: %s\n",get_error_msg_collection(ERR_NO_COLLECTION));
  }else{
 qsort(my_collection.tabla, my_collection.number_occupied, sizeof(struct item), compare);
 printf("Collection sorted with the option chosed\n");
 }
 return my_collection;
}

void print_item_id(struct collection my_collection, int id, int *errnum){
  if (my_collection.number_occupied==0) {
    *errnum=ERR_NO_COLLECTION;
    printf("Error: %s\n",get_error_msg_collection(*errnum));
  }else{
    int i;
    int checked=0;
    for (i = 0; i < my_collection.number_occupied; i++) {
      if (my_collection.tabla[i].id==id) {
          printf("%-13s %-26s %-10s  %-11s  %-6s  %-20s  %-18s  %-27s  %s\n","ID","Inode number","Permits","Hard Links","Owner","Group","Size","Modification Time","Name");
          printf("\n");
          print_item(my_collection.tabla[i]);
          checked=1;
      }
    }
    if (checked!=1) {
      *errnum=ELEMENT_NOT_FOUND;
      printf("Error: %s\n",get_error_msg_collection(*errnum));
    }
  }
}

void print_collection(struct collection my_collection){
  int i=0;
  if (my_collection.number_occupied==0) {
    printf("%s\n",get_error_msg_collection(ERR_NO_COLLECTION));
  }else{
    printf("%-13s %-26s %-10s  %-11s  %-6s  %-20s  %-18s  %-27s  %s\n","ID","Inode number","Permits","Hard Links","Owner","Group","Size","Modification Time","Name");
    printf("\n");
    for (i = 0; i < my_collection.number_occupied; i++) {
      print_item(my_collection.tabla[i]);
    }
  }
}
