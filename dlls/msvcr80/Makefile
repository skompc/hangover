SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_MSVCR80
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -D_MSVCR_VER=80
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: msvcr80.dll qemu_msvcr80.dll.so

msvcr80.dll: msvcr80.spec cpp_g.o ctype_g.o data_g.o dir_g.o environ_g.o errno_g.o except_g.o exit_g.o file_g.o heap_g.o locale_g.o lock_g.o main_g.o math_g.o mbcs_g.o misc_g.o process_g.o scanf_g.o string_g.o time_g.o wcs_g.o thread_g.o console_g.o scheduler_g.o undname_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/msvcr80.spec *_g.o -o msvcr80.dll -lkernel32 -l ntdll -nodefaultlibs -nostdlib -Wl,--image-base,0x1d0000000

qemu_msvcr80.dll.so: qemu_msvcr80.spec cpp_h.o ctype_h.o data_h.o dir_h.o environ_h.o errno_h.o except_h.o exit_h.o file_h.o heap_h.o locale_h.o lock_h.o main_h.o math_h.o mbcs_h.o misc_h.o process_h.o scanf_h.o string_h.o time_h.o wcs_h.o thread_h.o console_h.o scheduler_h.o undname_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_msvcr80.spec *_h.o -o qemu_msvcr80.dll.so

%_g.o: %.c qemu_msvcrt.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_msvcrt.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
