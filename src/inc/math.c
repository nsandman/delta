#include <math.h>

#define DBL_EPSILON 2.2204460492503131E-16
#define INT_MAX 2147483647
#define INT_MIN -2147483648 

// These functions were stolen from OSDevLibc (code.google.com/p/osdevlibc)
double exp(double x) {
  __asm("fldl2e ; fmulp ; f2xm1" : "+t"(x));
  return x + 1;
}

double fabs(double x) {
  __asm("fabs" : "+t"(x));
  return x;
}

double nearbyint(double x) {
  __asm("frndint" : "+t"(x));
  return x;
}

double floor(double x) {
  uint_least16_t controlWord;
  __asm __volatile("fstcw %0" : : "m"(controlWord) : "memory");
  controlWord |= 0x800; controlWord &= ~0x400;
  __asm __volatile("fldcw %0" : : "m"(controlWord));
  return nearbyint(x);
}

double log2(double x) {
  __asm("fld1 ; fxch ; fyl2x" : "+t"(x));
  return x;
}

double log(double x) {
  double ln2;
  __asm("fldln2" : "=t"(ln2));
  return ln2 * log2(x);
}

double pow(double x, double y) {
  return exp(y * log(x));
}