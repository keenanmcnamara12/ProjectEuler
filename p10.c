/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
 */

#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

typedef struct list_node {
  int number;
  struct list_node* next;
} list_node_t;

// Solution 1 globals
list_node_t head;
list_node_t* tail;

// Solution 2 globals
int* primeArray;
int primeArrayCount;

void init_node(list_node_t * node, int number) {
  node->number = number;
  node->next = NULL;
}

// Had an isPrime implementation in p7.c but that wasn't optimized enough.
// this implemntation leverages a linked list to see if the number in question
// is divisble by any of the primes
int isPrime(int number) {
  list_node_t* node = &head;
  int maxTestNumber = number / 2;
  while (node->next != NULL && node->next->number <= maxTestNumber) {
    node = node->next;
    if (number % node->number == 0)
      return 0;
  }

  tail->next = (list_node_t *)malloc(sizeof(list_node_t));

  // intentionally not modularizing to avoid unecessary activation records
  tail->next->number = number;
  tail->next->next = NULL;
  tail = tail->next;
  return 1;
}

void print_primes() {
  list_node_t* node = &head;
  while (node->next != NULL) {
    node = node->next;
    printf("%d\n", node->number);
  }
}

// Linked list of primes and division checking then summation
void solution1() {
  int number = 2000000;
  long long sum;

  // linked list of primes since we only need to check if a number is divisible
  // by other primes (rather than checking if a non-prime number will divide
  // the number)
  head.number = 1;  // (not actually check, just prevent null in maxTestNumber)
  head.next = (list_node_t *)malloc(sizeof(list_node_t));
  head.next->number = 2;
  sum = 2;
  head.next->next = NULL;
  tail = head.next;
  
  for (int i = 3; i < number; i += 2) {
    if (isPrime(i) == 1)
      sum += i;
  }

  // print prime list for the hell of it
  print_primes();

  printf("sum of all primes below %d = %lld\n", number, sum);
  
  // free the list
  list_node_t* node = &head;
  while (node->next != NULL) {
    node = node->next;
    free(node);
  }
}

int isPrime2(int number) {
  int maxTestNumber = number / 2;
  for (int i = 0; i < primeArrayCount; i++) {
    if (number % primeArray[i] == 0)
      return 0;
    if (primeArray[i] > maxTestNumber)
      break;
  }
  primeArray[primeArrayCount] = number;
  primeArrayCount++;
  return 1;
}

// Instead of linked list, use a large array (don't try to be cute with
// using memory resizing, we'll just initialize the few MB necessary).
void solution2() {
  int number = 2000000;
  long long sum;

  primeArray = (int *)calloc(number, sizeof(int));
  primeArray[0] = 2;
  primeArrayCount = 1;
  sum = 2;
  
  for (int i = 3; i < number; i += 2) {
    if (isPrime2(i) == 1)
      sum += i;
  }
  printf("sum of all primes below %d = %lld\n", number, sum);
  free(primeArray);

}

// After verifying the numberic answer online I found the Sieve of eratosthenes
// so I'm going to see how that one is. I wish I hadn't seen this solution when
// I did since I was naturally working towards something like that as I moved
// from p7.c's isPrime to solution1 with a linked list to solution2 with an
// array. Anyway, this one is pretty cool and is well described on wikipedia
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// This solution is so much faster than solution1 and solution2
void solution3() {
  int number = 2000000;
  long long sum;
  // Allocates nodes to zero, so one will indicate that a value is not a prime
  int* sieve = (int *)calloc(number, sizeof(int));
  sieve[0] = 1;
  sieve[1] = 1;
  int sievePosition = 2;
  while (sievePosition < number) {
    for (int i = sievePosition + sievePosition; i < number; i += sievePosition)
      sieve[i] = 1; 
    
    sievePosition++;
    while(sieve[sievePosition] == 1)
      sievePosition++; 
  }

  sum = 0;
  for (int i = 0; i < number; i++) {
    if (sieve[i] == 0)
      sum += i;
  }
  printf("sum of all primes below %d = %lld\n", number, sum);
}

int main(int argc, char** argv) {
  // solution1();
  // solution2();
  solution3();
  return 0;
}
