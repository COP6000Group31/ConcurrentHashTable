# Concurrent Hash Table

## Building

Run `make` to build `chash`.

## Running

Run `./chash`.

AI USE:

The AI was used for two parts in this project. It was used as a very quick way to get a Makefile up and running using the input "I want to create a Makefile for a C program "chash.c" which runs gcc chash.c" The Makefile in this repo is the result of that input into ChatGPT. It was convenient in that it made the make, make run, and make clean all at the same time.
Secondly, ChatGPT was made to fix errors in how originally we tried to implement the array of pthreads to be created. 

Prompt: here is my chash.c file:
//insert file with non-working implementations
I want to implement threading in chash.c to run the commands as individual threads. 

This produced a nearly working version of the chash.c that required minimal reworking to get it to work correctly with hashdb.c.


Tried to see how far it could get asking it to incorporate reader/writer locks as well with this prompt:

I want to implement reader/writer locks in my hashdb.c file where it is commented in each function

//insert hashdb.c code below

The results were pretty awful and it tried to use the pthread_rwlock_init/destroy/rdlock/rdrelease that didn't want to work nicely with the current implementation. 

Resulted in using the rwlocks.c and rwlocks.h examples from the book which were significantly easier to use and adapted their implementation into our own codebase. Like this first assignment, it is easier to just do it yourself than trying to do more complex interactions using chatGPT... But 10/10 for an extremely fast way to make a makefile( as basic as it is )

