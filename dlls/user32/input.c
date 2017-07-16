/*
 * Copyright 2017 André Hentschel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_SendInput
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t inputs;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI SendInput(UINT count, LPINPUT inputs, int size)
{
    struct qemu_SendInput call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDINPUT);
    call.count = (uint64_t)count;
    call.inputs = (uint64_t)inputs;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendInput(struct qemu_syscall *call)
{
    struct qemu_SendInput *c = (struct qemu_SendInput *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendInput(c->count, QEMU_G2H(c->inputs), c->size);
}

#endif

struct qemu_keybd_event
{
    struct qemu_syscall super;
    uint64_t bVk;
    uint64_t bScan;
    uint64_t dwFlags;
    uint64_t dwExtraInfo;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI void WINAPI keybd_event(BYTE bVk, BYTE bScan, DWORD dwFlags, ULONG_PTR dwExtraInfo)
{
    struct qemu_keybd_event call;
    call.super.id = QEMU_SYSCALL_ID(CALL_KEYBD_EVENT);
    call.bVk = (uint64_t)bVk;
    call.bScan = (uint64_t)bScan;
    call.dwFlags = (uint64_t)dwFlags;
    call.dwExtraInfo = (uint64_t)dwExtraInfo;

    qemu_syscall(&call.super);

    return;
}

#else

void qemu_keybd_event(struct qemu_syscall *call)
{
    struct qemu_keybd_event *c = (struct qemu_keybd_event *)call;
    WINE_FIXME("Unverified!\n");
    keybd_event(c->bVk, c->bScan, c->dwFlags, c->dwExtraInfo);
}

#endif

struct qemu_mouse_event
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t dx;
    uint64_t dy;
    uint64_t dwData;
    uint64_t dwExtraInfo;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI void WINAPI mouse_event(DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo)
{
    struct qemu_mouse_event call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MOUSE_EVENT);
    call.dwFlags = (uint64_t)dwFlags;
    call.dx = (uint64_t)dx;
    call.dy = (uint64_t)dy;
    call.dwData = (uint64_t)dwData;
    call.dwExtraInfo = (uint64_t)dwExtraInfo;

    qemu_syscall(&call.super);

    return;
}

#else

void qemu_mouse_event(struct qemu_syscall *call)
{
    struct qemu_mouse_event *c = (struct qemu_mouse_event *)call;
    WINE_FIXME("Unverified!\n");
    mouse_event(c->dwFlags, c->dx, c->dy, c->dwData, c->dwExtraInfo);
}

#endif

struct qemu_GetCursorPos
{
    struct qemu_syscall super;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetCursorPos(POINT *pt)
{
    struct qemu_GetCursorPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURSORPOS);
    call.pt = (uint64_t)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCursorPos(struct qemu_syscall *call)
{
    struct qemu_GetCursorPos *c = (struct qemu_GetCursorPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCursorPos(QEMU_G2H(c->pt));
}

#endif

struct qemu_GetCursorInfo
{
    struct qemu_syscall super;
    uint64_t pci;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetCursorInfo(PCURSORINFO pci)
{
    struct qemu_GetCursorInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURSORINFO);
    call.pci = (uint64_t)pci;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCursorInfo(struct qemu_syscall *call)
{
    struct qemu_GetCursorInfo *c = (struct qemu_GetCursorInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCursorInfo(QEMU_G2H(c->pci));
}

#endif

struct qemu_GetPhysicalCursorPos
{
    struct qemu_syscall super;
    uint64_t point;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetPhysicalCursorPos(POINT *point)
{
    struct qemu_GetPhysicalCursorPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPHYSICALCURSORPOS);
    call.point = (uint64_t)point;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetPhysicalCursorPos to Wine headers? */
