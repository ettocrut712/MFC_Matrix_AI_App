
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
	ON_BN_CLICKED(IDC_Create_test_input, &CMFCMatrixAIAppDlg::OnBnClickedCreatetestinput)
	ON_BN_CLICKED(IDC_Test, &CMFCMatrixAIAppDlg::OnBnClickedTest)
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
	Matrix* myMatrix;

	//*******************************************************

	cLigne.Format(_T("****CREATION DES MATRICES*** \t"));
	m_listBox1.InsertString(-1, cLigne);

	neuron_this_level = m_neuron_per_layer[0];
	myMatrix = new Matrix(1, neuron_this_level);								//*********************matrice des input (niveau = 0.  Meme forme que matrice des activations des niveaux suivants) *************************
	myMatrix->init_activation_and_z();											//initialise la matrice avec zero pour le moment.

	cLigne.Format(_T("  \t"));
	m_listBox1.InsertString(-1, cLigne);

	cLigne.Format(_T(" Matrice (a) L: %d:  %d  x %d  \t"), level, myMatrix->rows_, myMatrix->cols_);
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

	for (level=0; level< (m_number_layer-1); level++)
	{
		
		neuron_this_level = m_neuron_per_layer[level];
		neuron_next_level = m_neuron_per_layer[level+1];
		
		//****************************************************

		
		myMatrix = new Matrix(neuron_this_level, neuron_next_level );				//*****************matrice des ponderations (weight)****************
		myMatrix->init_bias_and_weight();

		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice(w) L: %d:  %d  x %d  \t"), level, myMatrix->rows_, myMatrix->cols_);
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

		myMatrix = new Matrix(1, neuron_next_level);								//*********************matrice des bias *************************
		myMatrix->init_bias_and_weight();

		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice (b) L: %d:  %d x %d \t"), level, myMatrix->rows_, myMatrix->cols_);
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



		myMatrix = new Matrix(1, neuron_next_level);								//*********************matrice des calculs (z) *************************
		myMatrix->init_activation_and_z();

		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice (z) L: %d:  %d x %d \t"), level, myMatrix->rows_, myMatrix->cols_);
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

		m_listPtrMatrix_z.push_back(myMatrix);



		myMatrix = new Matrix(1, neuron_next_level);								//*********************matrice des activations: est le resultat du calcul du niveau precedent. Devient input pour prochain niveau *************************
		myMatrix->init_activation_and_z();

		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice (a) L: %d:  %d x %d \t"), level+1, myMatrix->rows_, myMatrix->cols_);
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


	};

	//*******************************************************





}


void CMFCMatrixAIAppDlg::OnBnClickedCreatetestinput()
{
	// TODO: Add your control notification handler code here
	//Va chercher matrice Ao (input), assigne une valeur a chaque input et affiche la matrice dans la listbox.

	Matrix* testMatrix;
	CString cLigne;

	testMatrix = m_listPtrMatrix_activation.at(0);		//matrice avec les entrees externe (input) est toujours Ao.

	int i, j=0;

	cLigne.Format(_T(" Test Matrice input (a) L: %d:  %d x %d\t"), 0, testMatrix->rows_, testMatrix->cols_);
	m_listBox1.InsertString(-1, cLigne);

	for (int i = 0; i < testMatrix->rows_; ++i)
	{
		for (int j = 0; j < testMatrix->cols_; ++j)
		{
			testMatrix->p[i][j] = 1.0;
			cLigne.Format(_T("r:%d c:%d [ %6.3f]  \t"), i, j, testMatrix->p[i][j]);
			m_listBox1.InsertString(-1, cLigne); ;
		}
	}

	cLigne.Format(_T("\t "));

	m_listBox1.InsertString(-1, cLigne);
}

void CMFCMatrixAIAppDlg::multiplicationMatrice(Matrix& a, Matrix& w, Matrix& z, int level)		//Matrix a (activation), W (weight) sont les inputs, Matrix z: output
{
	int tempRow = a.rows_;
	int tempCol = w.cols_;
	int k = a.cols_;

	if (z.cols_ != tempCol || z.rows_ != a.rows_)
	{
		int test=0;
		test = test + 1;

	};

	for (int i = 0; i < tempRow; ++i) {
		for (int j = 0; j < tempCol; ++j) {
			for (int k = 0; k < a.cols_; ++k) {
				z.p[i][j] += (a.p[i][k] * w.p[k][j]);
			}
		}
	}
	CString cLigne;

	cLigne.Format(_T("Resultat de la multiplication: Z int.(%d) = A(%d) x W(%d) \t"),level, level, level);
	m_listBox1.InsertString(-1, cLigne);

	for (int i = 0; i < z.rows_; ++i)
	{
		for (int j = 0; j < z.cols_; ++j)
		{
			cLigne.Format(_T("r:%d c:%d [ %6.3f]  \t"), i, j, z.p[i][j]);
			m_listBox1.InsertString(-1, cLigne);
		}

		cLigne.Format(_T("\t "));

		m_listBox1.InsertString(-1, cLigne);
	}
}


