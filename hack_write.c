#define write ye_olde_write
#include <stdio.h>

#include <dlfcn.h>

#undef write

/* SOURCE: http://deathray.us/code/color_output.html */

static const char COL_RESET[] = "\x1b[0m";

/*  Foreground colors are in form of 3x, bacground are 4x */
static const char RED[]     = "\x1b[31m";
static const char GREEN[]   = "\x1b[32m";
static const char YELLOW[]  = "\x1b[33m";
static const char BLUE[]    = "\x1b[34m";
static const char MAGENTA[] = "\x1b[35m";
static const char CYAN[]    = "\x1b[36m";

/* Not including background colors for no good reason */

int write(int fd, const void*buf, size_t count) {
  
  void * libc = dlopen("/lib/libc.so.6", RTLD_LAZY); /* never closed, rofl */
  int (*lol_write) (int, const void*, int);
  *(void **) (&lol_write) = dlsym(libc, "write");
  
  if (fd  == 1) {
    (*lol_write)(fd, RED, sizeof(RED));
  } else if (fd == 2) {
    (*lol_write)(fd, BLUE, sizeof(BLUE));
  }

  /* always actually do the write() */
  (*lol_write)(fd, buf, count);
  
  if ( (fd == 1) ||
       (fd == 2 )) {
    (*lol_write)(fd, COL_RESET, sizeof(COL_RESET));
  }
  
}
