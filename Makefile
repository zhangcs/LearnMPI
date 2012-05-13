CC= mpicc
CFLAGS= -O3 -Wall -g
# LIBS= -llapack -lblas -lg2c

SRCS_hello= hello.c
OBJS_hello= ${SRCS_hello:.c=.o}

SRCS_sendrecv= sendrecv.c
OBJS_sendrecv= ${SRCS_sendrecv:.c=.o}

SRCS_mmult= mmult.c
OBJS_mmult= ${SRCS_mmult:.c=.o}

# several test examples
hello: Makefile $(OBJS_hello) 
	$(CC) $(CFLAGS) -o hello $(OBJS_hello) $(LIBS)

send: Makefile $(OBJS_sendrecv) 
	$(CC) $(CFLAGS) -o sendrecv $(OBJS_sendrecv) $(LIBS)

mmult: Makefile $(OBJS_mmult) 
	$(CC) $(CFLAGS) -o mmult $(OBJS_mmult) $(LIBS)

# standard clean up and achieve targets
tgz:
	gzip mpi.tar
	cp mpi.tar.gz mpi.tgz

tar:
	tar -cf mpi.tar Makefile *.c *.h *.cmd

clean:
	rm -f *.out *.o *~

allclean:
	rm -f *.out *.o *~
	rm -f hello sendrecv mmult


