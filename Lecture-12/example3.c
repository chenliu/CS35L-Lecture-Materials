#include<stdio.h>

void function(int a, int b, int c) {
   int buffer1[2];
   int buffer2[4];
   int *ret;

   ret = buffer1 + 4;
   *ret = *ret + 8;
}

void main() {
  int x;

  x = 0;
  function(1,2,3);
  x = 1;
  printf("%d\n",x);
}

