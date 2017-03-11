PROGS = libapue.so.1
PROGS2 = libapue.a

share: $(PROGS)
static: $(PROGS2)

$(PROGS): 
	gcc -Wall -fPIC -c *.c
	gcc -shared -Wl,-soname,libapue.so -o $(PROGS) *.o

$(PROGS2):
	gcc -Wall -c *.c
	ar rsv $(PROGS2) *.o

clean: 
	rm -f *.o $(PROGS) $(PROGS2) 
		
