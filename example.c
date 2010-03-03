
#include "example.h"

int by_value(int x) { return (x*2); }

int by_ptr_in(int *x) { return ((*x)*2); }

void by_ptr_out(int x, int *y) { *y = x*2; }

int by_struct_ptr_in(ExampleStruct *x) { return ((x->val)*2); }

void by_struct_ptr_out(int x, ExampleStruct *y) { y->val = x*2; }

