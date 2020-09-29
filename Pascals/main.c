#include <stdio.h>

int C(int n, int k) {
  double res = 1;
  int i;
  for(i = 1; i <=k; ++i){
    res = res * (n - k + i) / i;
  }
  return (int)(res + 0.01);
}

int main(){
  printf("%d\n", C(5, 2));
  return 0;
}
