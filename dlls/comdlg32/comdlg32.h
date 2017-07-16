#ifndef COMDLG32_H
#define COMDLG32_H

#include <stdlib.h>

enum comdlg32_calls
{
    CALL_CHOOSEFONTA = 0,
    CALL_CHOOSEFONTW,
    CALL_FINDTEXTA,
    CALL_FINDTEXTW,
    CALL_GETFILETITLEA,
    CALL_GETFILETITLEW,
    CALL_GETOPENFILENAMEA,
    CALL_GETOPENFILENAMEW,
    CALL_GETSAVEFILENAMEA,
    CALL_GETSAVEFILENAMEW,
    CALL_PAGESETUPDLGA,
    CALL_PAGESETUPDLGW,
    CALL_PRINTDLGA,
    CALL_PRINTDLGEXA,
    CALL_PRINTDLGEXW,
    CALL_PRINTDLGW,
    CALL_REPLACETEXTA,
    CALL_REPLACETEXTW,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_ChooseFontA(struct qemu_syscall *call);
void qemu_ChooseFontW(struct qemu_syscall *call);
void qemu_FindTextA(struct qemu_syscall *call);
void qemu_FindTextW(struct qemu_syscall *call);
void qemu_GetFileTitleA(struct qemu_syscall *call);
void qemu_GetFileTitleW(struct qemu_syscall *call);
void qemu_GetOpenSaveFileName(struct qemu_syscall *call);
void qemu_PageSetupDlgA(struct qemu_syscall *call);
void qemu_PageSetupDlgW(struct qemu_syscall *call);
void qemu_PrintDlgA(struct qemu_syscall *call);
void qemu_PrintDlgExA(struct qemu_syscall *call);
void qemu_PrintDlgExW(struct qemu_syscall *call);
void qemu_PrintDlgW(struct qemu_syscall *call);
void qemu_ReplaceTextA(struct qemu_syscall *call);
void qemu_ReplaceTextW(struct qemu_syscall *call);

DWORD comdlg32_tls;

#endif

#endif