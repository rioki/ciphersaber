
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
	rm -f *.o *.d ciphersaber$(EXEEXT)
	
%.o : %.c
	$(CC) $(CFLAGS) -MD -c $< -o $(patsubst %.c, %.o, $<)

ifneq "$(MAKECMDGOALS)" "clean"
-include  $(patsubst %.c, %.d, $(src))
endif
