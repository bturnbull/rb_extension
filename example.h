
typedef struct {
  int val;
} ExampleStruct;

extern int by_value(int x);

extern int by_ptr_in(int *x);

extern void by_ptr_out(int x, int *y);

extern void by_struct_ptr_out(int x, ExampleStruct *y);
