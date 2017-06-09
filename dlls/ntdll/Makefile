DESTDIR?=../..
CURRENT_DLL=DLL_NTDLL
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL)

all: ntdll.dll qemu_ntdll.dll.so

ntdll.dll: ntdll.def main_g.o critsection_g.o signal_g.o
	x86_64-w64-mingw32-ld -shared ntdll.def *_g.o -o ntdll.dll -nostdlib

qemu_ntdll.dll.so: main_h.o critsection_h.o signal_h.o qemu_ntdll.spec
	winegcc -shared qemu_ntdll.spec *_h.o -o qemu_ntdll.dll.so

%_g.o: %.c ntdll.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c ntdll.h Makefile
	winegcc $< -c -o $@ $(CFLAGS) -I$(DESTDIR)/build/install/include

clean:
	rm -rf *o *.dll *.so