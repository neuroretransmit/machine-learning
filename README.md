# cpp-lib-skeleton

This is a skeleton for Makefile project that has had its variables modularized and made nice and neat. The project has Google Test set up out of the box and some handy scripts. ```scripts/env-setup.sh``` will compile and install Google Test for you if you are on Ubuntu.

## Adding define statements to compilation flags 

(Currently, the only supported define is DEBUG. (It will add -g to your compiler flags and use your ```#ifdef DEBUG``` code.)

```
$ make DEFINES=-DDEBUG
```
