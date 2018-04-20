#include "EmuUniWnd.h"
#include "WndEnsure.h"
#include "MsgDefine.h"
#include "WndEnsure2.h"

void UniWnd::WndMsg(int nCode, UniWndMsg* pUniWndMsg)
{
	switch (nCode)
	{
	case 0:
	{

	}
	break;
	}
}

void UniWnd::WndEnsure(int nCode, UniWndMsg* pUniWndMsg)
{
	switch (nCode)
	{
	case UNI_CODE_ENSURE_DEL_CHEAT:
	{
		UniWndMsg* pMsg = pUniWndMsg;
		CWndEnsure2* pWnd;
		pWnd = new CWndEnsure2("确认删除此项");
		HWND hWnd = pWnd->CreateModalWnd(pUniWndMsg->mainHwnd);
		if (IDOK == CWndBase::ShowModalWnd(hWnd))
		{
			::PostMessage(pUniWndMsg->mainHwnd, WM_ENUMWND_MSG_DEL_CHEAT, 0, 0);
		}
		if (pMsg)
		{
			delete pMsg;
			pMsg = nullptr;
		}
	}
	break;
	case UNI_CODE_ENSURE_TUTRIAL:
	{
		UniWndMsg* pMsg = pUniWndMsg;
		CWndEnsure2* pWnd;
		pWnd = new CWndEnsure2("确认启动练习模式");
		HWND hWnd = pWnd->CreateModalWnd(pUniWndMsg->mainHwnd);
		if (IDOK == CWndBase::ShowModalWnd(hWnd))
		{
			::PostMessage(pUniWndMsg->mainHwnd, WM_ENUMWND_MSG_TUTRIAL, 0, 0);
		}
		if (pMsg)
		{
			delete pMsg;
			pMsg = nullptr;
		}
	}
	break;
	case UNI_CODE_ENSURE_EXIT:
	case UNI_CODE_ENSURE_EXIT_RANKING:
	{
		UniWndMsg* pMsg = pUniWndMsg;
		CWndEnsure2* pWnd;
		if (nCode == UNI_CODE_ENSURE_EXIT_RANKING)
			pWnd = new CWndEnsure2("如果现在退出游戏不会为您保存过关记录，确定要退出吗？");
		else
			pWnd = new CWndEnsure2("是否退出当前游戏");
		HWND hWnd = pWnd->CreateModalWnd(pUniWndMsg->mainHwnd);
		if (IDOK == CWndBase::ShowModalWnd(hWnd))
		{
			::PostMessage(pUniWndMsg->mainHwnd, WM_CLOSE, 0, 0);
		}
		if (pMsg)
		{
			delete pMsg;
			pMsg = nullptr;
		}
	}
	break;
	case UNI_CODE_ENSURE_EXIT_ELITE:
	{
		UniWndMsg* pMsg = pUniWndMsg;
		CWndEnsure* pWnd = new CWndEnsure("中途退出，将扣除您的挑战金", " *单人游戏时不扣除");
		HWND hWnd = pWnd->CreateModalWnd(pUniWndMsg->mainHwnd);
		pWnd->UpdateBtnText("继续游戏", "退出");
		if (IDCANCEL == CWndBase::ShowModalWnd(hWnd))
		{
			::PostMessage(pUniWndMsg->mainHwnd, WM_CLOSE, 0, 0);
		}
		if (pMsg)
		{
			delete pMsg;
			pMsg = nullptr;
		}
	}
	break;
	}
}