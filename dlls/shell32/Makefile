SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_SHELL32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DNTDDI_VERSION=0x06020000 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: shell32.dll qemu_shell32.dll.so

shell32.dll: appbar_g.o assoc_g.o brsfolder_g.o changenotify_g.o control_g.o dde_g.o dialogs_g.o iconcache_g.o main_g.o pidl_g.o recyclebin_g.o shell32.spec shell32_main_g.o shellitem_g.o shellole_g.o shellord_g.o shellpath_g.o shellreg_g.o shellstring_g.o shlexec_g.o shlfileop_g.o shlfolder_g.o shlmenu_g.o shlview_g.o shpolicy_g.o systray_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/shell32.spec *_g.o -o shell32.dll -nodefaultlibs -nostdlib -Wl,--image-base,0x80000000

qemu_shell32.dll.so: appbar_h.o assoc_h.o brsfolder_h.o changenotify_h.o control_h.o dde_h.o dialogs_h.o iconcache_h.o main_h.o pidl_h.o recyclebin_h.o shell32_main_h.o shellitem_h.o shellole_h.o shellord_h.o shellpath_h.o shellreg_h.o shellstring_h.o shlexec_h.o shlfileop_h.o shlfolder_h.o shlmenu_h.o shlview_h.o shpolicy_h.o systray_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_shell32.spec *_h.o -o qemu_shell32.dll.so -lshell32

%_g.o: %.c qemu_shell32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_shell32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
