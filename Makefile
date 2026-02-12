LIBRESSL_INC = /usr/include/libressl
LIBRESSL_LIB = /usr/lib/libressl

CC_ARGS =

-include config.mk

all: dwmstatus mailstatus alarm

dwmstatus: dwmstatus.c
	$(CC) $(CC_ARGS) -o $@ $< -lX11

mailstatus: mailstatus.c
	$(CC) $(CC_ARGS) -o $@ $< -I$(LIBRESSL_INC) -L$(LIBRESSL_LIB) -ltls

alarm: alarm.c
	$(CC) $(CC_ARGS) -o $@ $< -lX11

clean:
	rm -f *.o dwmstatus mailstatus

