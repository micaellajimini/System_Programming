.SUFFIXES : .c .o

OBJECTS = 20151567.o
SRCS = 20151567.c

CC = gcc
CFLAGS = -Wall -c

TARGET = 20151567.out

all : $(SRCS) $(TARGET)

$(TARGET) : $(OBJECTS)
			  $(CC) -o $(TARGET) $(OBJECTS)

clean :
			rm -rf $(OBJECTS) $(TARGET)
