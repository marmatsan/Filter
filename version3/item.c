#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include "item.h"

struct item create_item(char *path, char *filename, char *abs_filename, struct stat info, int *error){
  struct item item;

  char *buf =NULL;
  char *buff_cpy;
  char *path_cpy= strdup(path);
  char *filename_cpy=strdup(filename);
  /*
  if (!filename_cpy) {
    printf("%s\n","Is null" );
    exit(1);
  }
  */
  char *abs_filename_cpy= strdup(abs_filename);

  lstat(filename_cpy,&info);

  if (S_ISLNK(info.st_mode)) {
    readlink(filename_cpy,buf,sizeof(buf));
    buff_cpy= strdup(buf);
    item.data.target_filename=buff_cpy;
  }else{
    item.data.target_filename= NULL;
  }

  item.data.path=path_cpy;
  item.data.filename=filename_cpy;
  item.data.abs_filename=abs_filename_cpy;
  item.data.st_ino= info.st_ino;
  item.data.st_size=info.st_size;
  item.data.st_nlink=info.st_nlink;
  item.data.st_mtime= info.st_mtime;
  item.data.st_mode=info.st_mode;

  struct passwd *pwd;
  struct group *grp;

  item.data.owner= info.st_uid;
  item.data.group=info.st_gid;

  pwd = getpwuid(item.data.owner); //user
  grp = getgrgid(item.data.group); //group

  item.data.owner_name= pwd->pw_name;
  item.data.group_name= grp->gr_name;
  free(abs_filename_cpy);
  return item;
}

void free_item(struct item *item){
  if (item->data.target_filename!=NULL) {
  free(item->data.target_filename);
  }
  free(item->data.path);
  free(item->data.filename);

}

void print_item(struct item foo){
  size_t date_size=40;
  char date[date_size];

  strftime(date, date_size, "%a %b %d %Y %T", localtime(&(foo.data.st_mtime)));
  printf("[%i]\t\t",foo.id);
  printf("%lu\t\t",foo.data.st_ino);
  printf("\t");
  printf( (S_ISDIR(foo.data.st_mode)) ? "d" : "-");
  printf( (foo.data.st_mode & S_IRUSR) ? "r" : "-");
  printf( (foo.data.st_mode & S_IWUSR) ? "w" : "-");
  printf( (foo.data.st_mode & S_IXUSR) ? "x" : "-");
  printf( (foo.data.st_mode & S_IRGRP) ? "r" : "-");
  printf( (foo.data.st_mode & S_IWGRP) ? "w" : "-");
  printf( (foo.data.st_mode & S_IXGRP) ? "x" : "-");
  printf( (foo.data.st_mode & S_IROTH) ? "r" : "-");
  printf( (foo.data.st_mode & S_IWOTH) ? "w" : "-");
  printf( (foo.data.st_mode & S_IXOTH) ? "x" : "-");
  printf("\t\t");
  printf("%lu ",foo.data.st_nlink);
  printf("%s  ",foo.data.owner_name );
  printf("%s\t\t",foo.data.group_name );
  printf("%lu\t\t",foo.data.st_size );
  printf("%s\t ",date );
  printf("%s\n",foo.data.filename);

}

int compare_id(const void *p, const void *q){
  struct item *e1= (struct item *)p;
  struct item *e2= (struct item *)q;

  return e1->id - e2->id;
}

int compare_filename(const void *p, const void *q){
  struct item *e1= (struct item *)p;
  struct item *e2= (struct item *)q;

  return strcmp(e1->data.filename, e2->data.filename);
}

int compare_last_modified(const void *p, const void *q){
  struct item *e1= (struct item *)p;
  struct item *e2= (struct item *)q;

  return e1->data.st_mtime - e2->data.st_mtime;
}

int compare_size(const void *p, const void *q){
  struct item *e1= (struct item *)p;
  struct item *e2= (struct item *)q;

  return e1->data.st_size - e2->data.st_size;
}

int compare_inode(const void *pa, const void *pb){
  struct item *e1= (struct item *)pa;
  struct item *e2= (struct item *)pb;

  return e1->data.st_ino - e2->data.st_ino;
}
