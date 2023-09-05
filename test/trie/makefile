# Path and name
NAME = trie

PROJECT_PATH = ../..

# The compiler : gcc for C program :
CC = gcc

# Compiler flags :
CFLAGS = -ansi -pedantic-errors -Wall -Wextra

# Valgrind
VALGRIND = valgrind --leak-check=yes --track-origins=yes -s

# Debug
DEBUG = gdb -tui

#Remove
RM = rm -rf

# Archive
AR = ar -rcs

# Source file
SRC = $(PROJECT_PATH)/src/$(NAME).c

# Source object file
O_SRC = $(PROJECT_PATH)/bin/objects/$(NAME).o

# Header file
HEADER = $(PROJECT_PATH)/include/$(NAME).h

# Path to header
PATH_TO_HEADER = -I$(PROJECT_PATH)/include/

# Main file
MAIN = $(PROJECT_PATH)/test/$(NAME)/$(NAME)_test.c

# Main file
O_MAIN = $(PROJECT_PATH)/bin/objects/$(NAME)_test.o

# The build target executable
TARGET = $(PROJECT_PATH)/bin/executables/$(NAME)

# Static Lib names
S_LIB = $(PROJECT_PATH)/bin/static_libs/lib$(NAME).a

# Shared Lib names
SO_NAME = $(PROJECT_PATH)/bin/shared_libs/lib$(NAME).so

# Shared lib path
PATH_TO_SO = -L$(PROJECT_PATH)/bin/shared_libs

# Static lib path
PATH_TO_S = -L$(PROJECT_PATH)/bin/static_libs

# Files of the project
C_FILES = $(MAIN) $(SRC)

# Files of the project
O_FILES = $(O_MAIN) $(O_SRC)

# List of all headers
HEADERS = $(HEADER)

.PHONY : run leak release debug lib.a lib.so link_shared link_static clean

#******************************************************************************

$(TARGET) : $(O_FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(O_FILES) -o $(TARGET)

#******************************************************************************

$(O_MAIN) : $(MAIN) $(HEADER)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(MAIN) -o $(O_MAIN)

$(O_SRC) : $(SRC) $(HEADER)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(SRC) -o $(O_SRC)

#******************************************************************************

run : $(TARGET)
	clear
	$(TARGET)

#******************************************************************************

vlg : CFLAGS += -DDEBUG_ON -g
vlg : clean $(TARGET)
	clear
	$(VALGRIND) $(TARGET)

#******************************************************************************

link_static : lib.a $(O_FILES)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) $(MAIN) $(PATH_TO_S) -l$(NAME) -o $(TARGET)
	clear

#******************************************************************************

lib.a : $(O_FILES)
	$(AR) $(S_LIB) $(O_SRC)
	ranlib $(S_LIB)
	clear

#******************************************************************************

link_shared : lib.so
	$(CC) $(PATH_TO_HEADER) $(PATH_TO_SO) -Wl,-rpath=$(dir $(SO_NAME)) -Wall $(MAIN) -l$(NAME) -o $(TARGET)
	clear

#******************************************************************************

lib.so : CFLAGS += -fPIC -c
lib.so : 
	$(RM) $(TARGET) $(O_SRC)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(SRC) -o $(O_SRC)
	$(CC) -shared -o $(SO_NAME) $(O_SRC)
	clear

#******************************************************************************

debug : CFLAGS += -DDEBUG_ON -g
debug : clean $(TARGET)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) $(C_FILES) -o $(TARGET)
	$(DEBUG) $(TARGET)
	clear

#******************************************************************************

release : CFLAGS += -DNDEBUG -O3
release : clean $(TARGET)
	$(CC) $(PATH_TO_HEADER) $(CFLAGS) $(C_FILES) -o $(TARGET)
	clear

#******************************************************************************

clean :
	clear
	$(RM) $(TARGET) $(O_FILES) $(SO_NAME) $(S_LIB)


#******************************************************************************

# When including: put the $(EXTERNAL_O_SRC) $(EXTERNAL_SRC) with the c files and o files.
# Put the variables in the top section of the make file and the rule in the objects rull section.
# In the header file remember to include the external header
# Add the external header file the the src object rull or any other file that depend on it.

# External dependency objects
# EXTERNAL_O_SRC = $(PROJECT_PATH)/bin/objects/?.o

# External dependency source
# EXTERNAL_SRC = $(PROJECT_PATH)/src/?.c

# External dependency header
#EXTERNAL_HEADER = $(PROJECT_PATH)/include/?.h

#$(EXTERNAL_O_SRC) : $(EXTERNAL_SRC) $(EXTERNAL_HEADER)
#	$(CC) $(PATH_TO_HEADER) $(CFLAGS) -c $(EXTERNAL_SRC) -o $(EXTERNAL_O_SRC)
#	clear
