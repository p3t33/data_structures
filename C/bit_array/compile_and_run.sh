# Remove binary files if any exists already. 
rm *.out

# compile prep_lut.
gcc -std=c99 -pedantic-errors -Wall -Wextra -g -o prep_lut.out \
prep_lut.c

# run the binary that will create lut.h file to be used with bit array.
./prep_lut.out

# compile bit_array and run it
gcc -std=c99 -pedantic-errors -Wall -Wextra -g -o bit_array.out \
bit_array.c \
bit_array_test.c 

./bit_array.out