extern BOOL WINAPI GetPhysicalCursorPos(POINT *point);
void qemu_GetPhysicalCursorPos(struct qemu_syscall *call)
{
    struct qemu_GetPhysicalCursorPos *c = (struct qemu_GetPhysicalCursorPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPhysicalCursorPos(QEMU_G2H(c->point));
}

#endif

struct qemu_SetCursorPos
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetCursorPos(INT x, INT y)
{
    struct qemu_SetCursorPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCURSORPOS);
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCursorPos(struct qemu_syscall *call)
{
    struct qemu_SetCursorPos *c = (struct qemu_SetCursorPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCursorPos(c->x, c->y);
}

#endif

struct qemu_SetPhysicalCursorPos
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetPhysicalCursorPos(INT x, INT y)
{
    struct qemu_SetPhysicalCursorPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPHYSICALCURSORPOS);
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetPhysicalCursorPos to Wine headers? */
extern BOOL WINAPI SetPhysicalCursorPos(INT x, INT y);
void qemu_SetPhysicalCursorPos(struct qemu_syscall *call)
{
    struct qemu_SetPhysicalCursorPos *c = (struct qemu_SetPhysicalCursorPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPhysicalCursorPos(c->x, c->y);
}

#endif

struct qemu_SetCapture
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI SetCapture(HWND hwnd)
{
    struct qemu_SetCapture call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCAPTURE);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_SetCapture(struct qemu_syscall *call)
{
    struct qemu_SetCapture *c = (struct qemu_SetCapture *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetCapture(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_ReleaseCapture
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ReleaseCapture(void)
{
    struct qemu_ReleaseCapture call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RELEASECAPTURE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReleaseCapture(struct qemu_syscall *call)
{
    struct qemu_ReleaseCapture *c = (struct qemu_ReleaseCapture *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReleaseCapture();
}

#endif

struct qemu_GetCapture
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetCapture(void)
{
    struct qemu_GetCapture call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCAPTURE);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetCapture(struct qemu_syscall *call)
{
    struct qemu_GetCapture *c = (struct qemu_GetCapture *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetCapture();
}

#endif

struct qemu_GetAsyncKeyState
{
    struct qemu_syscall super;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI SHORT WINAPI GetAsyncKeyState(INT key)
{
    struct qemu_GetAsyncKeyState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETASYNCKEYSTATE);
    call.key = (uint64_t)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAsyncKeyState(struct qemu_syscall *call)
{
    struct qemu_GetAsyncKeyState *c = (struct qemu_GetAsyncKeyState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAsyncKeyState(c->key);
}

#endif

struct qemu_GetQueueStatus
{
    struct qemu_syscall super;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetQueueStatus(UINT flags)
{
    struct qemu_GetQueueStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETQUEUESTATUS);
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetQueueStatus(struct qemu_syscall *call)
{
    struct qemu_GetQueueStatus *c = (struct qemu_GetQueueStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetQueueStatus(c->flags);
}

#endif

struct qemu_GetInputState
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetInputState(void)
{
    struct qemu_GetInputState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETINPUTSTATE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetInputState(struct qemu_syscall *call)
{
    struct qemu_GetInputState *c = (struct qemu_GetInputState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetInputState();
}

#endif

struct qemu_GetLastInputInfo
{
    struct qemu_syscall super;
    uint64_t plii;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetLastInputInfo(PLASTINPUTINFO plii)
{
    struct qemu_GetLastInputInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLASTINPUTINFO);
    call.plii = (uint64_t)plii;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLastInputInfo(struct qemu_syscall *call)
{
    struct qemu_GetLastInputInfo *c = (struct qemu_GetLastInputInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetLastInputInfo(QEMU_G2H(c->plii));
}

#endif

struct qemu_GetRawInputDeviceList
{
    struct qemu_syscall super;
    uint64_t devices;
    uint64_t device_count;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetRawInputDeviceList(RAWINPUTDEVICELIST *devices, UINT *device_count, UINT size)
{
    struct qemu_GetRawInputDeviceList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETRAWINPUTDEVICELIST);
    call.devices = (uint64_t)devices;
    call.device_count = (uint64_t)device_count;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRawInputDeviceList(struct qemu_syscall *call)
{
    struct qemu_GetRawInputDeviceList *c = (struct qemu_GetRawInputDeviceList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetRawInputDeviceList(QEMU_G2H(c->devices), QEMU_G2H(c->device_count), c->size);
}

#endif

struct qemu_GetRawInputData
{
    struct qemu_syscall super;
    uint64_t rawinput;
    uint64_t command;
    uint64_t data;
    uint64_t data_size;
    uint64_t header_size;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetRawInputData(HRAWINPUT rawinput, UINT command, void *data, UINT *data_size, UINT header_size)
{
    struct qemu_GetRawInputData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETRAWINPUTDATA);
    call.rawinput = (uint64_t)rawinput;
    call.command = (uint64_t)command;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;
    call.header_size = (uint64_t)header_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRawInputData(struct qemu_syscall *call)
{
    struct qemu_GetRawInputData *c = (struct qemu_GetRawInputData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetRawInputData(QEMU_G2H(c->rawinput), c->command, QEMU_G2H(c->data), QEMU_G2H(c->data_size), c->header_size);
}

#endif

struct qemu_GetRawInputBuffer
{
    struct qemu_syscall super;
    uint64_t pData;
    uint64_t pcbSize;
    uint64_t cbSizeHeader;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetRawInputBuffer(PRAWINPUT pData, PUINT pcbSize, UINT cbSizeHeader)
{
    struct qemu_GetRawInputBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETRAWINPUTBUFFER);
    call.pData = (uint64_t)pData;
    call.pcbSize = (uint64_t)pcbSize;
    call.cbSizeHeader = (uint64_t)cbSizeHeader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRawInputBuffer(struct qemu_syscall *call)
{
    struct qemu_GetRawInputBuffer *c = (struct qemu_GetRawInputBuffer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetRawInputBuffer(QEMU_G2H(c->pData), QEMU_G2H(c->pcbSize), c->cbSizeHeader);
}

#endif

struct qemu_GetRawInputDeviceInfoA
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t command;
    uint64_t data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetRawInputDeviceInfoA(HANDLE device, UINT command, void *data, UINT *data_size)
{
    struct qemu_GetRawInputDeviceInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETRAWINPUTDEVICEINFOA);
    call.device = (uint64_t)device;
    call.command = (uint64_t)command;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRawInputDeviceInfoA(struct qemu_syscall *call)
{
    struct qemu_GetRawInputDeviceInfoA *c = (struct qemu_GetRawInputDeviceInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetRawInputDeviceInfoA(QEMU_G2H(c->device), c->command, QEMU_G2H(c->data), QEMU_G2H(c->data_size));
}

#endif

struct qemu_GetRawInputDeviceInfoW
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t command;
    uint64_t data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetRawInputDeviceInfoW(HANDLE device, UINT command, void *data, UINT *data_size)
{
    struct qemu_GetRawInputDeviceInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETRAWINPUTDEVICEINFOW);
    call.device = (uint64_t)device;
    call.command = (uint64_t)command;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRawInputDeviceInfoW(struct qemu_syscall *call)
{
    struct qemu_GetRawInputDeviceInfoW *c = (struct qemu_GetRawInputDeviceInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetRawInputDeviceInfoW(QEMU_G2H(c->device), c->command, QEMU_G2H(c->data), QEMU_G2H(c->data_size));
}

#endif

struct qemu_GetRegisteredRawInputDevices
{
    struct qemu_syscall super;
    uint64_t pRawInputDevices;
    uint64_t puiNumDevices;
    uint64_t cbSize;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetRegisteredRawInputDevices(PRAWINPUTDEVICE pRawInputDevices, PUINT puiNumDevices, UINT cbSize)
{
    struct qemu_GetRegisteredRawInputDevices call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETREGISTEREDRAWINPUTDEVICES);
    call.pRawInputDevices = (uint64_t)pRawInputDevices;
    call.puiNumDevices = (uint64_t)puiNumDevices;
    call.cbSize = (uint64_t)cbSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRegisteredRawInputDevices(struct qemu_syscall *call)
{
    struct qemu_GetRegisteredRawInputDevices *c = (struct qemu_GetRegisteredRawInputDevices *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetRegisteredRawInputDevices(QEMU_G2H(c->pRawInputDevices), QEMU_G2H(c->puiNumDevices), c->cbSize);
}

#endif

struct qemu_DefRawInputProc
{
    struct qemu_syscall super;
    uint64_t paRawInput;
    uint64_t nInput;
    uint64_t cbSizeHeader;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI DefRawInputProc(PRAWINPUT *paRawInput, INT nInput, UINT cbSizeHeader)
{
    struct qemu_DefRawInputProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFRAWINPUTPROC);
    call.paRawInput = (uint64_t)paRawInput;
    call.nInput = (uint64_t)nInput;
    call.cbSizeHeader = (uint64_t)cbSizeHeader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefRawInputProc(struct qemu_syscall *call)
{
    struct qemu_DefRawInputProc *c = (struct qemu_DefRawInputProc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DefRawInputProc(QEMU_G2H(c->paRawInput), c->nInput, c->cbSizeHeader);
}

#endif

struct qemu_AttachThreadInput
{
    struct qemu_syscall super;
    uint64_t from;
    uint64_t to;
    uint64_t attach;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI AttachThreadInput(DWORD from, DWORD to, BOOL attach)
{
    struct qemu_AttachThreadInput call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATTACHTHREADINPUT);
    call.from = (uint64_t)from;
    call.to = (uint64_t)to;
    call.attach = (uint64_t)attach;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AttachThreadInput(struct qemu_syscall *call)
{
    struct qemu_AttachThreadInput *c = (struct qemu_AttachThreadInput *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AttachThreadInput(c->from, c->to, c->attach);
}

#endif

struct qemu_GetKeyState
{
    struct qemu_syscall super;
    uint64_t vkey;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI SHORT WINAPI GetKeyState(INT vkey)
{
    struct qemu_GetKeyState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKEYSTATE);
    call.vkey = (uint64_t)vkey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKeyState(struct qemu_syscall *call)
{
    struct qemu_GetKeyState *c = (struct qemu_GetKeyState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetKeyState(c->vkey);
}

#endif

struct qemu_GetKeyboardState
{
    struct qemu_syscall super;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetKeyboardState(LPBYTE state)
{
    struct qemu_GetKeyboardState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKEYBOARDSTATE);
    call.state = (uint64_t)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKeyboardState(struct qemu_syscall *call)
{
    struct qemu_GetKeyboardState *c = (struct qemu_GetKeyboardState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetKeyboardState(QEMU_G2H(c->state));
}

#endif

struct qemu_SetKeyboardState
{
    struct qemu_syscall super;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetKeyboardState(LPBYTE state)
{
    struct qemu_SetKeyboardState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETKEYBOARDSTATE);
    call.state = (uint64_t)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetKeyboardState(struct qemu_syscall *call)
{
    struct qemu_SetKeyboardState *c = (struct qemu_SetKeyboardState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetKeyboardState(QEMU_G2H(c->state));
}

#endif

struct qemu_VkKeyScanA
{
    struct qemu_syscall super;
    uint64_t cChar;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI SHORT WINAPI VkKeyScanA(CHAR cChar)
{
    struct qemu_VkKeyScanA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VKKEYSCANA);
    call.cChar = (uint64_t)cChar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VkKeyScanA(struct qemu_syscall *call)
{
    struct qemu_VkKeyScanA *c = (struct qemu_VkKeyScanA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VkKeyScanA(c->cChar);
}

#endif

struct qemu_VkKeyScanW
{
    struct qemu_syscall super;
    uint64_t cChar;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI SHORT WINAPI VkKeyScanW(WCHAR cChar)
{
    struct qemu_VkKeyScanW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VKKEYSCANW);
    call.cChar = (uint64_t)cChar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VkKeyScanW(struct qemu_syscall *call)
{
    struct qemu_VkKeyScanW *c = (struct qemu_VkKeyScanW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VkKeyScanW(c->cChar);
}

#endif

struct qemu_OemKeyScan
{
    struct qemu_syscall super;
    uint64_t oem;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI OemKeyScan(WORD oem)
{
    struct qemu_OemKeyScan call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OEMKEYSCAN);
    call.oem = (uint64_t)oem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OemKeyScan(struct qemu_syscall *call)
{
    struct qemu_OemKeyScan *c = (struct qemu_OemKeyScan *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OemKeyScan(c->oem);
}

#endif

struct qemu_GetKeyboardType
{
    struct qemu_syscall super;
    uint64_t nTypeFlag;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetKeyboardType(INT nTypeFlag)
{
    struct qemu_GetKeyboardType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKEYBOARDTYPE);
    call.nTypeFlag = (uint64_t)nTypeFlag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKeyboardType(struct qemu_syscall *call)
{
    struct qemu_GetKeyboardType *c = (struct qemu_GetKeyboardType *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetKeyboardType(c->nTypeFlag);
}

#endif

struct qemu_MapVirtualKeyA
{
    struct qemu_syscall super;
    uint64_t code;
    uint64_t maptype;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI MapVirtualKeyA(UINT code, UINT maptype)
{
    struct qemu_MapVirtualKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAPVIRTUALKEYA);
    call.code = (uint64_t)code;
    call.maptype = (uint64_t)maptype;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MapVirtualKeyA(struct qemu_syscall *call)
{
    struct qemu_MapVirtualKeyA *c = (struct qemu_MapVirtualKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MapVirtualKeyA(c->code, c->maptype);
}

#endif

struct qemu_MapVirtualKeyW
{
    struct qemu_syscall super;
    uint64_t code;
    uint64_t maptype;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI MapVirtualKeyW(UINT code, UINT maptype)
{
    struct qemu_MapVirtualKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAPVIRTUALKEYW);
    call.code = (uint64_t)code;
    call.maptype = (uint64_t)maptype;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MapVirtualKeyW(struct qemu_syscall *call)
{
    struct qemu_MapVirtualKeyW *c = (struct qemu_MapVirtualKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MapVirtualKeyW(c->code, c->maptype);
}

#endif

struct qemu_MapVirtualKeyExA
{
    struct qemu_syscall super;
    uint64_t code;
    uint64_t maptype;
    uint64_t hkl;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI MapVirtualKeyExA(UINT code, UINT maptype, HKL hkl)
{
    struct qemu_MapVirtualKeyExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAPVIRTUALKEYEXA);
    call.code = (uint64_t)code;
    call.maptype = (uint64_t)maptype;
    call.hkl = (uint64_t)hkl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MapVirtualKeyExA(struct qemu_syscall *call)
{
    struct qemu_MapVirtualKeyExA *c = (struct qemu_MapVirtualKeyExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MapVirtualKeyExA(c->code, c->maptype, QEMU_G2H(c->hkl));
}

#endif

struct qemu_MapVirtualKeyExW
{
    struct qemu_syscall super;
    uint64_t code;
    uint64_t maptype;
    uint64_t hkl;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI MapVirtualKeyExW(UINT code, UINT maptype, HKL hkl)
{
    struct qemu_MapVirtualKeyExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAPVIRTUALKEYEXW);
    call.code = (uint64_t)code;
    call.maptype = (uint64_t)maptype;
    call.hkl = (uint64_t)hkl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MapVirtualKeyExW(struct qemu_syscall *call)
{
    struct qemu_MapVirtualKeyExW *c = (struct qemu_MapVirtualKeyExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MapVirtualKeyExW(c->code, c->maptype, QEMU_G2H(c->hkl));
}

#endif

struct qemu_GetKBCodePage
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetKBCodePage(void)
{
    struct qemu_GetKBCodePage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKBCODEPAGE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKBCodePage(struct qemu_syscall *call)
{
    struct qemu_GetKBCodePage *c = (struct qemu_GetKBCodePage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetKBCodePage();
}

#endif

struct qemu_GetKeyboardLayout
{
    struct qemu_syscall super;
    uint64_t thread_id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HKL WINAPI GetKeyboardLayout(DWORD thread_id)
{
    struct qemu_GetKeyboardLayout call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKEYBOARDLAYOUT);
    call.thread_id = (uint64_t)thread_id;

    qemu_syscall(&call.super);

    return (HKL)call.super.iret;
}

#else

void qemu_GetKeyboardLayout(struct qemu_syscall *call)
{
    struct qemu_GetKeyboardLayout *c = (struct qemu_GetKeyboardLayout *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetKeyboardLayout(c->thread_id);
}

#endif

struct qemu_GetKeyboardLayoutNameA
{
    struct qemu_syscall super;
    uint64_t pszKLID;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetKeyboardLayoutNameA(LPSTR pszKLID)
{
    struct qemu_GetKeyboardLayoutNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKEYBOARDLAYOUTNAMEA);
    call.pszKLID = (uint64_t)pszKLID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKeyboardLayoutNameA(struct qemu_syscall *call)
{
    struct qemu_GetKeyboardLayoutNameA *c = (struct qemu_GetKeyboardLayoutNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetKeyboardLayoutNameA(QEMU_G2H(c->pszKLID));
}

#endif

struct qemu_GetKeyboardLayoutNameW
{
    struct qemu_syscall super;
    uint64_t pwszKLID;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetKeyboardLayoutNameW(LPWSTR pwszKLID)
{
    struct qemu_GetKeyboardLayoutNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKEYBOARDLAYOUTNAMEW);
    call.pwszKLID = (uint64_t)pwszKLID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKeyboardLayoutNameW(struct qemu_syscall *call)
{
    struct qemu_GetKeyboardLayoutNameW *c = (struct qemu_GetKeyboardLayoutNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetKeyboardLayoutNameW(QEMU_G2H(c->pwszKLID));
}

#endif

struct qemu_GetKeyNameTextA
{
    struct qemu_syscall super;
    uint64_t lParam;
    uint64_t lpBuffer;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetKeyNameTextA(LONG lParam, LPSTR lpBuffer, INT nSize)
{
    struct qemu_GetKeyNameTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKEYNAMETEXTA);
    call.lParam = (uint64_t)lParam;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.nSize = (uint64_t)nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKeyNameTextA(struct qemu_syscall *call)
{
    struct qemu_GetKeyNameTextA *c = (struct qemu_GetKeyNameTextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetKeyNameTextA(c->lParam, QEMU_G2H(c->lpBuffer), c->nSize);
}

#endif

struct qemu_GetKeyNameTextW
{
    struct qemu_syscall super;
    uint64_t lParam;
    uint64_t lpBuffer;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetKeyNameTextW(LONG lParam, LPWSTR lpBuffer, INT nSize)
{
    struct qemu_GetKeyNameTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKEYNAMETEXTW);
    call.lParam = (uint64_t)lParam;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.nSize = (uint64_t)nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKeyNameTextW(struct qemu_syscall *call)
{
    struct qemu_GetKeyNameTextW *c = (struct qemu_GetKeyNameTextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetKeyNameTextW(c->lParam, QEMU_G2H(c->lpBuffer), c->nSize);
}

#endif

struct qemu_ToUnicode
{
    struct qemu_syscall super;
    uint64_t virtKey;
    uint64_t scanCode;
    uint64_t lpKeyState;
    uint64_t lpwStr;
    uint64_t size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI ToUnicode(UINT virtKey, UINT scanCode, const BYTE *lpKeyState, LPWSTR lpwStr, int size, UINT flags)
{
    struct qemu_ToUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOUNICODE);
    call.virtKey = (uint64_t)virtKey;
    call.scanCode = (uint64_t)scanCode;
    call.lpKeyState = (uint64_t)lpKeyState;
    call.lpwStr = (uint64_t)lpwStr;
    call.size = (uint64_t)size;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ToUnicode(struct qemu_syscall *call)
{
    struct qemu_ToUnicode *c = (struct qemu_ToUnicode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ToUnicode(c->virtKey, c->scanCode, QEMU_G2H(c->lpKeyState), QEMU_G2H(c->lpwStr), c->size, c->flags);
}

#endif

struct qemu_ToUnicodeEx
{
    struct qemu_syscall super;
    uint64_t virtKey;
    uint64_t scanCode;
    uint64_t lpKeyState;
    uint64_t lpwStr;
    uint64_t size;
    uint64_t flags;
    uint64_t hkl;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI ToUnicodeEx(UINT virtKey, UINT scanCode, const BYTE *lpKeyState, LPWSTR lpwStr, int size, UINT flags, HKL hkl)
{
    struct qemu_ToUnicodeEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOUNICODEEX);
    call.virtKey = (uint64_t)virtKey;
    call.scanCode = (uint64_t)scanCode;
    call.lpKeyState = (uint64_t)lpKeyState;
    call.lpwStr = (uint64_t)lpwStr;
    call.size = (uint64_t)size;
    call.flags = (uint64_t)flags;
    call.hkl = (uint64_t)hkl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ToUnicodeEx(struct qemu_syscall *call)
{
    struct qemu_ToUnicodeEx *c = (struct qemu_ToUnicodeEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ToUnicodeEx(c->virtKey, c->scanCode, QEMU_G2H(c->lpKeyState), QEMU_G2H(c->lpwStr), c->size, c->flags, QEMU_G2H(c->hkl));
}

#endif

struct qemu_ToAscii
{
    struct qemu_syscall super;
    uint64_t virtKey;
    uint64_t scanCode;
    uint64_t lpKeyState;
    uint64_t lpChar;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI ToAscii(UINT virtKey, UINT scanCode, const BYTE *lpKeyState, LPWORD lpChar, UINT flags)
{
    struct qemu_ToAscii call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOASCII);
    call.virtKey = (uint64_t)virtKey;
    call.scanCode = (uint64_t)scanCode;
    call.lpKeyState = (uint64_t)lpKeyState;
    call.lpChar = (uint64_t)lpChar;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ToAscii(struct qemu_syscall *call)
{
    struct qemu_ToAscii *c = (struct qemu_ToAscii *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ToAscii(c->virtKey, c->scanCode, QEMU_G2H(c->lpKeyState), QEMU_G2H(c->lpChar), c->flags);
}

#endif

struct qemu_ToAsciiEx
{
    struct qemu_syscall super;
    uint64_t virtKey;
    uint64_t scanCode;
    uint64_t lpKeyState;
    uint64_t lpChar;
    uint64_t flags;
    uint64_t dwhkl;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI ToAsciiEx(UINT virtKey, UINT scanCode, const BYTE *lpKeyState, LPWORD lpChar, UINT flags, HKL dwhkl)
{
    struct qemu_ToAsciiEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOASCIIEX);
    call.virtKey = (uint64_t)virtKey;
    call.scanCode = (uint64_t)scanCode;
    call.lpKeyState = (uint64_t)lpKeyState;
    call.lpChar = (uint64_t)lpChar;
    call.flags = (uint64_t)flags;
    call.dwhkl = (uint64_t)dwhkl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ToAsciiEx(struct qemu_syscall *call)
{
    struct qemu_ToAsciiEx *c = (struct qemu_ToAsciiEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ToAsciiEx(c->virtKey, c->scanCode, QEMU_G2H(c->lpKeyState), QEMU_G2H(c->lpChar), c->flags, QEMU_G2H(c->dwhkl));
}

#endif

struct qemu_ActivateKeyboardLayout
{
    struct qemu_syscall super;
    uint64_t hLayout;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HKL WINAPI ActivateKeyboardLayout(HKL hLayout, UINT flags)
{
    struct qemu_ActivateKeyboardLayout call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACTIVATEKEYBOARDLAYOUT);
    call.hLayout = (uint64_t)hLayout;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return (HKL)call.super.iret;
}

#else

void qemu_ActivateKeyboardLayout(struct qemu_syscall *call)
{
    struct qemu_ActivateKeyboardLayout *c = (struct qemu_ActivateKeyboardLayout *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ActivateKeyboardLayout(QEMU_G2H(c->hLayout), c->flags);
}

#endif

struct qemu_BlockInput
{
    struct qemu_syscall super;
    uint64_t fBlockIt;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI BlockInput(BOOL fBlockIt)
{
    struct qemu_BlockInput call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BLOCKINPUT);
    call.fBlockIt = (uint64_t)fBlockIt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add BlockInput to Wine headers? */
extern BOOL WINAPI BlockInput(BOOL fBlockIt);
void qemu_BlockInput(struct qemu_syscall *call)
{
    struct qemu_BlockInput *c = (struct qemu_BlockInput *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BlockInput(c->fBlockIt);
}

#endif

struct qemu_RegisterHotKey
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t modifiers;
    uint64_t vk;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI RegisterHotKey(HWND hwnd,INT id,UINT modifiers,UINT vk)
{
    struct qemu_RegisterHotKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERHOTKEY);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.modifiers = (uint64_t)modifiers;
    call.vk = (uint64_t)vk;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegisterHotKey(struct qemu_syscall *call)
{
    struct qemu_RegisterHotKey *c = (struct qemu_RegisterHotKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterHotKey(QEMU_G2H(c->hwnd), c->id, c->modifiers, c->vk);
}

#endif

struct qemu_UnregisterHotKey
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UnregisterHotKey(HWND hwnd,INT id)
{
    struct qemu_UnregisterHotKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREGISTERHOTKEY);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnregisterHotKey(struct qemu_syscall *call)
{
    struct qemu_UnregisterHotKey *c = (struct qemu_UnregisterHotKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnregisterHotKey(QEMU_G2H(c->hwnd), c->id);
}

#endif

struct qemu_LoadKeyboardLayoutW
{
    struct qemu_syscall super;
    uint64_t pwszKLID;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HKL WINAPI LoadKeyboardLayoutW(LPCWSTR pwszKLID, UINT Flags)
{
    struct qemu_LoadKeyboardLayoutW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADKEYBOARDLAYOUTW);
    call.pwszKLID = (uint64_t)pwszKLID;
    call.Flags = (uint64_t)Flags;

    qemu_syscall(&call.super);

    return (HKL)call.super.iret;
}

#else

void qemu_LoadKeyboardLayoutW(struct qemu_syscall *call)
{
    struct qemu_LoadKeyboardLayoutW *c = (struct qemu_LoadKeyboardLayoutW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)LoadKeyboardLayoutW(QEMU_G2H(c->pwszKLID), c->Flags);
}

#endif

struct qemu_LoadKeyboardLayoutA
{
    struct qemu_syscall super;
    uint64_t pwszKLID;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HKL WINAPI LoadKeyboardLayoutA(LPCSTR pwszKLID, UINT Flags)
{
    struct qemu_LoadKeyboardLayoutA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADKEYBOARDLAYOUTA);
    call.pwszKLID = (uint64_t)pwszKLID;
    call.Flags = (uint64_t)Flags;

    qemu_syscall(&call.super);

    return (HKL)call.super.iret;
}

#else

void qemu_LoadKeyboardLayoutA(struct qemu_syscall *call)
{
    struct qemu_LoadKeyboardLayoutA *c = (struct qemu_LoadKeyboardLayoutA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)LoadKeyboardLayoutA(QEMU_G2H(c->pwszKLID), c->Flags);
}

#endif

struct qemu_UnloadKeyboardLayout
{
    struct qemu_syscall super;
    uint64_t hkl;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UnloadKeyboardLayout(HKL hkl)
{
    struct qemu_UnloadKeyboardLayout call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNLOADKEYBOARDLAYOUT);
    call.hkl = (uint64_t)hkl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnloadKeyboardLayout(struct qemu_syscall *call)
{
    struct qemu_UnloadKeyboardLayout *c = (struct qemu_UnloadKeyboardLayout *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnloadKeyboardLayout(QEMU_G2H(c->hkl));
}

#endif

struct qemu_TrackMouseEvent
{
    struct qemu_syscall super;
    uint64_t ptme;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI TrackMouseEvent (TRACKMOUSEEVENT *ptme)
{
    struct qemu_TrackMouseEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRACKMOUSEEVENT);
    call.ptme = (uint64_t)ptme;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TrackMouseEvent(struct qemu_syscall *call)
{
    struct qemu_TrackMouseEvent *c = (struct qemu_TrackMouseEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TrackMouseEvent(QEMU_G2H(c->ptme));
}

#endif
