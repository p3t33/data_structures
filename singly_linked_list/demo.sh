gcc -ansi -pedantic-errors -Wall -Wextra -g sl_list_test.c sl_list.c
valgrind --leak-check=yes --track-origins=yes ./a.out