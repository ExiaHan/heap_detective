CC=g++
CFLAGS=-Wall --std=c++2a -O2 
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS=-Wl 
else
	LDFLAGS=-Wl,-z,relro,-z,now,-z,nodump
	# -D_FORTIFY_SOURCE=2
endif

DIR=src/
DIROUT=bin/
HARDENING= -fstack-protector-all -fpie -fPIE -fno-common -fvisibility=hidden -fno-plt -fwrapv-pointer -fwrapv

mem_audit: $(DIR)heap_detective.cpp
	$(CC) $(CFLAGS) $(DFLAGS) -c $(DIR)*.cpp $(HARDENING)
	$(CC) -o $(DIROUT)heap_detective *.o $(LDFLAGS)
	rm *.o

clean:
	rm -f *.o heap_detective

