#include<stdio.h>
#include "BigIntegerSingleFile.cpp"
#include<math.h>
/*
 * 1. gcc -c the .c files
 * 2. g++ -c the .cpp files
 * 3. g++ the .o's together into one executable
 */

int main(){

  BigInteger* M = makeBigIntStr("1");
  BigInteger* n = makeBigIntStr("0");
  BigInteger* two = makeBigIntStr("2");
  BigInteger* N = makeBigIntStr("10000");
  BigInteger* x = NULL;
  BigInteger* y = NULL;
  BigInteger* count = makeBigIntStr("0");

  for(x = makeBigIntStr("101");  c_leeq(x, N); c_pp(x)){
    for(y = makeBigIntStr("101");  c_leeq(y, N); c_pp(y)){
      //printf("Count: %d\n", c_neq(c_mod(c_div(c_mult(y,y), c_mult(x,x)), two), n));
      if(c_neq(c_mod(c_div(c_mult(y,y), c_mult(x,x)), two), n)){
        c_pp(count);
      }
    }
  }
  printf("Count: %s\n", c_str(count));
return 0;
}

