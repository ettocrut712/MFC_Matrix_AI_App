
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
	, m_TrainingDataFile(_T(""))
	, m_str_SampleSize(_T(""))
	, m_str_NeuronPerSampleInput(_T(""))
	, m_strTraining_tours(_T(""))
	
	, m_str_learning_rate(_T(""))
	, m_display_tour(_T(""))
	, m_display_erreur(_T(""))
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
	DDX_Text(pDX, IDC_TrainingDataFile, m_TrainingDataFile);
	DDX_Text(pDX, IDC_str_SampleSize, m_str_SampleSize);
	DDX_Text(pDX, IDC_str_NeuronPerSampleInput, m_str_NeuronPerSampleInput);
	DDX_Text(pDX, IDC_EDIT_TRAINING_TOURS, m_strTraining_tours);

	DDX_Control(pDX, IDC_LIST_COST_FUNCTION, m_listbox_cost_function);
	DDX_Text(pDX, IDC_EDIT2, m_str_learning_rate);
	DDX_Text(pDX, IDC_TOUR, m_display_tour);
	DDX_Text(pDX, IDC_ERREUR, m_display_erreur);
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
	ON_BN_CLICKED(IDC_OpenTrainingData, &CMFCMatrixAIAppDlg::OnBnClickedOpentrainingdata)
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
	m_str_SampleSize = "0";
	m_str_NeuronPerSampleInput ="0";
	m_str_learning_rate = "0";



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
		m_neuron_per_layer[m_number_layer] = (_wtoi(mStr_layer_1_neurons));
		cLigne.Format(_T("Entrée: %d neurones \t"), m_neuron_per_layer[m_number_layer]);
		m_listBox1.InsertString(-1, cLigne);
		m_number_layer++;
	};

	if (_wtoi(mStr_layer_2_neurons) > 0)
	{
		m_neuron_per_layer[m_number_layer] = (_wtoi(mStr_layer_2_neurons));
		cLigne.Format(_T("Couche cachée 1: %d neurones \t"), m_neuron_per_layer[m_number_layer]);
		m_listBox1.InsertString(-1, cLigne);
		m_number_layer++;
	};

	if (_wtoi(mStr_layer_3_neurons) > 0)
	{
		m_neuron_per_layer[m_number_layer] = (_wtoi(mStr_layer_3_neurons));
		cLigne.Format(_T("Couche cachée 2: %d neurones \t"), m_neuron_per_layer[m_number_layer]);
		m_listBox1.InsertString(-1, cLigne);
		m_number_layer++;
	};

	if (_wtoi(mStr_layer_4_neurons) > 0)
	{
		m_neuron_per_layer[m_number_layer] = (_wtoi(mStr_layer_4_neurons));
		cLigne.Format(_T("Couche cachée 3: %d neurones \t"), m_neuron_per_layer[m_number_layer]);
		m_listBox1.InsertString(-1, cLigne); 
		m_number_layer++;

	};

	if (_wtoi(mStr_layer_5_neurons) > 0)
	{
		m_neuron_per_layer[m_number_layer] = (_wtoi(mStr_layer_5_neurons));
		cLigne.Format(_T("Sortie: %d neurones \t"), m_neuron_per_layer[m_number_layer]);
		m_listBox1.InsertString(-1, cLigne);
		m_number_layer++;
	};

	cLigne.Format(_T("Nombre de niveaux actifs: %d  \t"), m_number_layer);
	m_listBox1.InsertString(-1, cLigne);

	int level = 0;


	int neuron_this_level, neuron_next_level, neuron_previous_level;
	Matrix *myMatrix,*myNewMatrix;

	//*******************************************************

	cLigne.Format(_T("  \t"));
	m_listBox1.InsertString(-1, cLigne);

	cLigne.Format(_T("****CREATION DES MATRICES*** \t"));
	m_listBox1.InsertString(-1, cLigne);

	neuron_this_level = m_neuron_per_layer[0];
	myMatrix = new Matrix(1, neuron_this_level);								//*********************matrice des input (niveau = 0).  Meme forme que matrice des activations des niveaux suivants) *************************
	myMatrix->init_activation_and_z();											//initialise la matrice avec zero pour le moment.

	cLigne.Format(_T("  \t"));
	m_listBox1.InsertString(-1, cLigne);

	cLigne.Format(_T(" Matrice Entrée   %d  x %d  \t"), myMatrix->rows_, myMatrix->cols_);
	m_listBox1.InsertString(-1, cLigne);


	//*******************************

	myMatrix->p[0][0] = 0.05;   //valeurs pour reprendre l'exemple du document.
	myMatrix->p[0][1] = 0.10;


	//******************************
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

	m_listPtrMatrix_activation.push_back(myMatrix);					//Matrice avec les valeurs d'entrée (données = input du système)

	myNewMatrix = new Matrix(1, 1);									//matrice dummy pour permettre de synchroniser les no de matrice avec les niveaux.
	myMatrix = new Matrix(1, 1);
	m_listPtrMatrix_weight.push_back(myMatrix);						// Pour le niveau"0" (entree), c'est une matrice dummy.  Crée pour permettre de synchroniser les no de matrice avec le niveau.
	m_listPtrMatrix_newWeight.push_back(myNewMatrix);				// Pour le niveau"0" (entree), c'est une matrice dummy.  Crée pour permettre de synchroniser les no de matrice avec le niveau.
	m_listPtrMatrix_newBias.push_back(myNewMatrix);					// Pour le niveau"0" (entree), c'est une matrice dummy.  Crée pour permettre de synchroniser les no de matrice avec le niveau.
	m_listPtrMatrix_z.push_back(myMatrix);							// Pour le niveau"0" (entree), c'est une matrice dummy.  Crée pour permettre de synchroniser les no de matrice avec le niveau.
	m_listPtrMatrix_bias.push_back(myMatrix);						// Pour le niveau"0" (entree), c'est une matrice dummy.  Crée pour permettre de synchroniser les no de matrice avec le niveau.
	
	//*******************************************

	for (level = 1; level < (m_number_layer); level++)
	{

		neuron_previous_level = m_neuron_per_layer[level - 1];
		neuron_this_level = m_neuron_per_layer[level];
		neuron_next_level = m_neuron_per_layer[level + 1];

		//****************************************************


		myMatrix = new Matrix(neuron_previous_level, neuron_this_level);				//*****************matrice des ponderations (weight)****************
		myMatrix->init_bias_and_weight();

		myNewMatrix = new Matrix(neuron_previous_level, neuron_this_level);				//*****************matrice des ponderations (weight) pour conserver temporairement 
																						//les nouvelles valeurs lors des calculs de backpropagation****************

		//**************************************************************************
		if (level == 1) {
			myMatrix->p[0][0] = 0.15;   //valeurs pour reprendre l'exemple du document.
			myMatrix->p[0][1] = 0.25;
			myMatrix->p[1][0] = 0.20;
			myMatrix->p[1][1] = 0.30;
		};
		//**************************************************************************


		//**************************************************************************
		if (level == 2) {
			myMatrix->p[0][0] = 0.40;   //valeurs pour reprendre l'exemple du document.
			myMatrix->p[0][1] = 0.50;
			myMatrix->p[1][0] = 0.45;
			myMatrix->p[1][1] = 0.55;
		};
		//**************************************************************************


		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice W(%d)  %d  x %d  \t"), level, myMatrix->rows_, myMatrix->cols_);
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T("  \t"));

		for (int i = 0; i < myMatrix->rows_; ++i)
		{

			for (int j = 0; j < myMatrix->cols_; ++j)
			{
				cLigne.Format(_T("r:%d c:%d [ %6.3f] "), i, j, myMatrix->p[i][j]);			// pour une rangee, affiche chaque colonne(col) de la matrice
				m_listBox1.InsertString(-1, cLigne);
			}

			cLigne.Format(_T("\t "));

			m_listBox1.InsertString(-1, cLigne);
		}


		m_listPtrMatrix_weight.push_back(myMatrix);						// matrice des weights pour la propagation
		m_listPtrMatrix_newWeight.push_back(myNewMatrix);				// matrice des weights apres ajustement lors de la backpropagation. Conserve temporairement les nouvelles valeurs après ajustement.

		//****************************************************





		//m_listPtrMatrix_weight.push_back(new Matrix(neuron_next_level, neuron_this_level));

		myMatrix = new Matrix(1, neuron_this_level);								//*********************matrice des bias *************************
		myMatrix->init_bias_and_weight();
		myNewMatrix = new Matrix(1, neuron_this_level);								// matrice des bias pour conserver les nouveaux bias lors de l'étape de backpropagation.  

		//**************************************************************************
		if (level == 1) {
			myMatrix->p[0][0] = 0.35;   //valeurs pour reprendre l'exemple du document.
			myMatrix->p[0][1] = 0.35;

		};


		if (level == 2) {
			myMatrix->p[0][0] = 0.60;   //valeurs pour reprendre l'exemple du document.
			myMatrix->p[0][1] = 0.60;

		};

		//**************************************************************************




		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice B(%d)  %d x %d \t"), level, myMatrix->rows_, myMatrix->cols_);
		m_listBox1.InsertString(-1, cLigne);

		for (int i = 0; i < myMatrix->rows_; ++i)
		{

			for (int j = 0; j < myMatrix->cols_; ++j)
			{
				cLigne.Format(_T("r:%d c:%d [ %6.3f]  \t"), i, j, myMatrix->p[i][j]);
				m_listBox1.InsertString(-1, cLigne);





			}



			cLigne.Format(_T("\t "));

			m_listBox1.InsertString(-1, cLigne);
		}


		m_listPtrMatrix_bias.push_back(myMatrix);
		m_listPtrMatrix_newBias.push_back(myNewMatrix);



		//*******************************************************



		myMatrix = new Matrix(1, neuron_this_level);								//*********************matrice des calculs (z) *************************
		myMatrix->init_activation_and_z();

		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice Z(%d)  %d x %d \t"), level, myMatrix->rows_, myMatrix->cols_);
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



		myMatrix = new Matrix(1, neuron_this_level);								//*********************matrice des activations: est le resultat du calcul du niveau precedent. Devient input pour prochain niveau *************************
		myMatrix->init_activation_and_z();

		cLigne.Format(_T("  \t"));
		m_listBox1.InsertString(-1, cLigne);

		cLigne.Format(_T(" Matrice A(%d)  %d x %d \t"), level + 1, myMatrix->rows_, myMatrix->cols_);
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


}


