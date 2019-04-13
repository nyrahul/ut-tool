include ../mk.inc

all:
	$(CC) $(CFLAGS) sample.c -shared -o libsample.so $(LDFLAGS)

clean:
	@rm -f libsample.so *.gc* 2>/dev/null
