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
#include <wct.h>
#include <wmistr.h>
#include <evntrace.h>
#include <evntprov.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif


struct qemu_BackupEventLogA
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t lpBackupFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BackupEventLogA(HANDLE hEventLog, LPCSTR lpBackupFileName)
{
    struct qemu_BackupEventLogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BACKUPEVENTLOGA);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.lpBackupFileName = (ULONG_PTR)lpBackupFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BackupEventLogA(struct qemu_syscall *call)
{
    struct qemu_BackupEventLogA *c = (struct qemu_BackupEventLogA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BackupEventLogA(QEMU_G2H(c->hEventLog), QEMU_G2H(c->lpBackupFileName));
}

#endif

struct qemu_BackupEventLogW
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t lpBackupFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BackupEventLogW(HANDLE hEventLog, LPCWSTR lpBackupFileName)
{
    struct qemu_BackupEventLogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BACKUPEVENTLOGW);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.lpBackupFileName = (ULONG_PTR)lpBackupFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BackupEventLogW(struct qemu_syscall *call)
{
    struct qemu_BackupEventLogW *c = (struct qemu_BackupEventLogW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BackupEventLogW(QEMU_G2H(c->hEventLog), QEMU_G2H(c->lpBackupFileName));
}

#endif

struct qemu_ClearEventLogA
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t lpBackupFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ClearEventLogA(HANDLE hEventLog, LPCSTR lpBackupFileName)
{
    struct qemu_ClearEventLogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLEAREVENTLOGA);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.lpBackupFileName = (ULONG_PTR)lpBackupFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ClearEventLogA(struct qemu_syscall *call)
{
    struct qemu_ClearEventLogA *c = (struct qemu_ClearEventLogA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ClearEventLogA(QEMU_G2H(c->hEventLog), QEMU_G2H(c->lpBackupFileName));
}

#endif

struct qemu_ClearEventLogW
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t lpBackupFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ClearEventLogW(HANDLE hEventLog, LPCWSTR lpBackupFileName)
{
    struct qemu_ClearEventLogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLEAREVENTLOGW);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.lpBackupFileName = (ULONG_PTR)lpBackupFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ClearEventLogW(struct qemu_syscall *call)
{
    struct qemu_ClearEventLogW *c = (struct qemu_ClearEventLogW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ClearEventLogW(QEMU_G2H(c->hEventLog), QEMU_G2H(c->lpBackupFileName));
}

#endif

struct qemu_CloseEventLog
{
    struct qemu_syscall super;
    uint64_t hEventLog;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CloseEventLog(HANDLE hEventLog)
{
    struct qemu_CloseEventLog call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEEVENTLOG);
    call.hEventLog = (ULONG_PTR)hEventLog;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseEventLog(struct qemu_syscall *call)
{
    struct qemu_CloseEventLog *c = (struct qemu_CloseEventLog *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CloseEventLog(QEMU_G2H(c->hEventLog));
}

#endif

struct qemu_ControlTraceW
{
    struct qemu_syscall super;
    uint64_t hSession;
    uint64_t SessionName;
    uint64_t Properties;
    uint64_t control;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI ControlTraceW(TRACEHANDLE hSession, LPCWSTR SessionName, PEVENT_TRACE_PROPERTIES Properties, ULONG control)
{
    struct qemu_ControlTraceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTROLTRACEW);
    call.hSession = (ULONG_PTR)hSession;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;
    call.control = (ULONG_PTR)control;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ControlTraceW(struct qemu_syscall *call)
{
    struct qemu_ControlTraceW *c = (struct qemu_ControlTraceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ControlTraceW(c->hSession, QEMU_G2H(c->SessionName), QEMU_G2H(c->Properties), c->control);
}

#endif

struct qemu_ControlTraceA
{
    struct qemu_syscall super;
    uint64_t hSession;
    uint64_t SessionName;
    uint64_t Properties;
    uint64_t control;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI ControlTraceA(TRACEHANDLE hSession, LPCSTR SessionName, PEVENT_TRACE_PROPERTIES Properties, ULONG control)
{
    struct qemu_ControlTraceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTROLTRACEA);
    call.hSession = (ULONG_PTR)hSession;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;
    call.control = (ULONG_PTR)control;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ControlTraceA(struct qemu_syscall *call)
{
    struct qemu_ControlTraceA *c = (struct qemu_ControlTraceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ControlTraceA(c->hSession, QEMU_G2H(c->SessionName), QEMU_G2H(c->Properties), c->control);
}

#endif

struct qemu_FlushTraceA
{
    struct qemu_syscall super;
    uint64_t hSession;
    uint64_t SessionName;
    uint64_t Properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI FlushTraceA (TRACEHANDLE hSession, LPCSTR SessionName, PEVENT_TRACE_PROPERTIES Properties)
{
    struct qemu_FlushTraceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLUSHTRACEA);
    call.hSession = (ULONG_PTR)hSession;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlushTraceA(struct qemu_syscall *call)
{
    struct qemu_FlushTraceA *c = (struct qemu_FlushTraceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FlushTraceA(c->hSession, QEMU_G2H(c->SessionName), QEMU_G2H(c->Properties));
}

#endif

struct qemu_FlushTraceW
{
    struct qemu_syscall super;
    uint64_t hSession;
    uint64_t SessionName;
    uint64_t Properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI FlushTraceW (TRACEHANDLE hSession, LPCWSTR SessionName, PEVENT_TRACE_PROPERTIES Properties)
{
    struct qemu_FlushTraceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLUSHTRACEW);
    call.hSession = (ULONG_PTR)hSession;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlushTraceW(struct qemu_syscall *call)
{
    struct qemu_FlushTraceW *c = (struct qemu_FlushTraceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FlushTraceW(c->hSession, QEMU_G2H(c->SessionName), QEMU_G2H(c->Properties));
}

#endif

struct qemu_DeregisterEventSource
{
    struct qemu_syscall super;
    uint64_t hEventLog;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeregisterEventSource(HANDLE hEventLog)
{
    struct qemu_DeregisterEventSource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEREGISTEREVENTSOURCE);
    call.hEventLog = (ULONG_PTR)hEventLog;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeregisterEventSource(struct qemu_syscall *call)
{
    struct qemu_DeregisterEventSource *c = (struct qemu_DeregisterEventSource *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeregisterEventSource(QEMU_G2H(c->hEventLog));
}

#endif

struct qemu_EnableTraceEx
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t source;
    uint64_t hSession;
    uint64_t enable;
    uint64_t level;
    uint64_t anykeyword;
    uint64_t allkeyword;
    uint64_t enableprop;
    uint64_t filterdesc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EnableTraceEx(LPCGUID provider, LPCGUID source, TRACEHANDLE hSession, ULONG enable, UCHAR level, ULONGLONG anykeyword, ULONGLONG allkeyword, ULONG enableprop, PEVENT_FILTER_DESCRIPTOR filterdesc)
{
    struct qemu_EnableTraceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLETRACEEX);
    call.provider = (ULONG_PTR)provider;
    call.source = (ULONG_PTR)source;
    call.hSession = (ULONG_PTR)hSession;
    call.enable = (ULONG_PTR)enable;
    call.level = (ULONG_PTR)level;
    call.anykeyword = (ULONG_PTR)anykeyword;
    call.allkeyword = (ULONG_PTR)allkeyword;
    call.enableprop = (ULONG_PTR)enableprop;
    call.filterdesc = (ULONG_PTR)filterdesc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EnableTraceEx to Wine headers? */
extern ULONG WINAPI EnableTraceEx(LPCGUID provider, LPCGUID source, TRACEHANDLE hSession, ULONG enable, UCHAR level, ULONGLONG anykeyword, ULONGLONG allkeyword, ULONG enableprop, PEVENT_FILTER_DESCRIPTOR filterdesc);
void qemu_EnableTraceEx(struct qemu_syscall *call)
{
    struct qemu_EnableTraceEx *c = (struct qemu_EnableTraceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnableTraceEx(QEMU_G2H(c->provider), QEMU_G2H(c->source), c->hSession, c->enable, c->level, c->anykeyword, c->allkeyword, c->enableprop, QEMU_G2H(c->filterdesc));
}

#endif

struct qemu_EnableTraceEx2
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t provider;
    uint64_t control;
    uint64_t level;
    uint64_t match_any;
    uint64_t match_all;
    uint64_t timeout;
    uint64_t params;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EnableTraceEx2(TRACEHANDLE handle, LPCGUID provider, ULONG control, UCHAR level, ULONGLONG match_any, ULONGLONG match_all, ULONG timeout, PENABLE_TRACE_PARAMETERS params)
{
    struct qemu_EnableTraceEx2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLETRACEEX2);
    call.handle = (ULONG_PTR)handle;
    call.provider = (ULONG_PTR)provider;
    call.control = (ULONG_PTR)control;
    call.level = (ULONG_PTR)level;
    call.match_any = (ULONG_PTR)match_any;
    call.match_all = (ULONG_PTR)match_all;
    call.timeout = (ULONG_PTR)timeout;
    call.params = (ULONG_PTR)params;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnableTraceEx2(struct qemu_syscall *call)
{
    struct qemu_EnableTraceEx2 *c = (struct qemu_EnableTraceEx2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnableTraceEx2(c->handle, QEMU_G2H(c->provider), c->control, c->level, c->match_any, c->match_all, c->timeout, QEMU_G2H(c->params));
}

#endif

struct qemu_EnableTrace
{
    struct qemu_syscall super;
    uint64_t enable;
    uint64_t flag;
    uint64_t level;
    uint64_t guid;
    uint64_t hSession;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EnableTrace(ULONG enable, ULONG flag, ULONG level, LPCGUID guid, TRACEHANDLE hSession)
{
    struct qemu_EnableTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLETRACE);
    call.enable = (ULONG_PTR)enable;
    call.flag = (ULONG_PTR)flag;
    call.level = (ULONG_PTR)level;
    call.guid = (ULONG_PTR)guid;
    call.hSession = (ULONG_PTR)hSession;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnableTrace(struct qemu_syscall *call)
{
    struct qemu_EnableTrace *c = (struct qemu_EnableTrace *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnableTrace(c->enable, c->flag, c->level, QEMU_G2H(c->guid), c->hSession);
}

#endif

struct qemu_GetEventLogInformation
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t dwInfoLevel;
    uint64_t lpBuffer;
    uint64_t cbBufSize;
    uint64_t pcbBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetEventLogInformation(HANDLE hEventLog, DWORD dwInfoLevel, LPVOID lpBuffer, DWORD cbBufSize, LPDWORD pcbBytesNeeded)
{
    struct qemu_GetEventLogInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEVENTLOGINFORMATION);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.dwInfoLevel = (ULONG_PTR)dwInfoLevel;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.cbBufSize = (ULONG_PTR)cbBufSize;
    call.pcbBytesNeeded = (ULONG_PTR)pcbBytesNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEventLogInformation(struct qemu_syscall *call)
{
    struct qemu_GetEventLogInformation *c = (struct qemu_GetEventLogInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetEventLogInformation(QEMU_G2H(c->hEventLog), c->dwInfoLevel, QEMU_G2H(c->lpBuffer), c->cbBufSize, QEMU_G2H(c->pcbBytesNeeded));
}

#endif

struct qemu_GetNumberOfEventLogRecords
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t NumberOfRecords;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNumberOfEventLogRecords(HANDLE hEventLog, PDWORD NumberOfRecords)
{
    struct qemu_GetNumberOfEventLogRecords call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMBEROFEVENTLOGRECORDS);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.NumberOfRecords = (ULONG_PTR)NumberOfRecords;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNumberOfEventLogRecords(struct qemu_syscall *call)
{
    struct qemu_GetNumberOfEventLogRecords *c = (struct qemu_GetNumberOfEventLogRecords *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumberOfEventLogRecords(QEMU_G2H(c->hEventLog), QEMU_G2H(c->NumberOfRecords));
}

#endif

struct qemu_GetOldestEventLogRecord
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t OldestRecord;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetOldestEventLogRecord(HANDLE hEventLog, PDWORD OldestRecord)
{
    struct qemu_GetOldestEventLogRecord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOLDESTEVENTLOGRECORD);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.OldestRecord = (ULONG_PTR)OldestRecord;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetOldestEventLogRecord(struct qemu_syscall *call)
{
    struct qemu_GetOldestEventLogRecord *c = (struct qemu_GetOldestEventLogRecord *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetOldestEventLogRecord(QEMU_G2H(c->hEventLog), QEMU_G2H(c->OldestRecord));
}

#endif

struct qemu_GetTraceEnableFlags
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI GetTraceEnableFlags(TRACEHANDLE handle)
{
    struct qemu_GetTraceEnableFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRACEENABLEFLAGS);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTraceEnableFlags(struct qemu_syscall *call)
{
    struct qemu_GetTraceEnableFlags *c = (struct qemu_GetTraceEnableFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTraceEnableFlags(c->handle);
}

#endif

struct qemu_GetTraceEnableLevel
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UCHAR WINAPI GetTraceEnableLevel(TRACEHANDLE handle)
{
    struct qemu_GetTraceEnableLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRACEENABLELEVEL);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTraceEnableLevel(struct qemu_syscall *call)
{
    struct qemu_GetTraceEnableLevel *c = (struct qemu_GetTraceEnableLevel *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTraceEnableLevel(c->handle);
}

#endif

struct qemu_GetTraceLoggerHandle
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRACEHANDLE WINAPI GetTraceLoggerHandle(PVOID buf)
{
    struct qemu_GetTraceLoggerHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRACELOGGERHANDLE);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTraceLoggerHandle(struct qemu_syscall *call)
{
    struct qemu_GetTraceLoggerHandle *c = (struct qemu_GetTraceLoggerHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTraceLoggerHandle(QEMU_G2H(c->buf));
}

#endif

struct qemu_NotifyChangeEventLog
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t hEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI NotifyChangeEventLog(HANDLE hEventLog, HANDLE hEvent)
{
    struct qemu_NotifyChangeEventLog call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NOTIFYCHANGEEVENTLOG);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.hEvent = (ULONG_PTR)hEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NotifyChangeEventLog(struct qemu_syscall *call)
{
    struct qemu_NotifyChangeEventLog *c = (struct qemu_NotifyChangeEventLog *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NotifyChangeEventLog(QEMU_G2H(c->hEventLog), QEMU_G2H(c->hEvent));
}

#endif

struct qemu_OpenBackupEventLogA
{
    struct qemu_syscall super;
    uint64_t lpUNCServerName;
    uint64_t lpFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenBackupEventLogA(LPCSTR lpUNCServerName, LPCSTR lpFileName)
{
    struct qemu_OpenBackupEventLogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENBACKUPEVENTLOGA);
    call.lpUNCServerName = (ULONG_PTR)lpUNCServerName;
    call.lpFileName = (ULONG_PTR)lpFileName;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenBackupEventLogA(struct qemu_syscall *call)
{
    struct qemu_OpenBackupEventLogA *c = (struct qemu_OpenBackupEventLogA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenBackupEventLogA(QEMU_G2H(c->lpUNCServerName), QEMU_G2H(c->lpFileName));
}

#endif

struct qemu_OpenBackupEventLogW
{
    struct qemu_syscall super;
    uint64_t lpUNCServerName;
    uint64_t lpFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenBackupEventLogW(LPCWSTR lpUNCServerName, LPCWSTR lpFileName)
{
    struct qemu_OpenBackupEventLogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENBACKUPEVENTLOGW);
    call.lpUNCServerName = (ULONG_PTR)lpUNCServerName;
    call.lpFileName = (ULONG_PTR)lpFileName;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenBackupEventLogW(struct qemu_syscall *call)
{
    struct qemu_OpenBackupEventLogW *c = (struct qemu_OpenBackupEventLogW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenBackupEventLogW(QEMU_G2H(c->lpUNCServerName), QEMU_G2H(c->lpFileName));
}

#endif

struct qemu_OpenEventLogA
{
    struct qemu_syscall super;
    uint64_t uncname;
    uint64_t source;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenEventLogA(LPCSTR uncname, LPCSTR source)
{
    struct qemu_OpenEventLogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENEVENTLOGA);
    call.uncname = (ULONG_PTR)uncname;
    call.source = (ULONG_PTR)source;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenEventLogA(struct qemu_syscall *call)
{
    struct qemu_OpenEventLogA *c = (struct qemu_OpenEventLogA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenEventLogA(QEMU_G2H(c->uncname), QEMU_G2H(c->source));
}

#endif

struct qemu_OpenEventLogW
{
    struct qemu_syscall super;
    uint64_t uncname;
    uint64_t source;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenEventLogW(LPCWSTR uncname, LPCWSTR source)
{
    struct qemu_OpenEventLogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENEVENTLOGW);
    call.uncname = (ULONG_PTR)uncname;
    call.source = (ULONG_PTR)source;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenEventLogW(struct qemu_syscall *call)
{
    struct qemu_OpenEventLogW *c = (struct qemu_OpenEventLogW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenEventLogW(QEMU_G2H(c->uncname), QEMU_G2H(c->source));
}

#endif

struct qemu_QueryAllTracesW
{
    struct qemu_syscall super;
    uint64_t parray;
    uint64_t arraycount;
    uint64_t psessioncount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI QueryAllTracesW(PEVENT_TRACE_PROPERTIES * parray, ULONG arraycount, PULONG psessioncount)
{
    struct qemu_QueryAllTracesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYALLTRACESW);
    call.parray = (ULONG_PTR)parray;
    call.arraycount = (ULONG_PTR)arraycount;
    call.psessioncount = (ULONG_PTR)psessioncount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryAllTracesW(struct qemu_syscall *call)
{
    struct qemu_QueryAllTracesW *c = (struct qemu_QueryAllTracesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryAllTracesW(QEMU_G2H(c->parray), c->arraycount, QEMU_G2H(c->psessioncount));
}

#endif

struct qemu_QueryAllTracesA
{
    struct qemu_syscall super;
    uint64_t parray;
    uint64_t arraycount;
    uint64_t psessioncount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI QueryAllTracesA(PEVENT_TRACE_PROPERTIES * parray, ULONG arraycount, PULONG psessioncount)
{
    struct qemu_QueryAllTracesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYALLTRACESA);
    call.parray = (ULONG_PTR)parray;
    call.arraycount = (ULONG_PTR)arraycount;
    call.psessioncount = (ULONG_PTR)psessioncount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryAllTracesA(struct qemu_syscall *call)
{
    struct qemu_QueryAllTracesA *c = (struct qemu_QueryAllTracesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryAllTracesA(QEMU_G2H(c->parray), c->arraycount, QEMU_G2H(c->psessioncount));
}

#endif

struct qemu_ReadEventLogA
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t dwReadFlags;
    uint64_t dwRecordOffset;
    uint64_t lpBuffer;
    uint64_t nNumberOfBytesToRead;
    uint64_t pnBytesRead;
    uint64_t pnMinNumberOfBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadEventLogA(HANDLE hEventLog, DWORD dwReadFlags, DWORD dwRecordOffset, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, DWORD *pnBytesRead, DWORD *pnMinNumberOfBytesNeeded)
{
    struct qemu_ReadEventLogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READEVENTLOGA);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.dwReadFlags = (ULONG_PTR)dwReadFlags;
    call.dwRecordOffset = (ULONG_PTR)dwRecordOffset;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.nNumberOfBytesToRead = (ULONG_PTR)nNumberOfBytesToRead;
    call.pnBytesRead = (ULONG_PTR)pnBytesRead;
    call.pnMinNumberOfBytesNeeded = (ULONG_PTR)pnMinNumberOfBytesNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadEventLogA(struct qemu_syscall *call)
{
    struct qemu_ReadEventLogA *c = (struct qemu_ReadEventLogA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadEventLogA(QEMU_G2H(c->hEventLog), c->dwReadFlags, c->dwRecordOffset, QEMU_G2H(c->lpBuffer), c->nNumberOfBytesToRead, QEMU_G2H(c->pnBytesRead), QEMU_G2H(c->pnMinNumberOfBytesNeeded));
}

#endif

struct qemu_ReadEventLogW
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t dwReadFlags;
    uint64_t dwRecordOffset;
    uint64_t lpBuffer;
    uint64_t nNumberOfBytesToRead;
    uint64_t pnBytesRead;
    uint64_t pnMinNumberOfBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadEventLogW(HANDLE hEventLog, DWORD dwReadFlags, DWORD dwRecordOffset, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, DWORD *pnBytesRead, DWORD *pnMinNumberOfBytesNeeded)
{
    struct qemu_ReadEventLogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READEVENTLOGW);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.dwReadFlags = (ULONG_PTR)dwReadFlags;
    call.dwRecordOffset = (ULONG_PTR)dwRecordOffset;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.nNumberOfBytesToRead = (ULONG_PTR)nNumberOfBytesToRead;
    call.pnBytesRead = (ULONG_PTR)pnBytesRead;
    call.pnMinNumberOfBytesNeeded = (ULONG_PTR)pnMinNumberOfBytesNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadEventLogW(struct qemu_syscall *call)
{
    struct qemu_ReadEventLogW *c = (struct qemu_ReadEventLogW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadEventLogW(QEMU_G2H(c->hEventLog), c->dwReadFlags, c->dwRecordOffset, QEMU_G2H(c->lpBuffer), c->nNumberOfBytesToRead, QEMU_G2H(c->pnBytesRead), QEMU_G2H(c->pnMinNumberOfBytesNeeded));
}

#endif

struct qemu_RegisterEventSourceA
{
    struct qemu_syscall super;
    uint64_t lpUNCServerName;
    uint64_t lpSourceName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI RegisterEventSourceA(LPCSTR lpUNCServerName, LPCSTR lpSourceName)
{
    struct qemu_RegisterEventSourceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTEREVENTSOURCEA);
    call.lpUNCServerName = (ULONG_PTR)lpUNCServerName;
    call.lpSourceName = (ULONG_PTR)lpSourceName;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RegisterEventSourceA(struct qemu_syscall *call)
{
    struct qemu_RegisterEventSourceA *c = (struct qemu_RegisterEventSourceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RegisterEventSourceA(QEMU_G2H(c->lpUNCServerName), QEMU_G2H(c->lpSourceName));
}

#endif

struct qemu_RegisterEventSourceW
{
    struct qemu_syscall super;
    uint64_t lpUNCServerName;
    uint64_t lpSourceName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI RegisterEventSourceW(LPCWSTR lpUNCServerName, LPCWSTR lpSourceName)
{
    struct qemu_RegisterEventSourceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTEREVENTSOURCEW);
    call.lpUNCServerName = (ULONG_PTR)lpUNCServerName;
    call.lpSourceName = (ULONG_PTR)lpSourceName;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RegisterEventSourceW(struct qemu_syscall *call)
{
    struct qemu_RegisterEventSourceW *c = (struct qemu_RegisterEventSourceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RegisterEventSourceW(QEMU_G2H(c->lpUNCServerName), QEMU_G2H(c->lpSourceName));
}

#endif

struct qemu_ReportEventA
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t wType;
    uint64_t wCategory;
    uint64_t dwEventID;
    uint64_t lpUserSid;
    uint64_t wNumStrings;
    uint64_t dwDataSize;
    uint64_t lpStrings;
    uint64_t lpRawData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReportEventA (HANDLE hEventLog, WORD wType, WORD wCategory, DWORD dwEventID, PSID lpUserSid, WORD wNumStrings, DWORD dwDataSize, LPCSTR *lpStrings, LPVOID lpRawData)
{
    struct qemu_ReportEventA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REPORTEVENTA);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.wType = (ULONG_PTR)wType;
    call.wCategory = (ULONG_PTR)wCategory;
    call.dwEventID = (ULONG_PTR)dwEventID;
    call.lpUserSid = (ULONG_PTR)lpUserSid;
    call.wNumStrings = (ULONG_PTR)wNumStrings;
    call.dwDataSize = (ULONG_PTR)dwDataSize;
    call.lpStrings = (ULONG_PTR)lpStrings;
    call.lpRawData = (ULONG_PTR)lpRawData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReportEventA(struct qemu_syscall *call)
{
    struct qemu_ReportEventA *c = (struct qemu_ReportEventA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReportEventA(QEMU_G2H(c->hEventLog), c->wType, c->wCategory, c->dwEventID, QEMU_G2H(c->lpUserSid), c->wNumStrings, c->dwDataSize, QEMU_G2H(c->lpStrings), QEMU_G2H(c->lpRawData));
}

#endif

struct qemu_ReportEventW
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t wType;
    uint64_t wCategory;
    uint64_t dwEventID;
    uint64_t lpUserSid;
    uint64_t wNumStrings;
    uint64_t dwDataSize;
    uint64_t lpStrings;
    uint64_t lpRawData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReportEventW(HANDLE hEventLog, WORD wType, WORD wCategory, DWORD dwEventID, PSID lpUserSid, WORD wNumStrings, DWORD dwDataSize, LPCWSTR *lpStrings, LPVOID lpRawData)
{
    struct qemu_ReportEventW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REPORTEVENTW);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.wType = (ULONG_PTR)wType;
    call.wCategory = (ULONG_PTR)wCategory;
    call.dwEventID = (ULONG_PTR)dwEventID;
    call.lpUserSid = (ULONG_PTR)lpUserSid;
    call.wNumStrings = (ULONG_PTR)wNumStrings;
    call.dwDataSize = (ULONG_PTR)dwDataSize;
    call.lpStrings = (ULONG_PTR)lpStrings;
    call.lpRawData = (ULONG_PTR)lpRawData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReportEventW(struct qemu_syscall *call)
{
    struct qemu_ReportEventW *c = (struct qemu_ReportEventW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReportEventW(QEMU_G2H(c->hEventLog), c->wType, c->wCategory, c->dwEventID, QEMU_G2H(c->lpUserSid), c->wNumStrings, c->dwDataSize, QEMU_G2H(c->lpStrings), QEMU_G2H(c->lpRawData));
}

#endif

struct qemu_StartTraceW
{
    struct qemu_syscall super;
    uint64_t pSessionHandle;
    uint64_t SessionName;
    uint64_t Properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI StartTraceW(PTRACEHANDLE pSessionHandle, LPCWSTR SessionName, PEVENT_TRACE_PROPERTIES Properties)
{
    struct qemu_StartTraceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTTRACEW);
    call.pSessionHandle = (ULONG_PTR)pSessionHandle;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartTraceW(struct qemu_syscall *call)
{
    struct qemu_StartTraceW *c = (struct qemu_StartTraceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StartTraceW(QEMU_G2H(c->pSessionHandle), QEMU_G2H(c->SessionName), QEMU_G2H(c->Properties));
}

#endif

struct qemu_StartTraceA
{
    struct qemu_syscall super;
    uint64_t pSessionHandle;
    uint64_t SessionName;
    uint64_t Properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI StartTraceA(PTRACEHANDLE pSessionHandle, LPCSTR SessionName, PEVENT_TRACE_PROPERTIES Properties)
{
    struct qemu_StartTraceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTTRACEA);
    call.pSessionHandle = (ULONG_PTR)pSessionHandle;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartTraceA(struct qemu_syscall *call)
{
    struct qemu_StartTraceA *c = (struct qemu_StartTraceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StartTraceA(QEMU_G2H(c->pSessionHandle), QEMU_G2H(c->SessionName), QEMU_G2H(c->Properties));
}

#endif

struct qemu_StopTraceW
{
    struct qemu_syscall super;
    uint64_t session;
    uint64_t session_name;
    uint64_t properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI StopTraceW(TRACEHANDLE session, LPCWSTR session_name, PEVENT_TRACE_PROPERTIES properties)
{
    struct qemu_StopTraceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STOPTRACEW);
    call.session = (ULONG_PTR)session;
    call.session_name = (ULONG_PTR)session_name;
    call.properties = (ULONG_PTR)properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StopTraceW to Wine headers? */
extern ULONG WINAPI StopTraceW(TRACEHANDLE session, LPCWSTR session_name, PEVENT_TRACE_PROPERTIES properties);
void qemu_StopTraceW(struct qemu_syscall *call)
{
    struct qemu_StopTraceW *c = (struct qemu_StopTraceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StopTraceW(c->session, QEMU_G2H(c->session_name), QEMU_G2H(c->properties));
}

#endif

struct qemu_StopTraceA
{
    struct qemu_syscall super;
    uint64_t session;
    uint64_t session_name;
    uint64_t properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI StopTraceA(TRACEHANDLE session, LPCSTR session_name, PEVENT_TRACE_PROPERTIES properties)
{
    struct qemu_StopTraceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STOPTRACEA);
    call.session = (ULONG_PTR)session;
    call.session_name = (ULONG_PTR)session_name;
    call.properties = (ULONG_PTR)properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StopTraceA to Wine headers? */
extern ULONG WINAPI StopTraceA(TRACEHANDLE session, LPCSTR session_name, PEVENT_TRACE_PROPERTIES properties);
void qemu_StopTraceA(struct qemu_syscall *call)
{
    struct qemu_StopTraceA *c = (struct qemu_StopTraceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StopTraceA(c->session, QEMU_G2H(c->session_name), QEMU_G2H(c->properties));
}

#endif

struct qemu_TraceEvent
{
    struct qemu_syscall super;
    uint64_t SessionHandle;
    uint64_t EventTrace;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI TraceEvent(TRACEHANDLE SessionHandle, PEVENT_TRACE_HEADER EventTrace)
{
    struct qemu_TraceEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRACEEVENT);
    call.SessionHandle = (ULONG_PTR)SessionHandle;
    call.EventTrace = (ULONG_PTR)EventTrace;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TraceEvent(struct qemu_syscall *call)
{
    struct qemu_TraceEvent *c = (struct qemu_TraceEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TraceEvent(c->SessionHandle, QEMU_G2H(c->EventTrace));
}

#endif

struct qemu_EventProviderEnabled
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t level;
    uint64_t keyword;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI EventProviderEnabled(REGHANDLE handle, UCHAR level, ULONGLONG keyword)
{
    struct qemu_EventProviderEnabled call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EVENTPROVIDERENABLED);
    call.handle = (ULONG_PTR)handle;
    call.level = (ULONG_PTR)level;
    call.keyword = (ULONG_PTR)keyword;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EventProviderEnabled(struct qemu_syscall *call)
{
    struct qemu_EventProviderEnabled *c = (struct qemu_EventProviderEnabled *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EventProviderEnabled(c->handle, c->level, c->keyword);
}

#endif

struct qemu_EventActivityIdControl
{
    struct qemu_syscall super;
    uint64_t code;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EventActivityIdControl(ULONG code, GUID *guid)
{
    struct qemu_EventActivityIdControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EVENTACTIVITYIDCONTROL);
    call.code = (ULONG_PTR)code;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EventActivityIdControl to Wine headers? */
extern ULONG WINAPI EventActivityIdControl(ULONG code, GUID *guid);
void qemu_EventActivityIdControl(struct qemu_syscall *call)
{
    struct qemu_EventActivityIdControl *c = (struct qemu_EventActivityIdControl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EventActivityIdControl(c->code, QEMU_G2H(c->guid));
}

#endif

struct qemu_EventWriteTransfer
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t descriptor;
    uint64_t activity;
    uint64_t related;
    uint64_t count;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EventWriteTransfer(REGHANDLE handle, PCEVENT_DESCRIPTOR descriptor, LPCGUID activity, LPCGUID related, ULONG count, PEVENT_DATA_DESCRIPTOR data)
{
    struct qemu_EventWriteTransfer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EVENTWRITETRANSFER);
    call.handle = (ULONG_PTR)handle;
    call.descriptor = (ULONG_PTR)descriptor;
    call.activity = (ULONG_PTR)activity;
    call.related = (ULONG_PTR)related;
    call.count = (ULONG_PTR)count;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EventWriteTransfer(struct qemu_syscall *call)
{
    struct qemu_EventWriteTransfer *c = (struct qemu_EventWriteTransfer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EventWriteTransfer(c->handle, QEMU_G2H(c->descriptor), QEMU_G2H(c->activity), QEMU_G2H(c->related), c->count, QEMU_G2H(c->data));
}

#endif

struct qemu_QueryTraceW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t sessionname;
    uint64_t properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI QueryTraceW(TRACEHANDLE handle, LPCWSTR sessionname, PEVENT_TRACE_PROPERTIES properties)
{
    struct qemu_QueryTraceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYTRACEW);
    call.handle = (ULONG_PTR)handle;
    call.sessionname = (ULONG_PTR)sessionname;
    call.properties = (ULONG_PTR)properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add QueryTraceW to Wine headers? */
extern ULONG WINAPI QueryTraceW(TRACEHANDLE handle, LPCWSTR sessionname, PEVENT_TRACE_PROPERTIES properties);
void qemu_QueryTraceW(struct qemu_syscall *call)
{
    struct qemu_QueryTraceW *c = (struct qemu_QueryTraceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryTraceW(c->handle, QEMU_G2H(c->sessionname), QEMU_G2H(c->properties));
}

#endif

struct qemu_OpenTraceA
{
    struct qemu_syscall super;
    uint64_t logfile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRACEHANDLE WINAPI OpenTraceA(PEVENT_TRACE_LOGFILEA logfile)
{
    struct qemu_OpenTraceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENTRACEA);
    call.logfile = (ULONG_PTR)logfile;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add OpenTraceA to Wine headers? */
extern TRACEHANDLE WINAPI OpenTraceA(PEVENT_TRACE_LOGFILEA logfile);
void qemu_OpenTraceA(struct qemu_syscall *call)
{
    struct qemu_OpenTraceA *c = (struct qemu_OpenTraceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OpenTraceA(QEMU_G2H(c->logfile));
}

#endif

struct qemu_OpenTraceW
{
    struct qemu_syscall super;
    uint64_t logfile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRACEHANDLE WINAPI OpenTraceW(PEVENT_TRACE_LOGFILEW logfile)
{
    struct qemu_OpenTraceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENTRACEW);
    call.logfile = (ULONG_PTR)logfile;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add OpenTraceW to Wine headers? */
extern TRACEHANDLE WINAPI OpenTraceW(PEVENT_TRACE_LOGFILEW logfile);
void qemu_OpenTraceW(struct qemu_syscall *call)
{
    struct qemu_OpenTraceW *c = (struct qemu_OpenTraceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OpenTraceW(QEMU_G2H(c->logfile));
}

#endif

struct qemu_ProcessTrace
{
    struct qemu_syscall super;
    uint64_t HandleArray;
    uint64_t HandleCount;
    uint64_t StartTime;
    uint64_t EndTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI ProcessTrace(PTRACEHANDLE HandleArray, ULONG HandleCount, LPFILETIME StartTime, LPFILETIME EndTime)
{
    struct qemu_ProcessTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROCESSTRACE);
    call.HandleArray = (ULONG_PTR)HandleArray;
    call.HandleCount = (ULONG_PTR)HandleCount;
    call.StartTime = (ULONG_PTR)StartTime;
    call.EndTime = (ULONG_PTR)EndTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ProcessTrace to Wine headers? */
extern ULONG WINAPI ProcessTrace(PTRACEHANDLE HandleArray, ULONG HandleCount, LPFILETIME StartTime, LPFILETIME EndTime);
void qemu_ProcessTrace(struct qemu_syscall *call)
{
    struct qemu_ProcessTrace *c = (struct qemu_ProcessTrace *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ProcessTrace(QEMU_G2H(c->HandleArray), c->HandleCount, QEMU_G2H(c->StartTime), QEMU_G2H(c->EndTime));
}

#endif

struct qemu_TraceMessageVa
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t flags;
    uint64_t guid;
    uint64_t number;
    uint64_t args;
};

#ifdef QEMU_DLL_GUEST

ULONG WINAPI advapi32_TraceMessageVa(TRACEHANDLE handle, ULONG flags, LPCGUID guid, USHORT number, va_list args)
{
    struct qemu_TraceMessageVa call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRACEMESSAGEVA);
    call.handle = (ULONG_PTR)handle;
    call.flags = (ULONG_PTR)flags;
    call.guid = (ULONG_PTR)guid;
    call.number = (ULONG_PTR)number;

    qemu_syscall(&call.super);

    return call.super.iret;
}

ULONG CDECL TraceMessage(TRACEHANDLE handle, ULONG flags, LPCGUID guid, USHORT number, ...)
{
    va_list valist;
    ULONG ret;

    va_start( valist, number );
    ret = advapi32_TraceMessageVa( handle, flags, guid, number, valist );
    va_end( valist );
    return ret;
}

#else

void qemu_TraceMessageVa(struct qemu_syscall *call)
{
    struct qemu_TraceMessageVa *c = (struct qemu_TraceMessageVa *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = 0;
}

#endif

struct qemu_CloseTrace
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI CloseTrace(TRACEHANDLE handle)
{
    struct qemu_CloseTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSETRACE);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseTrace(struct qemu_syscall *call)
{
    struct qemu_CloseTrace *c = (struct qemu_CloseTrace *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CloseTrace(c->handle);
}

#endif

struct qemu_EnumerateTraceGuids
{
    struct qemu_syscall super;
    uint64_t propertiesarray;
    uint64_t arraycount;
    uint64_t guidcount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EnumerateTraceGuids(PTRACE_GUID_PROPERTIES *propertiesarray, ULONG arraycount, PULONG guidcount)
{
    struct qemu_EnumerateTraceGuids call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMERATETRACEGUIDS);
    call.propertiesarray = (ULONG_PTR)propertiesarray;
    call.arraycount = (ULONG_PTR)arraycount;
    call.guidcount = (ULONG_PTR)guidcount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EnumerateTraceGuids to Wine headers? */
extern ULONG WINAPI EnumerateTraceGuids(PTRACE_GUID_PROPERTIES *propertiesarray, ULONG arraycount, PULONG guidcount);
void qemu_EnumerateTraceGuids(struct qemu_syscall *call)
{
    struct qemu_EnumerateTraceGuids *c = (struct qemu_EnumerateTraceGuids *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumerateTraceGuids(QEMU_G2H(c->propertiesarray), c->arraycount, QEMU_G2H(c->guidcount));
}

#endif

