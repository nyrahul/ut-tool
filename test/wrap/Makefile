include ../../mk.inc

all:
	$(CC) $(CFLAGS) wrap.c -shared -o libwrap.so $(LDFLAGS) -ldl

clean:
	@rm libwrap.so *.gc* 2>/dev/null
