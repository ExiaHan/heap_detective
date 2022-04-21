CC=g++
CFLAGS=-Wall --std=c++11 -O2 
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS=-Wl 
else
	LDFLAGS=-Wl,-z,relro,-z,now  
	# -D_FORTIFY_SOURCE=2
endif

DIR=src/
DIROUT=bin/
HARDENING= -fstack-protector-all -pie -fPIE -ftrapv

mem_audit: $(DIR)heap_detective.cpp
	$(CC) $(CFLAGS) $(DFLAGS) -c $(DIR)*.cpp $(HARDENING)
	$(CC) -o $(DIROUT)heap_detective *.o $(LDFLAGS)
	rm *.o

clean:
	rm -f *.o heap_detective

