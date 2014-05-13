#include <stdio.h>
#include "add.h"

int main (int argc, char *argv[]) {
  if (argc < 2) {
    printf("need param\n");
  } else {
    printf("param is %s\n", argv[1]);
  }
  #ifdef VERSION
    printf("verison define\n");
  #endif
  int result = add(1,3);
  printf("result : %d\n",result);
  return 0;
}
