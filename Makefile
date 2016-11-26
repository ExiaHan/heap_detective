CC=g++
CFLAGS=-Wall --std=c++11 -O2 -fstack-protector-all
DFLAGS=-D_FORTIFY_SOURCE=2
LDFLAGS=-Wl,-z,relro,-z,now 
DIR=src/
DIROUT=bin/


mem_audit: $(DIR)heap_detective.cpp
	$(CC) $(CFLAGS) $(DFLAGS) -c $(DIR)*.cpp
	$(CC) -o $(DIROUT)heap_detective *.o $(LDFLAGS)
	rm *.o

clean:
	rm -f *.o heap_detective

