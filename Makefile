SHELL ?= /bin/bash
CC ?= gcc
START_FILE = /usr/include/alibc/crt0.S
CFLAGS ?= -nostdlib -Wall -lac -I/usr/include/alibc
TARGET = ash
CSOURCES = $(shell find . -type f -name "*.c")

USER_DIR ?= /home/artinel
OS_DIR ?= $(USER_DIR)/os/artia/mnt
INSTALL_PATH ?= $(OS_DIR)/bin


OBJECTS = $(CSOURCES:.c=_c.o)

%_c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

install:
	cp $(TARGET) $(INSTALL_PATH)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(START_FILE)

clean:
	rm src/*.o
	rm $(TARGET)
