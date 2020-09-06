
// MFC_Matrix_AI_AppDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC_Matrix_AI_App.h"
#include "MFC_Matrix_AI_AppDlg.h"
#include "afxdialogex.h"
#include "matrix.h"
#include <iterator>
#include <algorithm>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMFCMatrixAIAppDlg dialog



CMFCMatrixAIAppDlg::CMFCMatrixAIAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_MATRIX_AI_APP_DIALOG, pParent)
	, mStr_layer_1_neurons(_T(""))
	, mStr_layer_2_neurons(_T(""))
	, mStr_layer_3_neurons(_T(""))
	, mStr_layer_4_neurons(_T(""))
	, mStr_layer_5_neurons(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMatrixAIAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NEURONS_LAYER_1, mStr_layer_1_neurons);
	DDX_Text(pDX, IDC_NEURONS_LAYER_2, mStr_layer_2_neurons);
	DDX_Text(pDX, IDC_NEURONS_LAYER_3, mStr_layer_3_neurons);
	DDX_Text(pDX, IDC_NEURONS_LAYER_4, mStr_layer_4_neurons);
	DDX_Text(pDX, IDC_NEURONS_LAYER_5, mStr_layer_5_neurons);
	DDX_Control(pDX, IDC_LIST1, m_listBox1);
}

BEGIN_MESSAGE_MAP(CMFCMatrixAIAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CMFCMatrixAIAppDlg::OnBnClickedButton1)
	//ON_EN_CHANGE(IDC_EDIT1, &CMFCMatrixAIAppDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_CREATE_MATRIX, &CMFCMatrixAIAppDlg::OnBnClickedCreateMatrix)
END_MESSAGE_MAP()


// CMFCMatrixAIAppDlg message handlers

