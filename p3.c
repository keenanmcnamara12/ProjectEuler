/*
 The prime factors of 13195 are 5, 7, 13 and 29.

 What is the largest prime factor of the number 600851475143 ?
*/

#include <stdio.h>

int main(int argc, char** argv) {
  long long num = 600851475143LL;
  long long largFact = 0;
  int count = 2;

  while ( count * count <= num ) {
    if (num % count == 0) {
        num = num / count;
        largFact = count;
    } else {
        count++;
    }
  }
  if (num > largFact)
    largFact = num;

  printf("largest factor of 600851475143 is %lld\n", num);
  return 0;
}
