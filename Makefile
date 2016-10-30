CC = g++
DEBUG = -g -Wall
CFLAGS = -c -std=c++11 $DEBUG

SRCDIR = src
BINDIR = bin
BUILDDIR = build

TARGET = $(BINDIR)/main

EXTENSION = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(EXTENSION))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(EXTENSION)=.o))

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) -o $(TARGET) $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(EXTENSION)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(BINDIR)

.PHONY: clean


