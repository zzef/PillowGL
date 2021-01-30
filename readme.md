# How to use

The following steps outline how to add this as a shared library

1. Compile and install include files `sudo make install`
2. Set environment variables for linker `export LIBRARY_PATH=/usr/lib/pillow:${LIBRARY_PATH}`
3. Set environment variables for loader `export LD_LIBRARY_PATH=/usr/lib/pillow:${LD_IBRARY_PATH}`

You may have to set `LD_LIBRARY_PATH` instead, depending on your system.

You can then link to it your program during compilation. For example:

`gcc -o cube cube.c -lPlw` 
