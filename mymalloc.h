#ifndef _MY_MALLOC_H
#define _MY_MALLOC_H
#include <stdio.h>
#include <stddef.h>

#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x)   myfree(x, __FILE__, __LINE__)

typedef struct metadata {
  size_t blockSize;
  char free;
  struct metadata*next;
} Metadata;

static char memoryBlock[4096]={3};
void *mymalloc(size_t resquestedSize, const char *File,int lineNumber);
void myfree(void * memory,const char *File,int lineNumber);
void nodeCreator();
void combineFreeSpace();
#endif