void CMFCMatrixAIAppDlg::additionMatrice(Matrix& z, Matrix& b, int level)		//Matrix z (activation : niveau intermediaire), b (bias) sont les inputs, Matrix z: output
{

	CString cLigne;

	if (z.cols_ != b.cols_ || z.rows_ != b.rows_)
	{
		int test = 0;
		test = test + 1;

	};

	for (int i = 0; i < z.rows_; ++i) {
		for (int j = 0; j < z.cols_; ++j) {

			z.p[i][j] = (z.p[i][j] + b.p[i][j]);

		};
	};

	cLigne.Format(_T("Resultat de l'addition: Z fin(%d). = Z int(%d) + B(%d) \t"), level,level,level);
	m_listBox1.InsertString(-1, cLigne);

	for (int i = 0; i < z.rows_; ++i)
	{
		for (int j = 0; j < z.cols_; ++j)
		{
			cLigne.Format(_T("r:%d c:%d [ %6.3f]  \t"), i, j, z.p[i][j]);
			m_listBox1.InsertString(-1, cLigne);
		};

		cLigne.Format(_T("\t "));

		m_listBox1.InsertString(-1, cLigne);
	};
}

void CMFCMatrixAIAppDlg::initialiseActivationNiveauSuivant(Matrix& z, Matrix&a, int level)
{
	CString cLigne;
	
	for (int i = 0; i < z.rows_; ++i) {
		for (int j = 0; j < z.cols_; ++j) {

			a.p[i][j] = z.p[i][j];

		};
	};


	cLigne.Format(_T("Resultat du transfert de Z fin(%d) a A (%d): niveau:  %d   \t"),level,  level+1, level);
	m_listBox1.InsertString(-1, cLigne);

	for (int i = 0; i < z.rows_; ++i)
	{
		for (int j = 0; j < z.cols_; ++j)
		{
			cLigne.Format(_T("r:%d c:%d [ %6.3f]  \t"), i, j, a.p[i][j]);
			m_listBox1.InsertString(-1, cLigne);
		};

		cLigne.Format(_T("\t "));

		m_listBox1.InsertString(-1, cLigne);
	};
};

void CMFCMatrixAIAppDlg::OnBnClickedTest()
{
	// TODO: Add your control notification handler code here

	//ici, on fait le test de calcul pour les matrices : Ao x Wo +Bo -> Zo.  Sigmoid (Zo) -> A1

	//multiplie matrice 1(Ao) avec matrice 2(Wo) et sauve le resultat dans matrice 3(Zo); ajoute le bias (Bo) a Zo, calcule le sigmoid, repete pour le niveau suivant.

	CString cLigne;

	for(int n= 0; n< (m_number_layer-1); n++)
	{

		cLigne.Format(_T("Multiplication.  Niveau: %d  \t"),n);
		m_listBox1.InsertString(-1, cLigne);

		multiplicationMatrice(*m_listPtrMatrix_activation.at(n), *m_listPtrMatrix_weight.at(n), *m_listPtrMatrix_z.at(n), n);

		cLigne.Format(_T("Addition.        Niveau: %d \t"), n);
		m_listBox1.InsertString(-1, cLigne);
		additionMatrice(*m_listPtrMatrix_z.at(n), *m_listPtrMatrix_bias.at(n), n);

		cLigne.Format(_T("Sigmoid.         Niveau: % d \t"), n);
		m_listBox1.InsertString(-1, cLigne);
		sigmoidMatrice(*m_listPtrMatrix_z.at(n), n);

		cLigne.Format(_T("Activation.  Niveau: %d  \t"),n+1);
		m_listBox1.InsertString(-1, cLigne);
		initialiseActivationNiveauSuivant(*m_listPtrMatrix_z.at(n), *m_listPtrMatrix_activation.at(n+1), n);
	};
	
}

void CMFCMatrixAIAppDlg::sigmoidMatrice(Matrix& z, int level)
{
	CString cLigne;
	
	for (int i = 0; i < z.rows_; ++i) {
		for (int j = 0; j < z.cols_; ++j) {

			z.p[i][j] = (1.0 / (1 + exp(-z.p[i][j])));

		};
	};

	cLigne.Format(_T("Resultat de la fonction sigmoid (%d) \t"), level);
	m_listBox1.InsertString(-1, cLigne);

	for (int i = 0; i < z.rows_; ++i)
	{
		for (int j = 0; j < z.cols_; ++j)
		{
			cLigne.Format(_T("r:%d c:%d [ %6.3f]  \t"), i, j, z.p[i][j]);
			m_listBox1.InsertString(-1, cLigne);
		};

		cLigne.Format(_T("\t "));

		m_listBox1.InsertString(-1, cLigne);
	};
	
};
