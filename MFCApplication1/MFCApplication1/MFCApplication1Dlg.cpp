
// MFCApplication1Dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <vector>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CMFCApplication1Dlg



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, zue(_T(" "))
	, shifr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	ES_MULTILINE;
	DDX_Text(pDX, IDC_EDIT1, zue);
	DDX_Text(pDX, IDC_EDIT2, shifr);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1,)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Обработчики сообщений CMFCApplication1Dlg

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	CFileDialog dlg(1, NULL, NULL, NULL, L"Файл для шифрации ГРУППА RSA ЛОХИ (*.txt)|*txt||");
	const int n = 999;

	if (dlg.DoModal() == IDOK);
	{
		// ifstream 
		CString Filename = dlg.GetPathName();
		std::ifstream ifs(Filename);

		while(!(ifs.eof()))
		{
			char stroka[n];
			ifs.getline(stroka, sizeof(stroka));
			zue += CString(stroka);
		}
	}
	UpdateData(0);
}

void textq() 
{
	//cout << "Vvedite text dlia shifracii: ";
	//string m_t;
	//cin >> m_t;
	//cout << m_t << endl;

	//int tmp;
	//vector<int> m_tmp;
	//int l = m.length();
	//m_tmp.resize(l);

	//for (int i = 0; i < l; i++)
	{
	//	tmp = (int)m_t[i];
	//	m_tmp[i] = tmp;
	}

	//ShowVector(m_tmp, 1);
	//cout << endl;
	//m = m_tmp;
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	UpdateData(1);
	CFileDialog dlg(0, NULL, NULL, NULL, L"Файл для шифрации ГРУППА RSA ЛОХИ (*.txt)|*txt||");
	const int n = 999;

	if (dlg.DoModal() == IDOK);
	{	fstream file;
		CString Filename = dlg.GetPathName();
		file.open(Filename, ios::out);
		for (int i = 0; i < zue.GetLength(); i++)
		{
			file << (char)zue[i];
		} 
		file.close();
	}

	// TODO: добавьте свой код обработчика уведомлений
}
void CMFCApplication1Dlg::OnBnClickedButton3()
{
	UpdateData(1);
	shifr = zue;
	UpdateData(0);
	// TODO: добавьте свой код обработчика уведомлений
}