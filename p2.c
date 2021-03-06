/*
 Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms will be:
 
 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
 
 By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
*/

#include <stdio.h>
#include <time.h>

#define TIMED_LOOPS 100000000

int fibEvenSum(int n);
int fibEvenSumRecur(int n);
int fibEvenSumRecurCore(int n, int sum, int num1, int num2);

int main(int argc, char** argv) {
  int sum, sumRecur;
  clock_t start, end, startRecur, endRecur;

  for (int j = 100; j < TIMED_LOOPS; j *= 10) {
    // non recursive approach
    start = clock();
    for (int i = 0; i < j; i++) {
      sum = fibEvenSum(4000000);
    }
    end = clock();

    // recursive approach
    startRecur = clock();
    for (int i = 0; i < j; i++) {
      sumRecur = fibEvenSumRecur(4000000);  
    }
    endRecur = clock();

    // display results
    printf("non-recursive approach time = %f\tsum = %d\n", 
          (end - start)/(double)CLOCKS_PER_SEC, sum);
    printf("recursive approach time = %f\tsum = %d\n", 
          (endRecur - startRecur)/(double)CLOCKS_PER_SEC, sumRecur);
    if ((end - start) < (endRecur - startRecur))
      printf("winner %d iterations: non-recursive\n", j);
    else
      printf("winner %d interations: recursive\n\n", j);
    }
  return 0;
}

int fibEvenSum(int n) {
    int sum = 0;
    int num1 = 1;
    int num2 = 2;
    int tmp;
    while (num2 < n) {
      if (num2 % 2 == 0)
        sum += num2;
      tmp = num2;
      num2 = num1 + num2;
      num1 = tmp;
    } 
  return sum;
}

int fibEvenSumRecur(int n) {
  return fibEvenSumRecurCore(n, 0, 1, 2);
}

int fibEvenSumRecurCore(int n, int sum, int num1, int num2){
  if (num2 > n)
    return sum;
  if (num2 % 2 == 0)
    sum += num2;
  return fibEvenSumRecurCore(n, sum, num2, num1 + num2);
}
