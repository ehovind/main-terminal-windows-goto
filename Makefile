CC=gcc

# GCC Compiler flags
DEBUG ?= 0
ifeq ($(DEBUG),1)
	CFLAGS=-std=c99 -Wall -Wextra -Wformat=2 -Wswitch-default -Wswitch-enum -Wcast-align -Wpointer-arith -Wbad-function-cast -Wstrict-prototypes -Winline -Wundef -Wnested-externs -Wshadow -Wwrite-strings -Wconversion -Wunreachable-code -Wstrict-aliasing=2 -Wfloat-equal -Waggregate-return -ffloat-store -fno-common -fstrict-aliasing -lm -pedantic -O0 -ggdb3 -pg --coverage -D_POSIX_C_SOURCE=200112L -DDEBUG -fprofile-arcs -ftest-coverage
else
	CFLAGS=-std=c99 -lm -pedantic -O3 -funroll-loops -D_POSIX_C_SOURCE=200112L -DNODEBUG
endif

# Library flags
LDLIBS=-fprofile-arcs

# Pre-processor and compile flags
INCLUDES=$(shell pkg-config --cflags glib-2.0 gtk+-3.0 gdk-3.0 libwnck-3.0)

# Linker flags
LIBS=$(shell pkg-config --libs glib-2.0 gtk+-3.0 gdk-3.0 libwnck-3.0)

bindir = bin
srcdir = src
PROGRAM = mtwg
SOURCES = $(wildcard $(srcdir)/*.c)
OBJECTS = $(patsubst $(srcdir)/%.c,$(bindir)/%.o,$(SOURCES))

.PHONY: install clean

all: clean $(PROGRAM)

clean:
	rm -f $(bindir)/*.o $(PROGRAM)

install:
	install -m 0755 $(PROGRAM) /usr/local/bin/

$(PROGRAM): $(OBJECTS)
	$(CC) $(LDLIBS) $(LIBS) $^ -o $@

$(OBJECTS): bin/%.o : src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
