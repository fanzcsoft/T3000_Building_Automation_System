#pragma once
#include "afxcmn.h"
#include "CM5/ListCtrlEx.h"

// CT3ModulesOutputDlg dialog

class CT3ModulesOutputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CT3ModulesOutputDlg)

public:
	CT3ModulesOutputDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CT3ModulesOutputDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_T3_OUTPUTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    ListCtrlEx::CListCtrlEx m_outputlist;
};
