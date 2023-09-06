## DHCP Server Project

This project implements a DHCP (Dynamic Host Configuration Protocol) server for managing IP address allocation within a network range. The DHCP server provides functions to create the server, allocate and free IP addresses, and count available (free) IP addresses. It efficiently handles scenarios like successful allocation, failed allocation, and double allocation attempts.


# Project Description

The DHCP server project efficiently manages IP address allocation within a network range. It offers a clear and well-documented interface and supports various functionalities, including IP allocation, deallocation, and counting available IP addresses. The code structure is designed for maintainability and future updates.

# Project Structure

The project is organized as follows:

- Header Files (include/): Contains the header files necessary for the project.

- Source Files (src/): Contains the source files for the DHCP server implementation.

- Tests (test/dhcp): Includes test files and a makefile for building running and 
testing the project.

# Dependencies
The project relies on a trie data structure, which is included as trie.h and trie.c
in the project folders. also a test for the trie is provided.

# Building and Testing
To build and test the project, navigate to the test/dhcp folder and use the provided makefile:

```shell
# Simple compilation
$ make
# Running the project
$ make run
# Debugging the project
$ make debug
# Deleting all the obj, exe, shared/static libs files
$ make clean 
# Checking valgrind on the project
$ make vlg 
# Release compilation with optimization -O3
$ make release

```

## Contact

For any questions about the project:

### Name: Tal Aharon
### Email: tal.aharon.work@gmail.com