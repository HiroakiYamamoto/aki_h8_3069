PREFIX	= /usr/cross
ARCH	= h8300-elf
BINDIR	= $(PREFIX)/bin
ADDNAME	= $(ARCH)-

AR	= $(BINDIR)/$(ADDNAME)ar
AS	= $(BINDIR)/$(ADDNAME)as
CC	= $(BINDIR)/$(ADDNAME)gcc
LD	= $(BINDIR)/$(ADDNAME)ld
NM	= $(BINDIR)/$(ADDNAME)nm
OBJCOPY	= $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP	= $(BINDIR)/$(ADDNAME)objdump
RANLIB	= $(BINDIR)/$(ADDNAME)ranlib
STRIP	= $(BINDIR)/$(ADDNAME)strip

BUILD_DIR = ../../build/build_$(ARCH)/$(TARGET)

OBJS	= startup.o main.o interrupt.o
OBJS	+= lib.o serial.o

TARGET	= kozos

BUILD_OBJS	= $(patsubst %, $(BUILD_DIR)/%, $(OBJS))

BUILD_TARGET	= $(patsubst %, $(BUILD_DIR)/%, $(TARGET))

BUILD_ELF	= $(addsuffix .elf, $(BUILD_TARGET))

BUILD_MOT	= $(addsuffix .mot, $(BUILD_TARGET))

CFLAGS	= -Wall -mh -nostdinc -nostdlib -fno-builtin
#CFLAGS	+= -mint32
CFLAGS	+= -I.
#CFLAGS	+= -g
CFLAGS	+= -Os
CFLAGS	+= -DKOZOS

LDFLAGS	= -static -T ld.scr -L.

#.SUFFIXES: .c .o
#.SUFFIXES: .s .o

all :		$(BUILD_DIR) $(BUILD_TARGET)

$(BUILD_DIR)/$(TARGET) :	$(BUILD_OBJS)
		$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
		cp $@ $(BUILD_DIR)/$(TARGET).elf
		$(STRIP) $@

$(BUILD_DIR)/%.o :	%.c
		$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o :	%.s
		$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.o :	%.S
		$(CC) -c $(CFLAGS) -o $@ $<

clean :		
		rm -f $(BUILD_OBJS) $(BUILD_TARGET) $(BUILD_ELF)
