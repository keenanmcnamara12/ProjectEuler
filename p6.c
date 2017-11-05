/*The sum of the squares of the first ten natural numbers is,

    1^2 + 2^2 + ... + 10^2 = 385
    The square of the sum of the first ten natural numbers is,

    (1 + 2 + ... + 10)^2 = 55^2 = 3025
    Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

    Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.*/

#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
  int number = 100; 
  int sumOfSquare = 0;
  int squareofSum = 0;

  for (int i = 1; i <= number; i++) {
    sumOfSquare += pow(i, 2); 
    squareofSum += i;
  }
  squareofSum = pow(squareofSum, 2);

  printf("diff = %d\n", squareofSum - sumOfSquare);

  return 0;
}
