/* A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers. */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

int isPalindrome(int num);
int palindromeCreate2();
int palindromeCreate();

int main(int argc, char** argv) {
  // int num = atoi(argv[1]);  // perfect users don't need validation
  // printf("isPalindrome = %d\n", isPalindrome(num));
  
  // somewhat brutish (not sure if palindrome generating and factoring
  // would be more efficient or not).
  int num1 = 0;
  int num2 = 0;
  int curProd = 0;
  int maxProd = 0;
  int foundLargerPossible = 0;
  clock_t start, end;

  start = clock();
  int i, j;
  for (i = 999; i > 0; i--) {
    for (j = 999; j > 0; j--) {
      curProd = i * j;
      if (isPalindrome(curProd) && curProd > maxProd) {
        num1 = i;
        num2 = j;
        maxProd = curProd; 
      }
      // at some point can't make a product larger, let's find out when
      // to save iterations.
      if (curProd > maxProd) {
        foundLargerPossible = 1; 
      }
    }
    if (foundLargerPossible == 0) {
      i = 0;  // we're done now. 
    }
    foundLargerPossible = 0;
  }
  end = clock();

  printf("largest palindrome = %d\n", maxProd);
  printf("\tnum1 = %d\n", num1);
  printf("\tnum2 = %d\n", num2);
  printf("time = %f\n", (end - start)/(double)CLOCKS_PER_SEC);

  // palindromeCreate();
  // palindromeCreate2();

  return 0;
}

int isPalindrome(int num) {
  int numDigits = log10(num) + 1;
  if (numDigits == 1) {
    return 1; 
  }
  char* digitArray = (char*)calloc(numDigits, sizeof(char));

  // creates array of digits (backwards array, but doesn't matter for palin)
  for (int i = 0; i < numDigits; i++) {
    digitArray[i] = num % 10;
    // printf("digitArray[%d] = %d\n", i, digitArray[i]);
    num = num / 10;
  }
 
  // palindrome check logic 
  for (int i = 0; i < numDigits / 2; i++) {
    if (digitArray[i] != digitArray[numDigits-1-i])
      return 0;
  }
  return 1; 
}

// messing around palindrome creater (fairly gross)
int palindromeCreate() {
  // find digits in max number
  int num = 999999;
  int numDigits = log10(num) + 1;
  if (numDigits == 1) {
    return 1; 
  }
  int halfNum = num / pow(10, numDigits/2);
  // note - 99,999 -> 999 (so need to make sure looping doesn't produce the large side of mirror
  int skipLargeMirror;
  if (numDigits % 2 == 0){
      skipLargeMirror = 0; 
  } else {
      skipLargeMirror = 1; 
  }
  printf("halfNum = %d\n", halfNum);
  // loop1: digit level we're checking. ex: 10 digits 9 digits, ... 1 digit
  //   loop2: mirror level (ex: first 123 -> 123321, second 123 -> 12321)
  //     loop3: varying digits between digit and digit - 1 (ex: 999 to 99)
  for (int i = numDigits; i > 4; i--) {
    // printf("i = %d\n", i);
    for (int j = 0; j < 2; j++) {
      if (skipLargeMirror == 1)
        j = 1;
      for (int k = halfNum; k > (halfNum / 10); k--) {
        if (j == 0) {
            int secondHalf = 0;
            int firstHalf = k;
            for (int l = 0; l < i / 2; l++) {
              secondHalf = secondHalf * 10 + firstHalf % 10;
              firstHalf = firstHalf / 10;
            }
            printf("%d\n", k * (int)pow(10, i/2) + secondHalf);
        } else {
            int secondHalf = 0;
            int firstHalf = k / 10; // remove first digit
            for (int l = 0; l < i / 2 -1 ; l++) {
              secondHalf = secondHalf * 10 + firstHalf % 10;
              firstHalf = firstHalf / 10;
            }
            printf("%d\n", k * (int)pow(10, i/2 - 1) + secondHalf);
        }
      }
    }
    skipLargeMirror = 0;
    halfNum /= 10;
  }

  // generate the 999, 989,...,2,1 (or if num lower, start there)
  int temp = 99;
  if (num < temp)
    temp = num;
  temp = num / 10;
  // make sure not to generate a larger number than given
  while (temp > (num % 10)) {
    temp--; 
  }
  for (int i = temp; i > 0; i--) {
    printf("%d\n", i * 10 + i);
  }
  temp = 9;
  if (num < temp)
    temp = num;
  for (int i = temp; i >= 0; i--) {
    printf("%d\n", i); 
  }

  return 0;
}

// more testing (this one doesn't work completely)
int palindromeCreate2() { 
  int num = 999999;
  int numDigits = 6;
  while (numDigits > 2) {
    int leftHalf = num / pow(10, numDigits / 2);
    while (leftHalf > pow(10, numDigits/2 - 1)) {
      // this loop can't handle 99 to 1, so stop and let the cases below handle it 
      if (leftHalf < 10)
        break;
      int leftCopy = leftHalf;
      int rightHalf = 0;
      if (numDigits % 2 == 1) {
        leftCopy /= 10; 
      }
      for (int i = 0; i < numDigits / 2; i++) {
        rightHalf = rightHalf * 10 + leftCopy % 10; 
        leftCopy /= 10;
      }
      printf("%d\n", leftHalf * (int)pow(10, numDigits / 2) + rightHalf);
      leftHalf--;
    }
    numDigits--;
    num = pow(10, numDigits) - 1;
  }
  if (numDigits == 2) {
    int temp = 99;
    if (num < temp)
      temp = num;
    temp = num / 10;
    // make sure not to generate a larger number than given
    while (temp > (num % 10)) {
      temp--; 
    }
    for (int i = temp; i > 0; i--) {
      printf("%d\n", i * 10 + i);
    }
    numDigits--;
  } 
  if (numDigits == 1) {
    int temp = 9;
    if (num < temp)
      temp = num;
    for (int i = temp; i >= 0; i--) {
      printf("%d\n", i); 
    }
  }
  return 0;
}
