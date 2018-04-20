#include "EmuUniWnd.h"

void EmuUniWnd::DoWndMsg(int nCode, UniWndMsg* pUniWndMsg)
{
	switch (nCode)
	{
	case 0:
	{
		UniWnd uniWnd;
		uniWnd.WndMsg(nCode, pUniWndMsg);
	}
	break;
	}
}

void EmuUniWnd::DoWndEnsure(int nCode, UniWndMsg* pUniWndMsg)
{
	switch (nCode)
	{
	case UNI_CODE_ENSURE_DEL_CHEAT:
	case UNI_CODE_ENSURE_TUTRIAL:
	case UNI_CODE_ENSURE_EXIT:
	case UNI_CODE_ENSURE_EXIT_ELITE:
	case UNI_CODE_ENSURE_EXIT_RANKING:
	{
		UniWnd uniWnd;
		uniWnd.WndEnsure(nCode, pUniWndMsg);
	}
	break;
	case UNI_CODE_ENSURE_WATCH_NORMAL:
	case UNI_CODE_ENSURE_JOIN_NORMAL:
	{
		NormalGrappleWnd uniWnd;
		uniWnd.WndEnsure(nCode, pUniWndMsg);
	}
	break;
	case UNI_CODE_ENSURE_WATCH_ELITE:
	case UNI_CODE_ENSURE_JOIN_GRAPPLE_ELITE:
	{
		EliteGrappleWnd uniWnd;
		uniWnd.WndEnsure(nCode, pUniWndMsg);
	}
	break;
	}
}