void CMFCMatrixAIAppDlg::OnBnClickedCreatetestinput()
{
	// TODO: Add your control notification handler code here
	//Va chercher matrice Ao (input), assigne une valeur a chaque input et affiche la matrice dans la listbox.

	// Matrix* testMatrix;
	CString cLigne;

	// Creation d'un fichier avec des données de test

	/*struct sampleStructure
	{
		int numberOfSample;			// nombre d'échantillons dans le fichier
		int sampleBitSize;				// nombre de bits par échantillon.  On suppose que les valeurs des inputs sont 0 ou 1.  Une autre version sera requise pour des valeurs de 0.0  à 1.0 (nombre réel).
	};

	struct sample
	{
		int input;
		int output;
	};*/


	sampleStructure structureTestEcriture;

	structureTestEcriture.numberOfSample=1;
	structureTestEcriture.inputSampleBitSize = 2;			//8 neurons comme entrée
	structureTestEcriture.outputSampleBitSize = 2;			//3 neurons comme sortie

	sample mySample;


	//**********Echantillon 1

	mySample.input = 255;
	mySample.output = 8;





	std::ofstream fsOut;
	
	fsOut.open("E:/E_Download/AI_sample_NT.bin", std::ofstream::out);

	if (fsOut.is_open())
	{
		fsOut.write((char*) &structureTestEcriture, sizeof(structureTestEcriture));
		fsOut.write((char*)&mySample, sizeof(mySample));


		//**********Echantillon 2
		mySample.input = 128;
		mySample.output = 4;

		fsOut.write((char*)&mySample, sizeof(mySample));

		//**********Echantillon 3

		mySample.input = 64;
		mySample.output = 2;

		fsOut.write((char*)&mySample, sizeof(mySample));
	}
	else
	{

		cLigne.Format(_T(" Create Test Input: ne peut ouvrir un fichier pour écrire"));
		m_listBox1.InsertString(-1, cLigne);
	};


	fsOut.close();

	//testMatrix = m_listPtrMatrix_activation.at(0);		//matrice avec les entrees externe (input) est toujours Ao.

	/*int j=0;

	cLigne.Format(_T(" Test Matrice input A(%d)  %d x %d\t"), 0, testMatrix->rows_, testMatrix->cols_);
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

	m_listBox1.InsertString(-1, cLigne);*/
}