BOOL CMFCMatrixAIAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	//mStr_number_layer ="0";
	mStr_layer_1_neurons="0";
	mStr_layer_2_neurons = "0";
	mStr_layer_3_neurons = "0";
	mStr_layer_4_neurons = "0";
	mStr_layer_5_neurons = "0";

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCMatrixAIAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCMatrixAIAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCMatrixAIAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMFCMatrixAIAppDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMFCMatrixAIAppDlg::OnBnClickedCreateMatrix()
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	CString cLigne;

	for (int i = 0; i < 10; i++)
		m_neuron_per_layer[i] = 0;

		
	m_number_layer = 0;
	
	//lire le nombre de neurons par couche et ajoute ce nombre à la liste "m_neuron_per_layer"
	
	
	if (_wtoi(mStr_layer_1_neurons) > 0)
	{
		m_neuron_per_layer[0] = (_wtoi(mStr_layer_1_neurons));
		m_number_layer++;

		cLigne.Format(_T("Niveau 1: %d neurones \t"), m_neuron_per_layer[0]);
		m_listBox1.InsertString(-1, cLigne);

	};
	
	if (_wtoi(mStr_layer_2_neurons) > 0)
	{
		m_neuron_per_layer[1] = (_wtoi(mStr_layer_2_neurons));
		m_number_layer++;

		cLigne.Format(_T("Niveau 2: %d neurones \t"), m_neuron_per_layer[1]);
		m_listBox1.InsertString(-1, cLigne);
	};

	if (_wtoi(mStr_layer_3_neurons) > 0)
	{
		m_neuron_per_layer[2] = (_wtoi(mStr_layer_3_neurons));
		m_number_layer++;

		cLigne.Format(_T("Niveau 3: %d neurones \t"), m_neuron_per_layer[2]);
		m_listBox1.InsertString(-1, cLigne);
	};

	if (_wtoi(mStr_layer_4_neurons) > 0)
	{
		m_neuron_per_layer[3] = (_wtoi(mStr_layer_4_neurons));
		m_number_layer++;

		cLigne.Format(_T("Niveau 4: %d neurones \t"), m_neuron_per_layer[3]);
		m_listBox1.InsertString(-1, cLigne);

	};

	if (_wtoi(mStr_layer_5_neurons) > 0)
	{
		m_neuron_per_layer[4] = (_wtoi(mStr_layer_5_neurons));
		m_number_layer++;

		cLigne.Format(_T("Niveau 5: %d neurones \t"), m_neuron_per_layer[4]);
		m_listBox1.InsertString(-1, cLigne);
	};

	cLigne.Format(_T("Nombre de niveaux actifs: %d  \t"), m_number_layer);
	m_listBox1.InsertString(-1, cLigne);

	int level = 0;

	
	int neuron_this_level, neuron_next_level;

	for (level=0; level< (m_number_layer-1); level++)
	{
		
		neuron_this_level = m_neuron_per_layer[level];
		neuron_next_level = m_neuron_per_layer[level+1];
		
		//****************************************************

		Matrix* myMatrix;
		myMatrix = new Matrix(neuron_next_level, neuron_this_level);				//*****************matrice des ponderations (weight)****************
		myMatrix->init_bias_and_weight();

		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice(w) L: %d:  %d  x %d  \t"), level, neuron_next_level, neuron_this_level);
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T("  \t"));													

		for (int i = 0; i < myMatrix->rows_; ++i)
		{
			
			for (int j = 0; j < myMatrix->cols_; ++j)
			{
				cLigne.Format(_T("r:%d c:%d [ %6.3f] "),i,j, myMatrix->p[i][j]);			// pour une rangee, affiche chaque colonne(col) de la matrice
				m_listBox1.InsertString(-1, cLigne);
			}

			cLigne.Format(_T("\t "));												

			m_listBox1.InsertString(-1, cLigne);
		}


		m_listPtrMatrix_weight.push_back(myMatrix);

		//****************************************************


		


		//m_listPtrMatrix_weight.push_back(new Matrix(neuron_next_level, neuron_this_level));

		myMatrix = new Matrix(neuron_next_level, 1);								//*********************matrice des bias *************************
		myMatrix->init_bias_and_weight();

		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice (b) L: %d:  %d  x 1  \t"), level, neuron_next_level);
		m_listBox1.InsertString(-1, cLigne);

		for (int i = 0; i < myMatrix->rows_; ++i)
		{
			
			for (int j = 0; j < myMatrix->cols_; ++j)
			{
				cLigne.Format(_T("r:%d c:%d [ %6.3f]  \t"), i, j, myMatrix->p[i][j]);
				m_listBox1.InsertString(-1, cLigne); ;
			}

			cLigne.Format(_T("\t "));												

			m_listBox1.InsertString(-1, cLigne);
		}

		m_listPtrMatrix_bias.push_back(myMatrix);



		//*******************************************************



		myMatrix = new Matrix(neuron_next_level, 1);								//*********************matrice des activations *************************
		myMatrix->init_activation_and_z();

		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice (a) L: %d:  %d  x 1  \t"), level, neuron_next_level);
		m_listBox1.InsertString(-1, cLigne);

		for (int i = 0; i < myMatrix->rows_; ++i)
		{


			for (int j = 0; j < myMatrix->cols_; ++j)
			{
				cLigne.Format(_T("r:%d c:%d [ %6.3f]  \t"), i, j, myMatrix->p[i][j]);
				m_listBox1.InsertString(-1, cLigne); ;
			}

			cLigne.Format(_T("\t "));												

			m_listBox1.InsertString(-1, cLigne);
		}

		m_listPtrMatrix_activation.push_back(myMatrix);
		


		//*******************************************



		myMatrix = new Matrix(neuron_next_level, 1);								//*********************matrice des calculs (z) *************************
		myMatrix->init_activation_and_z();

		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice (z) L: %d:  %d  x 1  \t"), level, neuron_next_level);
		m_listBox1.InsertString(-1, cLigne);

		for (int i = 0; i < myMatrix->rows_; ++i)
		{


			for (int j = 0; j < myMatrix->cols_; ++j)
			{
				cLigne.Format(_T("r:%d c:%d [ %6.3f]  \t"), i, j, myMatrix->p[i][j]);
				m_listBox1.InsertString(-1, cLigne); ;
			}

			cLigne.Format(_T("\t "));												//insert retour de chariot (change de ligne)

			m_listBox1.InsertString(-1, cLigne);
		}

		m_listPtrMatrix_z.push_back(myMatrix);

		

	};

	//*******************************************************



	

	std::list<Matrix*>::iterator it;

	for (it = m_listPtrMatrix_weight.begin(); it != m_listPtrMatrix_weight.end(); it++)
	{
		
		Matrix *itMatrix;

	//	itMatrix =it;

		//itMatrix = new Matrix;

		//itMatrix = it  ; // m_listPtrMatrix_weight.begin();
		
		//itMatrix* = it;
		//itMatrix->init_bias_and_weight();

	};


	





}
