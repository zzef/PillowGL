# How to use

The following steps outline how to add this as a shared library

1. `sudo make install`
2. `export LD_LIBRARY_PATH=/usr/lib/pillow:${LD_LIBRARY_PATH}`

You can then link to it. For example:

`gcc -o main main.c -lPlw` 