void CMFCMatrixAIAppDlg::multiplicationMatrice(Matrix& a, Matrix& w, Matrix& z, int level)		//Matrix a (activation), W (weight) sont les inputs, Matrix z: output
{
	int tempRow = a.rows_;
	int tempCol = w.cols_;
	int k = a.cols_;

	
	for (int i = 0; i < tempRow; i++) {
		for (int j = 0; j < tempCol; j++) {
			for (int k = 0; k < a.cols_; k++) {
				z.p[i][j] += (a.p[i][k] * w.p[k][j]);
			}
		}
	}
	CString cLigne;

	cLigne.Format(_T("Resultat de la multiplication: Z int.(%d) = A(%d) x W(%d) \t"),level, level-1, level);
	m_listBox1.InsertString(-1, cLigne);

	for (int i = 0; i < z.rows_; i++)
	{
		for (int j = 0; j < z.cols_; j++)
		{
			cLigne.Format(_T("r:%d c:%d [ %7.5f]  \t"), i, j, z.p[i][j]);
			m_listBox1.InsertString(-1, cLigne);
		}

		cLigne.Format(_T("\t "));

		m_listBox1.InsertString(-1, cLigne);
	}
}

//**********************

void CMFCMatrixAIAppDlg::copieMatrice(Matrix& a_source, Matrix& a_destination)		
{
	int tempRow = a_source.rows_;
	int tempCol = a_source.cols_;
	
	double dummy_in, dummy_out;

	for (int r = 0; r < tempRow; r++) 
	{
		for (int c = 0; c < tempCol; c++) 
			{
			a_destination.p[r][c] = a_source.p[r][c];
			dummy_in = a_source.p[r][c];
			dummy_out = a_destination.p[r][c];
			
			

			};
	};
	
}

