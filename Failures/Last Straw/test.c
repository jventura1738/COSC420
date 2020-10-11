#include<stdio.h>
#include "BigIntegerSingleFile.cpp"
#include<math.h>
/*
 * 1. gcc -c the .c files
 * 2. g++ -c the .cpp files
 * 3. g++ the .o's together into one executable
 */

int main(){

  BigInteger* cap = makeBigIntStr("100000000000000000000");
  BigInteger* one = makeBigIntStr("1");
  BigInteger* temp  = NULL;
  BigInteger* last = NULL;
  BigInteger* i = makeBigIntStr("1");
  int s;
  BigInteger* sq = NULL;
  BigInteger* finalSum = makeBigIntStr("0");
  BigInteger* sum = 0;
  BigInteger* ten = makeBigIntStr("10");
  BigInteger* zero = makeBigIntStr("0");
  for(i = makeBigIntStr("1"); c_lt(i,cap); c_pp(i)) { 
    sum = makeBigIntStr("0");;
    temp = i;
    while(c_gt(temp, zero)){
      last = c_mod(temp, ten);
      sum = c_add(sum, c_mult(last,last));
      temp = c_div(temp, ten);
    }
    
    s = c_is_perf_sq(sum);
    //printf("Sqrt: %d\n", s);
    if(s){
     finalSum = c_add(finalSum, i);
    }
    printf("i: %s Sum = %s\n", c_str(i), c_str(finalSum));
  }
  
  return 0;
}