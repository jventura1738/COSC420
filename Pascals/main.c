#include <stddef.h>
#include <stdio.h>

size_t C(size_t n, size_t k) {
  size_t res = 1;
  size_t i;
  for(i = 1; i <=k; ++i){
    res = res * (n - k + i) / i;
  }
  return (size_t)(res + 0.01);
}

int main(){
  size_t i, j;
  size_t n = 1000000000;
  size_t count = 0;
  for(i = 0; i < n; i++){
    for(j = 0; j <= i; j++){
      printf("%ld\n", i);
      if (C(i, j) % 7 != 0){
        //printf("%ld\n", C(i,j));
	count += 1;
      }
    }
    printf("%ld", count);
    puts("");
  }
  return 0;
}