//*********************


void CMFCMatrixAIAppDlg::additionMatrice(Matrix& z, Matrix& b, int level)		//Matrix z (activation : niveau intermediaire), b (bias) sont les inputs, Matrix z: output
{

	CString cLigne;

	
	for (int i = 0; i < z.rows_; ++i) {
		for (int j = 0; j < z.cols_; ++j) {

			z.p[i][j] = (z.p[i][j] + b.p[i][j]);

		};
	};

	//cLigne.Format(_T("Resultat de l'addition: Z fin(%d). = Z int(%d) + B(%d) \t"), level,level,level);
	//m_listBox1.InsertString(-1, cLigne);

	for (int i = 0; i < z.rows_; ++i)
	{
		for (int j = 0; j < z.cols_; ++j)
		{
			//cLigne.Format(_T("r:%d c:%d [ %7.5f]  \t"), i, j, z.p[i][j]);
			//m_listBox1.InsertString(-1, cLigne);
		};

		cLigne.Format(_T("\t "));

		m_listBox1.InsertString(-1, cLigne);
	};
}

void CMFCMatrixAIAppDlg::initialiseActivationNiveauSuivant(Matrix& z, Matrix&a, int level) //level = le niveau suivant pour activation.  Transfert les sortie du niveau précédent en activation pour le niveau suivant.
{																							// La matrice "z" est la sortie du niveau n-1.  La matrice "a" est l'activation pour le niveau suivant (n).
	CString cLigne;
	
	for (int i = 0; i < z.rows_; ++i) {
		for (int j = 0; j < z.cols_; ++j) {

			a.p[i][j] = z.p[i][j];

		};
	};

	if (level < (m_number_layer-1))
	{
		cLigne.Format(_T("Resultat du transfert de Z fin(%d) a A (%d)   \t"), level-1, level);
		m_listBox1.InsertString(-1, cLigne);
	}
	else
	{
		cLigne.Format(_T("Sortie:A ()   \t"));
		m_listBox1.InsertString(-1, cLigne);
	};

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

int CMFCMatrixAIAppDlg::GetNextSampleInput(int theSampleNumber) 

{
// contenu a developper et ajouter;
	
	CString cLigne;
	sample mySample;

	mySample = m_samples_vector.at(theSampleNumber);

	return mySample.input;
};

int CMFCMatrixAIAppDlg::GetNextSampleOutput(int theSampleNumber)

{
	// contenu a developper et ajouter;
	
	CString cLigne;
	sample mySample;
	
	mySample = m_samples_vector.at(theSampleNumber);

	return mySample.output;
};



std::array<int,10> CMFCMatrixAIAppDlg::ConvertNextSampleToBinary(int theNextSample_input)
{
	std::array<int, 10> myArray;
	int i;
	for (i = 0; i < 10; i++)
		myArray[i] = 0;

	for (i = 0; theNextSample_input > 0; i++)
	{
		myArray[i] = theNextSample_input % 2;
		theNextSample_input = theNextSample_input/2;
	}

	return myArray;
};

void CMFCMatrixAIAppDlg::OnBnClickedTest()
{
	// TODO: Add your control notification handler code here

	//ici, on fait le test de calcul pour les matrices : Ao x Wo +Bo -> Zo.  Sigmoid (Zo) -> A1

	//multiplie matrice 1(Ao) avec matrice 2(Wo) et sauve le resultat dans matrice 3(Zo); ajoute le bias (Bo) a Zo, calcule le sigmoid, repete pour le niveau suivant.

	CString cLigne;
	int theNextSample_input, theNextSample_output;

	std::array<double, 10> inputArray, outputArray;

	int sampleNumber = 0;
	int sampleBitSize = _ttoi(m_str_SampleSize);
	m_fCostFunctionError = 0.0;

	double dummy;

	UpdateData(TRUE);

	learning_rate = _ttof(m_str_learning_rate);

	cLigne.Format(_T("learning rate:  %6.4f  \t"), learning_rate);
	m_listbox_cost_function.InsertString(-1, cLigne);

	
	for (int tours = 0; tours < _wtoi(m_strTraining_tours); tours++)
	{

		for (sampleNumber = 0; sampleNumber < sampleBitSize; sampleNumber++)
		{

			/*
			cLigne.Format(_T("------------------\t"));
			m_listBox1.InsertString(-1, cLigne);

			cLigne.Format(_T("Echantillon: %d  \t"), sampleNumber + 1);
			m_listBox1.InsertString(-1, cLigne);

			cLigne.Format(_T(" \t"));
			m_listBox1.InsertString(-1, cLigne);

			*/

			theNextSample_input = GetNextSampleInput(sampleNumber);

			//inputArray = ConvertNextSampleToBinary(theNextSample_input);									//convertit la valeur de test : nombre entre 0-255, en valeur binaire.  Chaque bit correspond à 1 entrée du réseau.

			//CHANGER CECI POUR UNE FONCTION DE MATRIX : PLUS PROPRE...

			//*********************************
			inputArray[0] = 0.05;

			inputArray[1] = 0.10;

			//*********************************
			int layer;

			for (int n = 0; n < m_listPtrMatrix_activation.at(0)->cols_; n++)
			{
				m_listPtrMatrix_activation.at(0)->p[0][n] = inputArray[n];									// lire les valeurs des données à utiliser comme entrées du réseau
			}

			
			
			cLigne.Format(_T(" Matrice Entrée   %d  x %d  \t"), m_listPtrMatrix_activation.at(0)->rows_, m_listPtrMatrix_activation.at(0)->cols_);
			m_listBox1.InsertString(-1, cLigne);

			for (int i = 0; i < m_listPtrMatrix_activation.at(0)->rows_; ++i)
			{


				for (int j = 0; j < m_listPtrMatrix_activation.at(0)->cols_; ++j)
				{
					cLigne.Format(_T("r:%d c:%d [ %7.5f]  \t"), i, j, m_listPtrMatrix_activation.at(0)->p[i][j]);
					m_listBox1.InsertString(-1, cLigne); ;
				}

				cLigne.Format(_T("\t "));

				m_listBox1.InsertString(-1, cLigne);
			}
			



			//******************************************************************
			for (layer = 1; layer < (m_number_layer); layer++)													// layer 0 = entrée du système.  Layer =1 première couche de calcul.
			{

			//	cLigne.Format(_T("Multiplication.  Niveau: %d  \t"), layer);
			//	m_listBox1.InsertString(-1, cLigne);

				multiplicationMatrice(*m_listPtrMatrix_activation.at(layer -1), *m_listPtrMatrix_weight.at(layer), *m_listPtrMatrix_z.at(layer), layer);  //calcul: entrée(a) * entrée(w) -> sortie(z)

			//	cLigne.Format(_T("Addition.        Niveau: %d \t"), layer);
			//	m_listBox1.InsertString(-1, cLigne);
				
				additionMatrice(*m_listPtrMatrix_z.at(layer), *m_listPtrMatrix_bias.at(layer), layer);										//calcul: sortie(z) <- entrée (z) + entrée (b)

			//	cLigne.Format(_T("Sigmoid.         Niveau: % d \t"), layer);
			//	m_listBox1.InsertString(-1, cLigne);
				
				sigmoidMatrice(*m_listPtrMatrix_z.at(layer), layer);																		//calcul:sortie(z) <- sigmoid(entrée(z))

			//	cLigne.Format(_T("Activation.  Niveau: %d  \t"), layer + 1);
			//	m_listBox1.InsertString(-1, cLigne);
				
				initialiseActivationNiveauSuivant(*m_listPtrMatrix_z.at(layer), *m_listPtrMatrix_activation.at(layer), layer);				//calcul: sortie(a (L+1) <- entrée (z(L))
			};

			// Calcule l'erreur pour cet échantillon et fait la sommation.

			theNextSample_output = GetNextSampleOutput(sampleNumber);

			//outputArray = ConvertNextSampleToBinary(theNextSample_output);

			//*********************************************

			outputArray[0] = 0.01;  //Test pour suivre l'exemple de la doc 
			outputArray[1] = 0.99;
			//*********************************************
			
			m_fCostFunctionError = 0.0;


			for (int output = 0; output < m_structureTestEcriture.outputSampleBitSize; output++)
			{
				m_fCostFunctionError = m_fCostFunctionError + 0.5*(pow((outputArray[output] - m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][output]), 2));

				cLigne.Format(_T("bit: %d   valeur:   %7.5f   activation: %7.5f   \t"), output, outputArray[output], m_listPtrMatrix_activation.at(m_number_layer-1)->p[0][output]);
				m_listbox_cost_function.InsertString(-1, cLigne);
			};




		}; // fin du traitement des échantillons:  for (sampleNumber = 0; 
		
		
		// (b a c k p r o p a g a t i o n)*****************************************DEBUT:   B A C K P R O P A G A T I O N*********************************

		m_display_tour.Format(_T(" %d   "), tours);
		m_display_erreur.Format(_T(" %6.4f    "), m_fCostFunctionError);

		UpdateData(FALSE);

		UpdateWindow();

		//cLigne.Format(_T("Tour %d   erreur : %7.5f  \t"),tours, m_fCostFunctionError);
		//m_listbox_cost_function.InsertString(-1, cLigne);
		

		//Calcul de la variation de la pondération (W-L/jk)

		// dC/dW-L/jk = 2*(A-L/j -C)*A-L/j(1-A-L/j)*A-(L-1)/k

		double activation_x_L0 = 0.0;		//temporaire  activation à la couche "L"
		double activation_x_Lminus = 0.0;	//temporaire  activation a la couche "L-1"
		double weight_x = 0.0;				//temporaire
		double bias_x = 0.0;				//temporaire

		int neuron_L_destination = 0;
		int neuron_Lminus_source = 0;
		double error_jth_Neuron_L_Layer, derivative_weight, derivative_bias;
		/*

		std::vector<Matrix*> m_listPtrMatrix_weight;
		std::vector<Matrix*> m_listPtrMatrix_bias;
		std::vector<Matrix*> m_listPtrMatrix_z;
		std::vector<Matrix*> m_listPtrMatrix_activation;


		myMatrix->rows_, myMatrix->cols_


		m_neuron_per_layer[10]
		*/
		
		
			
		int matrix_layers = m_listPtrMatrix_weight.size()-1;						// les matrices weight et bias sont comprises entre les couches et leur nombre est: nombre de couche  moins un(1). Ici, on lit la grosseur de l'array.
																					// première matrice = matrice[0], seconde matrice = matrice[1], derniere matrice = matrice[m_number_layer - 1]
		
		//*************************************
		int layer = m_number_layer-1;												// Ici on cherche la derniere couche (la sortie) et on recule : back propagation... (entree = L0, sortie = m_numbe_layer -1)
		//*************************************


		/*for (int layer = m_number_layer - 1; layer > 1; layer--)
		{*/
			for (neuron_L_destination = 0; neuron_L_destination < m_neuron_per_layer[layer]; neuron_L_destination++)	// layer -1 : parce que le compteur commence a zero...m_neuron_per_layer[layer]: nombre de neurones dans la couche "L" 
																					// La derniere couche (sortie) = m_neuron_per_layer[layer-1], la premiere couche(entrée) = m_neuron_per_layer[0]
			{
				activation_x_L0 = m_listPtrMatrix_activation.at(layer)->p[0][neuron_L_destination];				//valeur de l'activation de la couche "L"

				error_jth_Neuron_L_Layer = -1.0*(outputArray[neuron_L_destination] - activation_x_L0 ) * activation_x_L0 * (1 - activation_x_L0);



				for (neuron_Lminus_source = 0; neuron_Lminus_source < m_neuron_per_layer[layer-1]; neuron_Lminus_source++)  // Nombre de neurones dans la couche précédente: "L minus one"
				{
					bias_x = m_listPtrMatrix_bias.at(layer)->p[0][neuron_L_destination];
					


				
					weight_x = m_listPtrMatrix_weight.at(layer)->p[neuron_Lminus_source][neuron_L_destination];

					activation_x_Lminus =  m_listPtrMatrix_activation.at(layer-1)->p[0][neuron_Lminus_source];

					/*
					
					cLigne.Format(_T("bias_x:   %7.5f  \t"), bias_x);
					m_listbox_cost_function.InsertString(-1, cLigne);

					cLigne.Format(_T("Weight_x:   %7.5f  \t"), weight_x);
					m_listbox_cost_function.InsertString(-1, cLigne);
					
					cLigne.Format(_T("dA/dZ:   %7.5f  \t"), activation_x_L0* (1 - activation_x_L0));
					m_listbox_cost_function.InsertString(-1, cLigne);


					cLigne.Format(_T("dA/dZ:   %7.5f  \t"), activation_x_L0* (1 - activation_x_L0));
					m_listbox_cost_function.InsertString(-1, cLigne);

					cLigne.Format(_T("dZ/dW:   %7.5f  \t"), activation_x_Lminus);
					m_listbox_cost_function.InsertString(-1, cLigne);

					cLigne.Format(_T("delta:   %7.5f  \t"), error_jth_Neuron_L_Layer);
					m_listbox_cost_function.InsertString(-1, cLigne);

					cLigne.Format(_T("delta*outH1:   %7.5f  \t"), error_jth_Neuron_L_Layer* activation_x_L0);
					m_listbox_cost_function.InsertString(-1, cLigne);
					
					*/

					dummy = weight_x - learning_rate * error_jth_Neuron_L_Layer * activation_x_Lminus;

					m_listPtrMatrix_newWeight.at(layer)->p[neuron_Lminus_source][neuron_L_destination] = dummy; // weight_x - learning_rate * error_jth_Neuron_L_Layer * activation_x_Lminus;

					cLigne.Format(_T("W(%d-%d):   %7.5f  \t"), neuron_Lminus_source,  neuron_L_destination, m_listPtrMatrix_newWeight.at(layer)->p[neuron_Lminus_source][neuron_L_destination]);
					m_listbox_cost_function.InsertString(-1, cLigne);

					dummy = bias_x - learning_rate * error_jth_Neuron_L_Layer;
					m_listPtrMatrix_newBias.at(layer)->p[0][neuron_L_destination] = dummy; // bias_x - learning_rate * error_jth_Neuron_L_Layer;
					cLigne.Format(_T("B(%d-%d):   %7.5f  \t"), 0, neuron_L_destination, m_listPtrMatrix_newBias.at(layer)->p[0][neuron_L_destination]);
					m_listbox_cost_function.InsertString(-1, cLigne);


				};
			};


			

			//****************************************
			layer = m_number_layer - 2;												// Ici on cherche les ajustements pour la premiere couche cachée (hidden layer )  et on recule : back propagation...
			//****************************************

		
			/*int neuron_source, neuron_destination, neuron_sortie;

			for (neuron_source = 0; neuron_source < m_neuron_per_layer[m_number_layer - 3]; neuron_source++)	// layer -1 est le max: parce que le compteur commence a zero...m_neuron_per_layer[layer]: nombre de neurones dans la couche "L-1" 
																					
			{
				
				for (neuron_destination = 0; neuron_destination < m_neuron_per_layer[m_number_layer - 2]; neuron_destination++)

				{
				
					//Calcul de l'erreur cumulative:
					
					for (int neuron_sortie = 0; neuron_sortie < m_neuron_per_layer[m_number_layer - 1]; neuron_sortie++)
					{
						activation_x_L0 = m_listPtrMatrix_activation.at(m_number_layer-1)->p[0][neuron_sortie];					//neurone de sortie: valeur de son activation.
					
						weight_x = m_listPtrMatrix_weight.at(m_number_layer - 2)->p[neuron_source][neuron_sortie];				// pour la premiere couche cachée, on somme les erreurs...

						error_jth_Neuron_L_Layer = error_jth_Neuron_L_Layer + (activation_x_L0 - outputArray[neuron_sortie]) * activation_x_L0 * (1 - activation_x_L0)* weight_x;
					};
				
				


				
					//bias_x = m_listPtrMatrix_bias.at(layer - 1)->p[0][neuron_L];		// bias du niveau L-1




					//weight_x = m_listPtrMatrix_weight.at(layer - 1)->p[neuron_Lminus][neuron_L];  // weight du niveau L-1

					//activation_x_Lminus = m_listPtrMatrix_activation.at(m_number_layer - 3)->p[0][neuron_source];			// va chercher l'activation de la couche précédente.

					//cLigne.Format(_T("dC/da-1:   %7.5f  \t"), (activation_x_L0 - (outputArray[0])));
					//m_listbox_cost_function.InsertString(-1, cLigne);


					
					cLigne.Format(_T("dA/dZ:   %7.5f  \t"), activation_x_L0* (1 - activation_x_L0));
					m_listbox_cost_function.InsertString(-1, cLigne);

					cLigne.Format(_T("dZ/dW:   %7.5f  \t"), activation_x_Lminus);
					m_listbox_cost_function.InsertString(-1, cLigne);

					cLigne.Format(_T("delta:   %7.5f  \t"), error_jth_Neuron_L_Layer);
					m_listbox_cost_function.InsertString(-1, cLigne);

					cLigne.Format(_T("delta*outH1:   %7.5f  \t"), error_jth_Neuron_L_Layer* activation_x_L0);
					m_listbox_cost_function.InsertString(-1, cLigne);


					m_listPtrMatrix_newWeight.at(m_number_layer - 2)->p[neuron_source][neuron_destination] = weight_x - learning_rate * error_jth_Neuron_L_Layer * activation_x_Lminus;

					cLigne.Format(_T("Wx:   %7.5f  \t"), m_listPtrMatrix_weight.at(layer - 1)->p[neuron_Lminus][neuron_L]);
					m_listbox_cost_function.InsertString(-1, cLigne);


					m_listPtrMatrix_newBias.at(layer - 1)->p[0][neuron_L] = bias_x - learning_rate * error_jth_Neuron_L_Layer;
					
				};
			};*/

			// Transfert des pondérations et bias de la matrice temporaire vers la matrice permanente...

			
			
			layer = m_number_layer - 1;		//ici on copie les nouvelles valeurs des bias et pondérations vers les matrices de calcul.


				copieMatrice(*m_listPtrMatrix_newWeight.at(layer), *m_listPtrMatrix_weight.at(layer));   // matrice source - > destination

				copieMatrice(*m_listPtrMatrix_newBias.at(layer), *m_listPtrMatrix_bias.at(layer));
			
			


	}; // For(nombre de tours d'apprentissage: m_strTraining_tours
}

