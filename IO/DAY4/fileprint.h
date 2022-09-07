#ifndef __FILEPRINTF_H
#define __FILEPRINTF_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

void file_print(struct stat F);
void rwx(struct stat F);
void hard_link_num(struct stat F);
int group_id(struct stat F);
int user_id(struct stat F);
void file_size(struct stat F);
void time_print(struct stat F);
void get_file_type(struct stat F);

void file_name_print(struct dirent *s);
#endif
