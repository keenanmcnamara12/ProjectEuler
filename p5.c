/*2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.  What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?*/

#include <stdio.h>
#include <stdlib.h>

// Recursively factors number and loads factorArrayTemp with the the prime
// factors of it (does note remove duplicates).
void factorsInternal(int number, int size, int* factorArrayTemp) {
  for (int i = number - 1; i > 1; i--) {
    if (number % i == 0) {
      factorsInternal(number/i, size, factorArrayTemp);
      factorsInternal(i, size, factorArrayTemp);
      return;
    } 
  }

  // make sure factor isn't in array
  for (int i = 0; i < size; i++) {
    if (factorArrayTemp[i] == 1) {
      factorArrayTemp[i] = number;
      return;
    }
  }
  return;
}

// For number loads factors that haven't been accounted for for number.
// Probably not great for large memory.
void factors(int number, int size, int* factorArray) {
  int* factorArrayInternal = (int*)malloc(number * sizeof(int));
  int* factorArrayCopy = (int*)malloc(size * sizeof(int));
  for (int i = 0; i < number; i++)
    factorArrayInternal[i] = 1;
  
  // Create a copy of the true result array so we can destroy it in the deduplication 
  for (int i = 0; i < size; i++)
    factorArrayCopy[i] = factorArray[i];
 
  factorsInternal(number, size, factorArrayInternal);
  
  // merge the new factorArrayInternal into the factorArray by destroying the
  // copy of factorArrayCopy. This destruction will prevent unecessary
  // additionals to the true results array. For example if factorArray contains
  // 2,2 and factorArrayInternal contains 2,2,2. Then one additional 2 will be
  // added to factorArray by first setting the 2s in factorArrayCopy to 0,0.
  // Then the following final two will not be found in the factorArrayCopy.
  for (int i = 0; i < number; i++) {
    int newNumber = factorArrayInternal[i];
    int found = 0;
    for (int j = 0; j < size; j++) {
      if (factorArrayCopy[j] == newNumber) {
        found = 1;
        factorArrayCopy[j] = 0;
        break;
      }
    }
    if (found != 1) {
      for (int j = 0; j < size; j++) {
        if (factorArray[j] == 1) {
          factorArray[j] = newNumber;
          break;
        }
      } 
    }
  } 
  
  // for (int i = 0; i < number; i++) {
  //   if (i != 0)
  //     printf("factorArrayInternal[%d] = %d\n", i, factorArrayInternal[i]);
  // }
  
  free(factorArrayInternal);
  free(factorArrayCopy);
}

int main(int argc, char** argv) {
  int number = 20;
  long sum = 1;  // supporting large numbers
  int* factorArray = (int*)malloc(number * sizeof(int));
  for (int i = 0; i < number; i++)
    factorArray[i] = 1;
  
  for (int i = number; i > 1; i--)
    factors(i, number, factorArray);

  for (int i = 0; i < number; i++) {
    sum *= (long)factorArray[i];
    // printf("factorArray[%d] = %d\n", i, factorArray[i]);
  }

  printf("smallest number that can be divided by each of the numbers from 1 to %d without any remainder = %ld\n", number, sum);
  free(factorArray);

  return 0;
}
