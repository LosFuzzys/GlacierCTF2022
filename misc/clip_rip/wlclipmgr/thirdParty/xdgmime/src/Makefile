.POSIX:
.PHONY: all clean

C_STD = -std=c99 -D_POSIX_C_SOURCE=200809L
ALL_CFLAGS = $(C_STD) -c -g -DXDG_PREFIX=xdg_test -DHAVE_MMAP -Wall -Wmissing-prototypes -Wno-sign-compare $(CFLAGS)

.c.o:
	$(CC) $(ALL_CFLAGS) -o $@ $<

all: test-mime test-mime-data print-mime-data

test-mime: test-mime.o xdgmime.o xdgmimeglob.o xdgmimeint.o xdgmimemagic.o xdgmimealias.o xdgmimeparent.o xdgmimecache.o xdgmimeicon.o
	$(CC) $(LDFLAGS) -o $@ $?

test-mime-data: test-mime-data.o xdgmime.o xdgmimeglob.o xdgmimeint.o xdgmimemagic.o xdgmimealias.o xdgmimeparent.o xdgmimecache.o xdgmimeicon.o
	$(CC) $(LDFLAGS) -o $@ $?

print-mime-data: print-mime-data.o xdgmime.o xdgmimeglob.o xdgmimeint.o xdgmimemagic.o xdgmimealias.o xdgmimeparent.o xdgmimecache.o xdgmimeicon.o
	$(CC) $(LDFLAGS) -o $@ $?

clean:
	rm -f *~ *.o test-mime test-mime-data print-mime-data
