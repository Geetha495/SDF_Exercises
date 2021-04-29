.PHONE	: all clean

CC=/usr/bin/g++
CFLAGS=-std=c++2a -Wall -Werror -pedantic-errors
FMTDIR=packages/fmt-7.1.3
INCLUDEDIR=${FMTDIR}/include 
LIBDIR=$(FMTDIR)
EXE=thread_pool

SRCS=main.cpp

all	: $(EXE)

$(EXE)	: $(SRCS)
	$(CC) $(CFLAGS) -o $(EXE) -L $(LIBDIR) -I $(INCLUDEDIR) -I . $(SRCS) -lfmt -lpthread

clean	:
	rm -f *.o $(EXE)
