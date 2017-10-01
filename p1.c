/*
If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
*/

#include <stdio.h>
#include <time.h>

#define TIMED_LOOPS 1000000

int main(int argc, char** argv) {
  int sum;
  clock_t start, end;
 
  start = clock();
  for (int j = 0; j < TIMED_LOOPS; j++) {
    sum = 0;
    
    for (int i = 0; i < 1000; i+=5)
      sum += i;

    for (int i = 0; i < 1000; i+=3) {
      if (i % 5 != 0)
        sum += i;
    }
  }
  end = clock();
  printf("approach 1 time = %f\tsum = %d\n", (end - start)/(double)CLOCKS_PER_SEC, sum);

  start = clock();
  for (int j = 0; j < TIMED_LOOPS; j++) {
    sum = 0;
    
    for (int i = 0; i < 1000; i+=5)
      sum += i;
    for (int i = 0; i < 1000; i+=3)
      sum += i;
    for (int i = 0; i < 1000; i+=15)
      sum -= i;
  }
  end = clock();
  printf("approach 2 time = %f\tsum = %d\n", (end - start)/(double)CLOCKS_PER_SEC, sum);

  return 0;
}