void CMFCMatrixAIAppDlg::sigmoidMatrice(Matrix& z, int level)
{
	CString cLigne;
	
	for (int i = 0; i < z.rows_; ++i) {
		for (int j = 0; j < z.cols_; ++j) {

			z.p[i][j] = (1.0 / (1 + exp(-z.p[i][j])));

		};
	};

	//cLigne.Format(_T("Fonction sigmoid sur: Z_fin.(%d) \t"), level);
	//m_listBox1.InsertString(-1, cLigne);

	for (int i = 0; i < z.rows_; ++i)
	{
		for (int j = 0; j < z.cols_; ++j)
		{
			//cLigne.Format(_T("r:%d c:%d [ %7.5f]  \t"), i, j, z.p[i][j]);
			//m_listBox1.InsertString(-1, cLigne);
		};

		//cLigne.Format(_T("\t "));

		//m_listBox1.InsertString(-1, cLigne);
	};
	
};

/*
void CMenus2Dlg::OnBnClickedActiviteFBN()						// click sur bouton pour lire le fichier des activit�s FBN
{
	CFileDialog ldFile(TRUE);

	if (ldFile.DoModal() == IDOK)
	{
		m_str_NOMFICHIEROUVERT = ldFile.GetFileName();
		m_str_REPERTOIRE = ldFile.GetFolderPath();
		m_str_REPERTOIRE = m_str_REPERTOIRE + L"\\";

		m_FBNConverter.SetFBNActiviteFile(m_str_REPERTOIRE, m_str_NOMFICHIEROUVERT);		// class FBNConverter cr�e pour traiter les activit�s de FBN.

		m_str_FBN_file = m_str_NOMFICHIEROUVERT;				// met le nom du fichier ouvert dans la variable qui sera affichee dans le dialogue sous: fichier FBN


		UpdateData(FALSE);

	};
}
*/

