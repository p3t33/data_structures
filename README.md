# Data structures

This repository contains several implementations (in c and c++) of common data structures, each one has a folder and an API. All data structures were tested and preform as expected to the best of my knowledge, if you encounter a bug please let me know. 

All stable and tested code is located on the master branch and all unfinished / untested code is located on the development branch.

## Compilers and operating system
* Development was on ubuntu 18.04 LTS OS.
* Source code was compiled with:
    - for C - GNU gcc (v7.4) and clang (v6.0), std=99
    - for C++ - GNU g++ (v7.4) and clang++ (v6.0), std=11
* Tested for memory leaks using Valgrind v3.13.0
  

## Getting Started

1. Clone the repository by typing in the command line:
```
  git clone https://github.com/p3t33/data_structures.git
```

2. Compile the source code:
run the following bash script to compile all test files 
```
  ./compile_source.sh
```
 
Optional:

clean up all binaries by running:
```
  ./clean_up.sh
```   

## Running the tests
After compiling source code with ./compile_source.sh bash script. Each data structure folder will contain binary .out file, running it will run the unit test for the specific data structure.  

For example, for stack data structure:
```
  ./stack/stack_test.out
```

## Versioning

Each API has version and date of last update.

## Authors

* **Kobi Medrish**  -  [github](https://github.com/p3t33)

## License

Licensed under the [GPLv3](http://www.gnu.org/licenses/gpl-3.0.html) license.


