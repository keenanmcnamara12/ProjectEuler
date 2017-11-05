/*A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

  a^2 + b^2 = c^2
  For example, 32 + 42 = 9 + 16 = 25 = 5^2.

  There exists exactly one Pythagorean triplet for which a + b + c = 1000.
  Find the product abc.*/

#include <stdio.h>
#include <math.h>

int check(int a, int b, int c) {
  if (pow(a, 2) + pow(b, 2) == pow(c, 2))
    return 1;
  return 0;
}

int main(int argc, char** argv) {
  int done = 0;
  int a, b, c;
  b = 0;
  c = 0;

  for (c = 1000; b < c; c--) {
    if (c <= 1000-c) {
        b =  c - 1;
        for (; b > 1000-b-c; b--) {
          a = 1000 - b - c; 
          // printf("a = %d\tb = %d\tc = %d\tsum = %d\n", a, b, c, a+b+c);
          if (check(a,b,c) == 1) {
            done = 1;
            break;
          }
        }
        if (done == 1)
          break;
    } else {
        b = 1000 - c;
        for (; b > 1000-b-c; b--) {
          a = 1000 - b - c; 
          // printf("a = %d\tb = %d\tc = %d\tsum = %d\n", a, b, c, a+b+c);
          if (check(a,b,c) == 1) {
            done = 1;
            break;
          }
        }
        if (done == 1)
          break;
    }
  }
  if (done == 1) {
      printf("a = %d\tb = %d\tc = %d\tsum = %d\n", a, b, c, a+b+c);
      printf("\t%d^2 + %d^2 = %d + %d = %d^2 = %d\n", 
              a, b, (int)pow(a,2), (int)pow(b,2), c, (int)pow(c,2));
  } else {
      printf("Hmm, must have done something wrong - solution not found\n"); 
  }
  return 0;
}
