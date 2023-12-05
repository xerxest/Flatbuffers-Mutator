#include <stdio.h>
#include <string.h>
#include <cassert>


int main(int argc, char *argv[]) {
  char str[6];
  fgets(str, sizeof(str), stdin);
  int zero = 0;

  if(str[1] == 'A')
  {
     assert(false);
  }

  return 0;
}