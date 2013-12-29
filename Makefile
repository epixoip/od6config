CC      = cc
CFLAGS  = -g -O2 -Wall 
OUT     = od6config
LIBS    = -ldl

OBJS := $(patsubst %.c,%.o,$(wildcard src/*.c))

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS) $(LIBS)

install:
	install -d -m 0755 -o root -g root $(DESTDIR)/usr
	install -d -m 0755 -o root -g root $(DESTDIR)/usr/sbin
	install -m 0755 -o root -g root $(OUT) $(DESTDIR)/usr/sbin/

uninstall:
	rm -f $(DESTDIR)/usr/sbin/$(OUT)

clean:
	rm -f $(OUT) src/*.o 

distclean: clean
	rm -rf ADL_SDK/include
