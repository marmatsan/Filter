#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include "directorio.h"
#include "collection.h"

int info_all_files_dir(char *path, struct dirent ***info_files, int *error){
  int num_files=0;
  char dirAbs[PATH_MAX];
  char *path_cpy=(char*)malloc(sizeof(path));

  strcpy(path_cpy,path);

  realpath(path_cpy,dirAbs);

  num_files=scandir(dirAbs,info_files,NULL,NULL);

  free(path_cpy);

  return num_files;

}

void free_info_files_array( struct dirent **info_files, int n){
  int i;
  for ( i = 0; i < n; i++) {
    free(info_files[i]);
  }
  free(info_files);
}
