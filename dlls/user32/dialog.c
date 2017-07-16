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


struct qemu_CreateDialogParamA
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t name;
    uint64_t owner;
    uint64_t dlgProc;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI CreateDialogParamA(HINSTANCE hInst, LPCSTR name, HWND owner, DLGPROC dlgProc, LPARAM param)
{
    struct qemu_CreateDialogParamA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDIALOGPARAMA);
    call.hInst = (uint64_t)hInst;
    call.name = (uint64_t)name;
    call.owner = (uint64_t)owner;
    call.dlgProc = (uint64_t)dlgProc;
    call.param = (uint64_t)param;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_CreateDialogParamA(struct qemu_syscall *call)
{
    struct qemu_CreateDialogParamA *c = (struct qemu_CreateDialogParamA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateDialogParamA(QEMU_G2H(c->hInst), QEMU_G2H(c->name), QEMU_G2H(c->owner), QEMU_G2H(c->dlgProc), c->param);
}

#endif

struct qemu_CreateDialogParamW
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t name;
    uint64_t owner;
    uint64_t dlgProc;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI CreateDialogParamW(HINSTANCE hInst, LPCWSTR name, HWND owner, DLGPROC dlgProc, LPARAM param)
{
    struct qemu_CreateDialogParamW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDIALOGPARAMW);
    call.hInst = (uint64_t)hInst;
    call.name = (uint64_t)name;
    call.owner = (uint64_t)owner;
    call.dlgProc = (uint64_t)dlgProc;
    call.param = (uint64_t)param;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_CreateDialogParamW(struct qemu_syscall *call)
{
    struct qemu_CreateDialogParamW *c = (struct qemu_CreateDialogParamW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateDialogParamW(QEMU_G2H(c->hInst), QEMU_G2H(c->name), QEMU_G2H(c->owner), QEMU_G2H(c->dlgProc), c->param);
}

#endif

struct qemu_CreateDialogIndirectParamAorW
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t dlgTemplate;
    uint64_t owner;
    uint64_t dlgProc;
    uint64_t param;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI CreateDialogIndirectParamAorW(HINSTANCE hInst, LPCVOID dlgTemplate, HWND owner, DLGPROC dlgProc, LPARAM param, DWORD flags)
{
    struct qemu_CreateDialogIndirectParamAorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDIALOGINDIRECTPARAMAORW);
    call.hInst = (uint64_t)hInst;
    call.dlgTemplate = (uint64_t)dlgTemplate;
    call.owner = (uint64_t)owner;
    call.dlgProc = (uint64_t)dlgProc;
    call.param = (uint64_t)param;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

/* TODO: Add CreateDialogIndirectParamAorW to Wine headers? */
extern HWND WINAPI CreateDialogIndirectParamAorW(HINSTANCE hInst, LPCVOID dlgTemplate, HWND owner, DLGPROC dlgProc, LPARAM param, DWORD flags);
void qemu_CreateDialogIndirectParamAorW(struct qemu_syscall *call)
{
    struct qemu_CreateDialogIndirectParamAorW *c = (struct qemu_CreateDialogIndirectParamAorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateDialogIndirectParamAorW(QEMU_G2H(c->hInst), QEMU_G2H(c->dlgTemplate), QEMU_G2H(c->owner), QEMU_G2H(c->dlgProc), c->param, c->flags);
}

#endif

struct qemu_CreateDialogIndirectParamA
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t dlgTemplate;
    uint64_t owner;
    uint64_t dlgProc;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI CreateDialogIndirectParamA(HINSTANCE hInst, LPCDLGTEMPLATEA dlgTemplate, HWND owner, DLGPROC dlgProc, LPARAM param)
{
    struct qemu_CreateDialogIndirectParamA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDIALOGINDIRECTPARAMA);
    call.hInst = (uint64_t)hInst;
    call.dlgTemplate = (uint64_t)dlgTemplate;
    call.owner = (uint64_t)owner;
    call.dlgProc = (uint64_t)dlgProc;
    call.param = (uint64_t)param;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_CreateDialogIndirectParamA(struct qemu_syscall *call)
{
    struct qemu_CreateDialogIndirectParamA *c = (struct qemu_CreateDialogIndirectParamA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateDialogIndirectParamA(QEMU_G2H(c->hInst), QEMU_G2H(c->dlgTemplate), QEMU_G2H(c->owner), QEMU_G2H(c->dlgProc), c->param);
}

#endif

struct qemu_CreateDialogIndirectParamW
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t dlgTemplate;
    uint64_t owner;
    uint64_t dlgProc;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI CreateDialogIndirectParamW(HINSTANCE hInst, LPCDLGTEMPLATEW dlgTemplate, HWND owner, DLGPROC dlgProc, LPARAM param)
{
    struct qemu_CreateDialogIndirectParamW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDIALOGINDIRECTPARAMW);
    call.hInst = (uint64_t)hInst;
    call.dlgTemplate = (uint64_t)dlgTemplate;
    call.owner = (uint64_t)owner;
    call.dlgProc = (uint64_t)dlgProc;
    call.param = (uint64_t)param;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_CreateDialogIndirectParamW(struct qemu_syscall *call)
{
    struct qemu_CreateDialogIndirectParamW *c = (struct qemu_CreateDialogIndirectParamW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateDialogIndirectParamW(QEMU_G2H(c->hInst), QEMU_G2H(c->dlgTemplate), QEMU_G2H(c->owner), QEMU_G2H(c->dlgProc), c->param);
}

#endif

struct qemu_DialogBoxParam
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t name;
    uint64_t owner;
    uint64_t dlgProc;
    uint64_t param;
    uint64_t guest_wrapper;
};

struct qemu_dlgproc_cb
{
    uint64_t guest_proc;
    uint64_t dlg, msg, wp, lp;
};

#ifdef QEMU_DLL_GUEST

static uint64_t guest_wrapper(const struct qemu_dlgproc_cb *cb)
{
    DLGPROC guest_proc = (DLGPROC)cb->guest_proc;
    return guest_proc((HWND)cb->dlg, cb->msg, cb->wp, cb->lp);
}

WINUSERAPI INT_PTR WINAPI DialogBoxParamA(HINSTANCE hInst, LPCSTR name, HWND owner, DLGPROC dlgProc, LPARAM param)
{
    struct qemu_DialogBoxParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIALOGBOXPARAMA);
    call.hInst = (uint64_t)hInst;
    call.name = (uint64_t)name;
    call.owner = (uint64_t)owner;
    call.dlgProc = (uint64_t)dlgProc;
    call.param = (uint64_t)param;
    call.guest_wrapper = (uint64_t)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI INT_PTR WINAPI DialogBoxParamW(HINSTANCE hInst, LPCWSTR name, HWND owner, DLGPROC dlgProc, LPARAM param)
{
    struct qemu_DialogBoxParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIALOGBOXPARAMW);
    call.hInst = (uint64_t)hInst;
    call.name = (uint64_t)name;
    call.owner = (uint64_t)owner;
    call.dlgProc = (uint64_t)dlgProc;
    call.param = (uint64_t)param;
    call.guest_wrapper = (uint64_t)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static uint64_t guest_wrapper;

static INT_PTR WINAPI dlgproc_wrapper(HWND dlg, UINT msg, WPARAM wp, LPARAM lp)
{
    uint64_t *dlgproc = TlsGetValue(user32_tls);
    uint64_t ret;
    struct qemu_dlgproc_cb call = {*dlgproc, (uint64_t)dlg, msg, wp, lp};

    WINE_TRACE("Calling guest proc 0x%lx(%p, %u, %lu, %lu).\n", *dlgproc, dlg, msg, wp, lp);
    ret = qemu_ops->qemu_execute(QEMU_G2H(guest_wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest proc returned %lu\n", ret);

    return ret;
}

void qemu_DialogBoxParam(struct qemu_syscall *call)
{
    struct qemu_DialogBoxParam *c = (struct qemu_DialogBoxParam *)call;
    HINSTANCE instance;
    uint64_t dlgproc;
    WINE_TRACE("\n");

    instance = (HINSTANCE)c->hInst;
    if (!instance)
        instance = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

    dlgproc = c->dlgProc;
    guest_wrapper = c->guest_wrapper;
    TlsSetValue(user32_tls, &dlgproc);

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_DIALOGBOXPARAMA):
            c->super.iret = DialogBoxParamA(instance, QEMU_G2H(c->name), QEMU_G2H(c->owner),
                    dlgproc_wrapper, c->param);
            break;

        case QEMU_SYSCALL_ID(CALL_DIALOGBOXPARAMW):
            c->super.iret = DialogBoxParamW(instance, QEMU_G2H(c->name), QEMU_G2H(c->owner),
                    dlgproc_wrapper, c->param);
            break;

        default:
            WINE_ERR("Unreachable code, id %16lx.\n", c->super.id);
    }
}

#endif

struct qemu_DialogBoxIndirectParamAorW
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t template;
    uint64_t owner;
    uint64_t dlgProc;
    uint64_t param;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT_PTR WINAPI DialogBoxIndirectParamAorW(HINSTANCE hInstance, LPCVOID template, HWND owner, DLGPROC dlgProc, LPARAM param, DWORD flags)
{
    struct qemu_DialogBoxIndirectParamAorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIALOGBOXINDIRECTPARAMAORW);
    call.hInstance = (uint64_t)hInstance;
    call.template = (uint64_t)template;
    call.owner = (uint64_t)owner;
    call.dlgProc = (uint64_t)dlgProc;
    call.param = (uint64_t)param;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DialogBoxIndirectParamAorW to Wine headers? */
extern INT_PTR WINAPI DialogBoxIndirectParamAorW(HINSTANCE hInstance, LPCVOID template, HWND owner, DLGPROC dlgProc, LPARAM param, DWORD flags);
void qemu_DialogBoxIndirectParamAorW(struct qemu_syscall *call)
{
    struct qemu_DialogBoxIndirectParamAorW *c = (struct qemu_DialogBoxIndirectParamAorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DialogBoxIndirectParamAorW(QEMU_G2H(c->hInstance), QEMU_G2H(c->template), QEMU_G2H(c->owner), QEMU_G2H(c->dlgProc), c->param, c->flags);
}

#endif

struct qemu_DialogBoxIndirectParamA
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t template;
    uint64_t owner;
    uint64_t dlgProc;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT_PTR WINAPI DialogBoxIndirectParamA(HINSTANCE hInstance, LPCDLGTEMPLATEA template, HWND owner, DLGPROC dlgProc, LPARAM param)
{
    struct qemu_DialogBoxIndirectParamA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIALOGBOXINDIRECTPARAMA);
    call.hInstance = (uint64_t)hInstance;
    call.template = (uint64_t)template;
    call.owner = (uint64_t)owner;
    call.dlgProc = (uint64_t)dlgProc;
    call.param = (uint64_t)param;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DialogBoxIndirectParamA(struct qemu_syscall *call)
{
    struct qemu_DialogBoxIndirectParamA *c = (struct qemu_DialogBoxIndirectParamA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DialogBoxIndirectParamA(QEMU_G2H(c->hInstance), QEMU_G2H(c->template), QEMU_G2H(c->owner), QEMU_G2H(c->dlgProc), c->param);
}

#endif

struct qemu_DialogBoxIndirectParamW
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t template;
    uint64_t owner;
    uint64_t dlgProc;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT_PTR WINAPI DialogBoxIndirectParamW(HINSTANCE hInstance, LPCDLGTEMPLATEW template, HWND owner, DLGPROC dlgProc, LPARAM param)
{
    struct qemu_DialogBoxIndirectParamW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIALOGBOXINDIRECTPARAMW);
    call.hInstance = (uint64_t)hInstance;
    call.template = (uint64_t)template;
    call.owner = (uint64_t)owner;
    call.dlgProc = (uint64_t)dlgProc;
    call.param = (uint64_t)param;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DialogBoxIndirectParamW(struct qemu_syscall *call)
{
    struct qemu_DialogBoxIndirectParamW *c = (struct qemu_DialogBoxIndirectParamW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DialogBoxIndirectParamW(QEMU_G2H(c->hInstance), QEMU_G2H(c->template), QEMU_G2H(c->owner), QEMU_G2H(c->dlgProc), c->param);
}

#endif

struct qemu_EndDialog
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t retval;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EndDialog(HWND hwnd, INT_PTR retval)
{
    struct qemu_EndDialog call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENDDIALOG);
    call.hwnd = (uint64_t)hwnd;
    call.retval = (uint64_t)retval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EndDialog(struct qemu_syscall *call)
{
    struct qemu_EndDialog *c = (struct qemu_EndDialog *)call;
    WINE_TRACE("\n");
    c->super.iret = EndDialog(QEMU_G2H(c->hwnd), c->retval);
}

#endif

struct qemu_IsDialogMessageW
{
    struct qemu_syscall super;
    uint64_t hwndDlg;
    uint64_t msg;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsDialogMessageW(HWND hwndDlg, LPMSG msg)
{
    struct qemu_IsDialogMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISDIALOGMESSAGEW);
    call.hwndDlg = (uint64_t)hwndDlg;
    call.msg = (uint64_t)msg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsDialogMessageW(struct qemu_syscall *call)
{
    struct qemu_IsDialogMessageW *c = (struct qemu_IsDialogMessageW *)call;
    WINE_TRACE("\n");
    c->super.iret = IsDialogMessageW(QEMU_G2H(c->hwndDlg), QEMU_G2H(c->msg));
}

#endif

struct qemu_GetDlgCtrlID
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetDlgCtrlID(HWND hwnd)
{
    struct qemu_GetDlgCtrlID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDLGCTRLID);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDlgCtrlID(struct qemu_syscall *call)
{
    struct qemu_GetDlgCtrlID *c = (struct qemu_GetDlgCtrlID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDlgCtrlID(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetDlgItem
{
    struct qemu_syscall super;
    uint64_t hwndDlg;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetDlgItem(HWND hwndDlg, INT id)
{
    struct qemu_GetDlgItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDLGITEM);
    call.hwndDlg = (uint64_t)hwndDlg;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetDlgItem(struct qemu_syscall *call)
{
    struct qemu_GetDlgItem *c = (struct qemu_GetDlgItem *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GetDlgItem(QEMU_G2H(c->hwndDlg), c->id);
}

#endif

struct qemu_SendDlgItemMessageA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI SendDlgItemMessageA(HWND hwnd, INT id, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_SendDlgItemMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDDLGITEMMESSAGEA);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.msg = (uint64_t)msg;
    call.wParam = (uint64_t)wParam;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendDlgItemMessageA(struct qemu_syscall *call)
{
    struct qemu_SendDlgItemMessageA *c = (struct qemu_SendDlgItemMessageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendDlgItemMessageA(QEMU_G2H(c->hwnd), c->id, c->msg, c->wParam, c->lParam);
}

#endif

struct qemu_SendDlgItemMessageW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI SendDlgItemMessageW(HWND hwnd, INT id, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_SendDlgItemMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDDLGITEMMESSAGEW);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.msg = (uint64_t)msg;
    call.wParam = (uint64_t)wParam;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendDlgItemMessageW(struct qemu_syscall *call)
{
    struct qemu_SendDlgItemMessageW *c = (struct qemu_SendDlgItemMessageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendDlgItemMessageW(QEMU_G2H(c->hwnd), c->id, c->msg, c->wParam, c->lParam);
}

#endif

struct qemu_SetDlgItemTextA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t lpString;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetDlgItemTextA(HWND hwnd, INT id, LPCSTR lpString)
{
    struct qemu_SetDlgItemTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDLGITEMTEXTA);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.lpString = (uint64_t)lpString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDlgItemTextA(struct qemu_syscall *call)
{
    struct qemu_SetDlgItemTextA *c = (struct qemu_SetDlgItemTextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetDlgItemTextA(QEMU_G2H(c->hwnd), c->id, QEMU_G2H(c->lpString));
}

#endif

struct qemu_SetDlgItemTextW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t lpString;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetDlgItemTextW(HWND hwnd, INT id, LPCWSTR lpString)
{
    struct qemu_SetDlgItemTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDLGITEMTEXTW);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.lpString = (uint64_t)lpString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDlgItemTextW(struct qemu_syscall *call)
{
    struct qemu_SetDlgItemTextW *c = (struct qemu_SetDlgItemTextW *)call;
    WINE_TRACE("\n");
    c->super.iret = SetDlgItemTextW(QEMU_G2H(c->hwnd), c->id, QEMU_G2H(c->lpString));
}

#endif

struct qemu_GetDlgItemTextA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetDlgItemTextA(HWND hwnd, INT id, LPSTR str, INT len)
{
    struct qemu_GetDlgItemTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDLGITEMTEXTA);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.str = (uint64_t)str;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDlgItemTextA(struct qemu_syscall *call)
{
    struct qemu_GetDlgItemTextA *c = (struct qemu_GetDlgItemTextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDlgItemTextA(QEMU_G2H(c->hwnd), c->id, QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_GetDlgItemTextW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetDlgItemTextW(HWND hwnd, INT id, LPWSTR str, INT len)
{
    struct qemu_GetDlgItemTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDLGITEMTEXTW);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.str = (uint64_t)str;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDlgItemTextW(struct qemu_syscall *call)
{
    struct qemu_GetDlgItemTextW *c = (struct qemu_GetDlgItemTextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDlgItemTextW(QEMU_G2H(c->hwnd), c->id, QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_SetDlgItemInt
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t value;
    uint64_t fSigned;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetDlgItemInt(HWND hwnd, INT id, UINT value, BOOL fSigned)
{
    struct qemu_SetDlgItemInt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDLGITEMINT);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.value = (uint64_t)value;
    call.fSigned = (uint64_t)fSigned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDlgItemInt(struct qemu_syscall *call)
{
    struct qemu_SetDlgItemInt *c = (struct qemu_SetDlgItemInt *)call;
    WINE_TRACE("\n");
    c->super.iret = SetDlgItemInt(QEMU_G2H(c->hwnd), c->id, c->value, c->fSigned);
}

#endif

struct qemu_GetDlgItemInt
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t translated;
    uint64_t fSigned;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetDlgItemInt(HWND hwnd, INT id, BOOL *translated, BOOL fSigned)
{
    struct qemu_GetDlgItemInt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDLGITEMINT);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.translated = (uint64_t)translated;
    call.fSigned = (uint64_t)fSigned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDlgItemInt(struct qemu_syscall *call)
{
    struct qemu_GetDlgItemInt *c = (struct qemu_GetDlgItemInt *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDlgItemInt(QEMU_G2H(c->hwnd), c->id, QEMU_G2H(c->translated), c->fSigned);
}

#endif

struct qemu_CheckDlgButton
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t check;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CheckDlgButton(HWND hwnd, INT id, UINT check)
{
    struct qemu_CheckDlgButton call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHECKDLGBUTTON);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.check = (uint64_t)check;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CheckDlgButton(struct qemu_syscall *call)
{
    struct qemu_CheckDlgButton *c = (struct qemu_CheckDlgButton *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CheckDlgButton(QEMU_G2H(c->hwnd), c->id, c->check);
}

#endif

struct qemu_IsDlgButtonChecked
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI IsDlgButtonChecked(HWND hwnd, int id)
{
    struct qemu_IsDlgButtonChecked call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISDLGBUTTONCHECKED);
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsDlgButtonChecked(struct qemu_syscall *call)
{
    struct qemu_IsDlgButtonChecked *c = (struct qemu_IsDlgButtonChecked *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsDlgButtonChecked(QEMU_G2H(c->hwnd), c->id);
}

#endif

struct qemu_CheckRadioButton
{
    struct qemu_syscall super;
    uint64_t hwndDlg;
    uint64_t firstID;
    uint64_t lastID;
    uint64_t checkID;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CheckRadioButton(HWND hwndDlg, int firstID, int lastID, int checkID)
{
    struct qemu_CheckRadioButton call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHECKRADIOBUTTON);
    call.hwndDlg = (uint64_t)hwndDlg;
    call.firstID = (uint64_t)firstID;
    call.lastID = (uint64_t)lastID;
    call.checkID = (uint64_t)checkID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CheckRadioButton(struct qemu_syscall *call)
{
    struct qemu_CheckRadioButton *c = (struct qemu_CheckRadioButton *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CheckRadioButton(QEMU_G2H(c->hwndDlg), c->firstID, c->lastID, c->checkID);
}

#endif

struct qemu_MapDialogRect
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI MapDialogRect(HWND hwnd, LPRECT rect)
{
    struct qemu_MapDialogRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAPDIALOGRECT);
    call.hwnd = (uint64_t)hwnd;
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MapDialogRect(struct qemu_syscall *call)
{
    struct qemu_MapDialogRect *c = (struct qemu_MapDialogRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MapDialogRect(QEMU_G2H(c->hwnd), QEMU_G2H(c->rect));
}

#endif

struct qemu_GetNextDlgGroupItem
{
    struct qemu_syscall super;
    uint64_t hwndDlg;
    uint64_t hwndCtrl;
    uint64_t fPrevious;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetNextDlgGroupItem(HWND hwndDlg, HWND hwndCtrl, BOOL fPrevious)
{
    struct qemu_GetNextDlgGroupItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNEXTDLGGROUPITEM);
    call.hwndDlg = (uint64_t)hwndDlg;
    call.hwndCtrl = (uint64_t)hwndCtrl;
    call.fPrevious = (uint64_t)fPrevious;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetNextDlgGroupItem(struct qemu_syscall *call)
{
    struct qemu_GetNextDlgGroupItem *c = (struct qemu_GetNextDlgGroupItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetNextDlgGroupItem(QEMU_G2H(c->hwndDlg), QEMU_G2H(c->hwndCtrl), c->fPrevious);
}

#endif

struct qemu_GetNextDlgTabItem
{
    struct qemu_syscall super;
    uint64_t hwndDlg;
    uint64_t hwndCtrl;
    uint64_t fPrevious;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetNextDlgTabItem(HWND hwndDlg, HWND hwndCtrl, BOOL fPrevious)
{
    struct qemu_GetNextDlgTabItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNEXTDLGTABITEM);
    call.hwndDlg = (uint64_t)hwndDlg;
    call.hwndCtrl = (uint64_t)hwndCtrl;
    call.fPrevious = (uint64_t)fPrevious;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetNextDlgTabItem(struct qemu_syscall *call)
{
    struct qemu_GetNextDlgTabItem *c = (struct qemu_GetNextDlgTabItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetNextDlgTabItem(QEMU_G2H(c->hwndDlg), QEMU_G2H(c->hwndCtrl), c->fPrevious);
}

#endif

struct qemu_DlgDirSelectExA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t str;
    uint64_t len;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DlgDirSelectExA(HWND hwnd, LPSTR str, INT len, INT id)
{
    struct qemu_DlgDirSelectExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLGDIRSELECTEXA);
    call.hwnd = (uint64_t)hwnd;
    call.str = (uint64_t)str;
    call.len = (uint64_t)len;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DlgDirSelectExA(struct qemu_syscall *call)
{
    struct qemu_DlgDirSelectExA *c = (struct qemu_DlgDirSelectExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DlgDirSelectExA(QEMU_G2H(c->hwnd), QEMU_G2H(c->str), c->len, c->id);
}

#endif

struct qemu_DlgDirSelectExW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t str;
    uint64_t len;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DlgDirSelectExW(HWND hwnd, LPWSTR str, INT len, INT id)
{
    struct qemu_DlgDirSelectExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLGDIRSELECTEXW);
    call.hwnd = (uint64_t)hwnd;
    call.str = (uint64_t)str;
    call.len = (uint64_t)len;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DlgDirSelectExW(struct qemu_syscall *call)
{
    struct qemu_DlgDirSelectExW *c = (struct qemu_DlgDirSelectExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DlgDirSelectExW(QEMU_G2H(c->hwnd), QEMU_G2H(c->str), c->len, c->id);
}

#endif

struct qemu_DlgDirSelectComboBoxExA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t str;
    uint64_t len;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DlgDirSelectComboBoxExA(HWND hwnd, LPSTR str, INT len, INT id)
{
    struct qemu_DlgDirSelectComboBoxExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLGDIRSELECTCOMBOBOXEXA);
    call.hwnd = (uint64_t)hwnd;
    call.str = (uint64_t)str;
    call.len = (uint64_t)len;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DlgDirSelectComboBoxExA(struct qemu_syscall *call)
{
    struct qemu_DlgDirSelectComboBoxExA *c = (struct qemu_DlgDirSelectComboBoxExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DlgDirSelectComboBoxExA(QEMU_G2H(c->hwnd), QEMU_G2H(c->str), c->len, c->id);
}

#endif

struct qemu_DlgDirSelectComboBoxExW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t str;
    uint64_t len;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DlgDirSelectComboBoxExW(HWND hwnd, LPWSTR str, INT len, INT id)
{
    struct qemu_DlgDirSelectComboBoxExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLGDIRSELECTCOMBOBOXEXW);
    call.hwnd = (uint64_t)hwnd;
    call.str = (uint64_t)str;
    call.len = (uint64_t)len;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DlgDirSelectComboBoxExW(struct qemu_syscall *call)
{
    struct qemu_DlgDirSelectComboBoxExW *c = (struct qemu_DlgDirSelectComboBoxExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DlgDirSelectComboBoxExW(QEMU_G2H(c->hwnd), QEMU_G2H(c->str), c->len, c->id);
}

#endif

struct qemu_DlgDirListA
{
    struct qemu_syscall super;
    uint64_t hDlg;
    uint64_t spec;
    uint64_t idLBox;
    uint64_t idStatic;
    uint64_t attrib;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI DlgDirListA(HWND hDlg, LPSTR spec, INT idLBox, INT idStatic, UINT attrib)
{
    struct qemu_DlgDirListA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLGDIRLISTA);
    call.hDlg = (uint64_t)hDlg;
    call.spec = (uint64_t)spec;
    call.idLBox = (uint64_t)idLBox;
    call.idStatic = (uint64_t)idStatic;
    call.attrib = (uint64_t)attrib;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DlgDirListA(struct qemu_syscall *call)
{
    struct qemu_DlgDirListA *c = (struct qemu_DlgDirListA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DlgDirListA(QEMU_G2H(c->hDlg), QEMU_G2H(c->spec), c->idLBox, c->idStatic, c->attrib);
}

#endif

struct qemu_DlgDirListW
{
    struct qemu_syscall super;
    uint64_t hDlg;
    uint64_t spec;
    uint64_t idLBox;
    uint64_t idStatic;
    uint64_t attrib;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI DlgDirListW(HWND hDlg, LPWSTR spec, INT idLBox, INT idStatic, UINT attrib)
{
    struct qemu_DlgDirListW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLGDIRLISTW);
    call.hDlg = (uint64_t)hDlg;
    call.spec = (uint64_t)spec;
    call.idLBox = (uint64_t)idLBox;
    call.idStatic = (uint64_t)idStatic;
    call.attrib = (uint64_t)attrib;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DlgDirListW(struct qemu_syscall *call)
{
    struct qemu_DlgDirListW *c = (struct qemu_DlgDirListW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DlgDirListW(QEMU_G2H(c->hDlg), QEMU_G2H(c->spec), c->idLBox, c->idStatic, c->attrib);
}

#endif

struct qemu_DlgDirListComboBoxA
{
    struct qemu_syscall super;
    uint64_t hDlg;
    uint64_t spec;
    uint64_t idCBox;
    uint64_t idStatic;
    uint64_t attrib;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI DlgDirListComboBoxA(HWND hDlg, LPSTR spec, INT idCBox, INT idStatic, UINT attrib)
{
    struct qemu_DlgDirListComboBoxA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLGDIRLISTCOMBOBOXA);
    call.hDlg = (uint64_t)hDlg;
    call.spec = (uint64_t)spec;
    call.idCBox = (uint64_t)idCBox;
    call.idStatic = (uint64_t)idStatic;
    call.attrib = (uint64_t)attrib;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DlgDirListComboBoxA(struct qemu_syscall *call)
{
    struct qemu_DlgDirListComboBoxA *c = (struct qemu_DlgDirListComboBoxA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DlgDirListComboBoxA(QEMU_G2H(c->hDlg), QEMU_G2H(c->spec), c->idCBox, c->idStatic, c->attrib);
}

#endif

struct qemu_DlgDirListComboBoxW
{
    struct qemu_syscall super;
    uint64_t hDlg;
    uint64_t spec;
    uint64_t idCBox;
    uint64_t idStatic;
    uint64_t attrib;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI DlgDirListComboBoxW(HWND hDlg, LPWSTR spec, INT idCBox, INT idStatic, UINT attrib)
{
    struct qemu_DlgDirListComboBoxW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLGDIRLISTCOMBOBOXW);
    call.hDlg = (uint64_t)hDlg;
    call.spec = (uint64_t)spec;
    call.idCBox = (uint64_t)idCBox;
    call.idStatic = (uint64_t)idStatic;
    call.attrib = (uint64_t)attrib;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DlgDirListComboBoxW(struct qemu_syscall *call)
{
    struct qemu_DlgDirListComboBoxW *c = (struct qemu_DlgDirListComboBoxW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DlgDirListComboBoxW(QEMU_G2H(c->hDlg), QEMU_G2H(c->spec), c->idCBox, c->idStatic, c->attrib);
}

#endif