void CMFCMatrixAIAppDlg::OnBnClickedOpentrainingdata()
{
	// TODO: Add your control notification handler code here

	CFileDialog ldFile(TRUE);
	std::ifstream fsIn;
	CString cLigne;


	/*void FBNConverter::SetFBNActiviteFile(CString nom_repertoire, CString nom_fichier)			// sauve le nom du fichier obtenu du site internet de la FBN
{



	std::string my_strRepertoireActiviteFBN(CW2A(nom_repertoire.GetString()));

	my_strRepertoireActiviteFBN = my_strRepertoireActiviteFBN;

	std::string my_strFichierActiviteFBN(CW2A(nom_fichier.GetString()));

	my_strFichierActiviteFBN = my_strFichierActiviteFBN;

	string repertoire = my_strRepertoireActiviteFBN + my_strFichierActiviteFBN;

	m_FBNActiviteFile.open(repertoire, std::ifstream::in);

};*/



	if (ldFile.DoModal() == IDOK)
	{
		m_str_NOMFICHIEROUVERT = CW2A(ldFile.GetFileName());
		m_str_REPERTOIRE = CW2A(ldFile.GetFolderPath());
		m_str_REPERTOIRE = m_str_REPERTOIRE + L"\\";

		
		m_TrainingDataFile = m_str_REPERTOIRE + m_str_NOMFICHIEROUVERT;				// met le nom du fichier ouvert dans la variable qui sera affichee dans le dialogue sous: fichier FBN


		

		m_structureTestEcriture.numberOfSample = 0;			//nombre d'échantillons dans le fichier
		m_structureTestEcriture.inputSampleBitSize = 0;		//nombre de neurons pour l'entrée
		m_structureTestEcriture.outputSampleBitSize = 0;		//nombre de neurons pour la sortie  (étiquette de l'échantillon)

		sample mySample;

		mySample.input = 0;									//bits de l'échantillon (entrée du système)
		mySample.output = 0;								//valeur attendue du système (pour comparer avec l'activation de sortie du système) (étiquette de l'échantillon)




		fsIn.open(m_TrainingDataFile);

		if (fsIn.is_open())
		{
			fsIn.read((char*)&m_structureTestEcriture, sizeof(m_structureTestEcriture));  // lire nombre d'échantillons, nombre de bits pour entrée, nombre de bits pour sortie.
			
			
			for (int j = 0; j < m_structureTestEcriture.numberOfSample; j++)				// pour chaque échantillon, lire l'entrée(couche 0) et la sortie.
			{
				fsIn.read((char*)&mySample, sizeof(mySample));
				m_samples_vector.push_back(mySample);
			};

			fsIn.close();
		}
		else
		{

			cLigne.Format(_T(" Open Training Data: ne peut ouvrir un fichier pour lire les échantillons"));
			m_listBox1.InsertString(-1, cLigne);
		};


		m_str_SampleSize.Format(_T("%d"), m_structureTestEcriture.numberOfSample);
		m_str_NeuronPerSampleInput.Format(_T("%d"), m_structureTestEcriture.inputSampleBitSize);
		mStr_layer_1_neurons.Format(_T("%d"), m_structureTestEcriture.inputSampleBitSize);
		mStr_layer_5_neurons.Format(_T("%d"), m_structureTestEcriture.outputSampleBitSize);

		
	};

	

	UpdateData(FALSE);
}
