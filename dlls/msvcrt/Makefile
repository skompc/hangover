SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_MSVCRT
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -D_MSVCR_VER=0
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: msvcrt.dll qemu_msvcrt.dll.so

msvcrt.dll: console_g.o cpp_g.o ctype_g.o data_g.o dir_g.o environ_g.o errno_g.o except_g.o exit_g.o file_g.o heap_g.o locale_g.o lock_g.o main_g.o math_g.o mbcs_g.o misc_g.o msvcrt.def process_g.o scanf_g.o scheduler_g.o string_g.o thread_g.o time_g.o undname_g.o wcs_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/msvcrt.spec *_g.o -o msvcrt.dll -lkernel32 -l ntdll -nodefaultlibs -nostdlib -Wl,--image-base,0x30000000 -lntdll

qemu_msvcrt.dll.so: console_h.o cpp_h.o ctype_h.o data_h.o dir_h.o environ_h.o errno_h.o except_h.o exit_h.o file_h.o heap_h.o locale_h.o lock_h.o main_h.o math_h.o mbcs_h.o misc_h.o process_h.o qemu_msvcrt.spec scanf_h.o scheduler_h.o string_h.o thread_h.o time_h.o undname_h.o wcs_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_msvcrt.spec *_h.o -o qemu_msvcrt.dll.so

%_g.o: %.c qemu_msvcrt.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_msvcrt.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
