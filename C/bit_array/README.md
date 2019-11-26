### Getting Started

This bit array implementation is extended by using a LUT file for API functions
CountBitLut and MirrorBitLut to do the same calculations done by API functions
CountOn and Mirror.
After running the binary compiled from auxiliary prep_lut.c file, a lut.h file
will be created.  lut.h is part of the included list in bit_array.c file.
bit_array.c won't compile without existence of lut.h, so it is important to
create it first.

The simplest way to do all of this is by running the provided script:
```bash
    ./compile_and_run.sh
```