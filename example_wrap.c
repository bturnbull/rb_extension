#include "example.h"
#include "ruby.h"

// Wrap ExampleStruct struct as Ruby class Example::Struct

static void example_struct_free(void *p)
{
  free(p);
}

static VALUE example_struct_alloc(VALUE klass)
{
  ExampleStruct *es;
  VALUE obj;

  es = (ExampleStruct *)malloc(sizeof(ExampleStruct));

  obj = Data_Wrap_Struct(klass, 0, example_struct_free, es);

  return obj;
}

static VALUE example_struct_initialize(VALUE self)
{
  ExampleStruct *es;

  Data_Get_Struct(self, ExampleStruct, es);
  es->val = 0;

  return self;
}

static VALUE example_struct_val_get(VALUE self)
{
  ExampleStruct *es;

  Data_Get_Struct(self, ExampleStruct, es);

  return INT2NUM(es->val);
}

static VALUE example_struct_val_set(VALUE self, VALUE val)
{
  ExampleStruct *es;

  Data_Get_Struct(self, ExampleStruct, es);
  es->val = NUM2INT(val);

  return Qnil;
}

// Example Module Top Level Methods

static VALUE example_by_value(VALUE self, VALUE x)
{
  return INT2NUM(by_value(NUM2INT(x)));
}

static VALUE example_by_ptr_in(VALUE self, VALUE x)
{
  VALUE y;
  int *xp;

  // demonstrate heap allocation
  xp = malloc(sizeof(int));
  *xp = NUM2INT(x);
  y = INT2NUM(by_ptr_in(xp));
  free(xp);

  return y;
}

static VALUE example_by_ptr_out(VALUE self, VALUE x)
{
  int y;

  by_ptr_out(NUM2INT(x), &y);

  return INT2NUM(y);
}

static VALUE example_by_struct_ptr_in(VALUE self, VALUE x)
{
  ExampleStruct *esp;

  Data_Get_Struct(x, ExampleStruct, esp);
  return INT2NUM(by_struct_ptr_in(esp));
}

static VALUE example_by_struct_ptr_out(VALUE self, VALUE x)
{
  VALUE y;
  ExampleStruct es;

  // demonstrate stack allocation
  by_struct_ptr_out(NUM2INT(x), &es);
  y = INT2NUM(es.val);

  return y;
}

// Extension Initialization

static VALUE mExample;
static VALUE cExampleStruct;

void Init_example()
{
  // Example module
  mExample = rb_define_module("Example");

  // Example module methods
  rb_define_module_function(mExample, "by_value", example_by_value, 1);
  rb_define_module_function(mExample, "by_ptr_in", example_by_ptr_in, 1);
  rb_define_module_function(mExample, "by_ptr_out", example_by_ptr_out, 1);
  rb_define_module_function(mExample, "by_struct_ptr_in", example_by_struct_ptr_in, 1);
  rb_define_module_function(mExample, "by_struct_ptr_out", example_by_struct_ptr_out, 1);

  // Example::ExampleStruct class
  cExampleStruct = rb_define_class_under(mExample, "Struct", rb_cObject);
  rb_define_alloc_func(cExampleStruct, example_struct_alloc);
  rb_define_method(cExampleStruct, "initialize", example_struct_initialize, 0);
  rb_define_method(cExampleStruct, "val", example_struct_val_get, 0);
  rb_define_method(cExampleStruct, "val=", example_struct_val_set, 1);

}
