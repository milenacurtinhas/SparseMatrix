CC = gcc
CFLAGS = -I./include -Wall 
LIBS := -lm
OBJDIR = objects
SRCDIR = source

OBJECTS = $(OBJDIR)/matrix.o $(OBJDIR)/node.o $(OBJDIR)/aux.o
ALL_OBJECTS = $(shell find . -type f -name "*.o" -print) 

all: prog1 prog2 build_libs

$(OBJDIR):
	mkdir -p $(OBJDIR)
	
prog1: $(OBJDIR) $(OBJECTS) main1.c
	$(CC) $(CFLAGS) -o prog1 main1.c $(OBJECTS) $(LIBS)

prog2: $(OBJDIR) $(OBJECTS) main2.c
	$(CC) $(CFLAGS) -o prog2 main2.c $(OBJECTS) $(LIBS)

$(OBJDIR)/matrix.o: $(SRCDIR)/matrix.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/matrix.c -o $(OBJDIR)/matrix.o

$(OBJDIR)/node.o: $(SRCDIR)/node.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/node.c -o $(OBJDIR)/node.o

$(OBJDIR)/aux.o: $(SRCDIR)/aux.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/aux.c -o $(OBJDIR)/aux.o


clean:

	rm prog1 prog2 $(OBJDIR)/*.o 
	rm -r $(OBJDIR)
	rm -f *.bin
	rm -f *.txt