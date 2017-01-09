CC = g++-5
DEBUG = -g -Wall
CFLAGS = -c -std=c++11 $(DEBUG) -I${SDSLLITE}/include
LDFLAGS= -L${SDSLLITE}/lib -static -lsdsl -ldivsufsort -ldivsufsort64

SRCDIR = src
BINDIR = bin
BUILDDIR = build

TARGET = $(BINDIR)/main

EXTENSION = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(EXTENSION))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(EXTENSION)=.o))

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) -o $(TARGET) $^ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(EXTENSION)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -rf $(BUILDDIR) $(BINDIR)

.PHONY: clean