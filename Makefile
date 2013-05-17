
CC     ?= gcc
CFLAGS ?= -g -Wall

src = $(wildcard *.c)

ifeq ($(MSYSTEM), MINGW32)
  EXEEXT = .exe  
else
  EXEEXT =
endif

.PHONY: all clean

all: ciphersaber$(EXEEXT)

ciphersaber$(EXEEXT): $(patsubst %.c, %.o, $(src))
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm *.o *.d ciphersaber$(EXEEXT)

ifneq "$(MAKECMDGOALS)" "clean"
-include  $(patsubst %.c, %.d, $(src))
endif
