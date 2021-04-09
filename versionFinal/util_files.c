#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "util_files.h"

int info_file(char *path, char *filename, char **abs_filename, struct stat *bufStat){

  char *path_cpy= strdup(path);
  char *filename_cpy= strdup(filename);
  char dirAbs[PATH_MAX];

  realpath(path_cpy, dirAbs);
  strcat(dirAbs,"/");
  strcat(dirAbs, filename_cpy);

  *abs_filename=dirAbs; //Copies string dirAbs in string literal dirAbs in add_file

  if (lstat(dirAbs, bufStat) == -1){
    printf("An error happened: ");
  }

  free((char*)path_cpy);
  free((char*)filename_cpy);

  return errno;
}
