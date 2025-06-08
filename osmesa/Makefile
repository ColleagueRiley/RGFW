AR = $(GCC_PREFIX)ar
CC = $(GCC_PREFIX)gcc
CFLAGS = -fPIC -Iinclude -Isrc -Isrc/main -Isrc/glapi -Isrc/shader -Isrc/shader/grammar -Isrc/shader/slang $(EXTRA_CFLAGS)
LDFLAGS =
LIBS =

LIB = .a
DYLIB =

DYNAMIC = NO

TARGET = unix

ifneq (,$(filter $(CC),owcc))
CFLAGS += -std=c99
AR = wlib
LIB = .lib
endif

ifneq (,$(filter $(TARGET),windows nt win32 win32s))
CFLAGS += -DWIN32_THREADS

ifeq (,$(filter $(CC),owcc))
LDFLAGS += -Wl,--out-implib,libOSMesa.lib
else
CFLAGS += -I$(WATCOM)/h -I$(WATCOM)/h/nt
ifeq (NO,$(DYNAMIC))
CFLAGS += -b$(TARGET)
else
CFLAGS += -b$(TARGET)_dll
endif
endif

DYLIB = .dll
else ifeq ($(TARGET),unix)
CFLAGS += -DPTHREADS
LIBS += -lpthread -lm
DYLIB = .so
else ifeq ($(TARGET),emscripten)
CFLAGS += -DPTHREADS -pthread
LDFLAGS += -pthread
DYLIB = .so
else
# Unknown platform, but Watcom might know it...
ifneq (,$(filter $(CC),owcc))
CFLAGS += -b$(TARGET)
endif

endif

.PHONY: all clean
.SUFFIXES: .c .o

ifeq (NO,$(DYNAMIC))
all: libOSMesa$(LIB)
else
all: libOSMesa$(DYLIB)
endif

include objects.mk

libOSMesa$(LIB): $(OBJS)
ifeq ($(AR),wlib)
	$(AR) -q -fo -b -n -io -o=$@ $@ +`echo $(OBJS) | sed 's/ / +/g'`
else
	$(AR) rcs $@ $(OBJS)
endif

libOSMesa$(DYLIB): $(OBJS)
	$(CC) $(LDFLAGS) -shared -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f `find src -name "*.o"` *.so *.dll *.a *.lib
