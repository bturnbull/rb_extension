
Ruby Wrapper for C API

## Build library
gcc -Wall -fPIC -c example.c
gcc -shared -W1,-soname,libexample.so.1 -o libexample.so.1.0 example.o

## Build extension
ruby extconf.rb
make


