/*By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?*/

#include <stdio.h>

int isPrime(int number) {
  if (number % 2 == 0)
    return 0;

  int testNum = number / 2;
  if (testNum % 2 == 0)
    testNum--;

  while (testNum > 1) {
    if (number % testNum == 0)
      return 0;
    testNum -= 2;
  }
  return 1;
}

int main(int argc, char** argv) {
  int number = 10001;
  int count = 0;
  int i = 0;
  int lastPrime = 0;
  while (count < number) {
    if (isPrime(i) == 1) {
      lastPrime = i;
      count++;
    }
    i++;
  }
  printf("the %d's prime is %d\n", number, lastPrime);
  
  return 0;
}
