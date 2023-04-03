
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
	, m_bool_verbose(FALSE)
	, m_CStr_activation_choice(_T(""))
	, m_str_activationSelection(_T(""))
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
	DDX_Check(pDX, IDC_CHECK_VERBOSE, m_bool_verbose);
	DDX_Control(pDX, IDC_COMBO_ACTIVATION, m_comboListBox_activation);
	DDX_CBString(pDX, IDC_COMBO_ACTIVATION, m_str_activationSelection);
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
	
	ON_BN_CLICKED(IDOK, &CMFCMatrixAIAppDlg::OnBnClickedOk)
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
	
	int count = m_comboListBox_activation.GetCount();
	int index = m_comboListBox_activation.GetCurSel();
	
	m_comboListBox_activation.SetCueBanner(_T("Select activation..."));			//Dans la liste des activations possibles (RELU, Sigmoid), choisit Sigmoid par default (pour le moment).
	
	
	m_str_learning_rate = "0.1";




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
	
	try 
	{
		myMatrix = new Matrix(3, 1);	//new Matrix(1, neuron_this_level);							//*********************matrice des input (niveau = 0).  Meme forme que matrice des activations des niveaux suivants) *************************
		if (myMatrix == NULL) throw "null 308";
	}
	catch (std::bad_alloc) 
	{ 
		myMatrix = new Matrix(1, neuron_this_level);
		std::cout << "ligne 309" << "\n"; 
	};
	

	myMatrix->init_activation_and_z();														//initialise la matrice avec zero pour le moment.

	
	//*******************************

	myMatrix->p[0][0] = 10;																//valeurs pour tester
	myMatrix->p[1][0] = 11;
	myMatrix->p[2][0] = 12;

	//******************************
	
	PrintMatrixToListBox(*myMatrix, level, activationType );
	m_listPtrMatrix_activation.push_back(myMatrix);											//Matrice avec les valeurs d'entrée (données = input du système)
	
																
	
	try 
	{
		myMatrix = new Matrix(3, 3);							//new Matrix(3, 3);
		if (myMatrix == NULL) throw "null 308";
	}
	catch (std::bad_alloc) { std::cout << "ligne 332" << "\n"; };

	PrintMatrixToListBox(*myMatrix, 0, weightType);

	//*******************************

	myMatrix->p[0][0] = 1;																//valeurs pour reprendre l'exemple du document.
	myMatrix->p[0][1] = 2;
	myMatrix->p[0][2] = 3;
	myMatrix->p[1][0] = 4;
	myMatrix->p[1][1] = 5;																//valeurs pour reprendre l'exemple du document.
	myMatrix->p[1][2] = 6;
	myMatrix->p[2][0] = 7;
	myMatrix->p[2][1] = 8;
	myMatrix->p[2][2] = 9;																//valeurs pour reprendre l'exemple du document.
	


	//******************************


	//******************************

	m_listPtrMatrix_weight.push_back(myMatrix);												// Pour le niveau"0" (entree), c'est une matrice dummy.  Crée pour permettre de synchroniser les no de matrice avec le niveau.
	
	//***test ici  

	myMatrix = new Matrix(3, 1);
	m_listPtrMatrix_z.push_back(myMatrix);

	multiplicationMatrice(*m_listPtrMatrix_weight.at(0),  *m_listPtrMatrix_activation.at(0), *m_listPtrMatrix_z.at(0), 1);	//calcul: entrée(W(L-1)) * entrée(A(L)) -> sortie(Z(L))
	
		
	try
	{
		myMatrix = new Matrix(1, m_neuron_per_layer[level]);									//*****************matrice des gradients****************
	}
	catch (std::bad_alloc) { std::cout << "ligne 365" << "\n"; };

	
	PrintMatrixToListBox(*myMatrix, 0, gradientType);
	m_listPtrMatrix_gradient.push_back(myMatrix);
	
	//*******************************************

	for (level = 1; level < (m_number_layer); level++)
	{

		neuron_previous_level = m_neuron_per_layer[level - 1];
		neuron_this_level = m_neuron_per_layer[level];
		neuron_next_level = m_neuron_per_layer[level + 1];

		try 
		{
			myMatrix = new Matrix(1, m_neuron_per_layer[level]);									//*****************matrice des gradients****************
		}
		catch (std::bad_alloc) { std::cout << "ligne 382" << "\n"; };
		
		//myMatrix->init_bias_and_weight();
		PrintMatrixToListBox(*myMatrix, level, gradientType);
		m_listPtrMatrix_gradient.push_back(myMatrix);

		
		
		//****************************************************


		
		
		try
		{
			myMatrix = new Matrix(neuron_previous_level, neuron_this_level);				//*****************matrice des ponderations (weight)****************
			if (myMatrix == NULL) throw "null 413";
		}
		catch (std::bad_alloc) { std::cout << "ligne 404" << "\n"; };


		myMatrix->init_bias_and_weight();

		

		try
		{
			myNewMatrix = new Matrix(neuron_previous_level, neuron_this_level);				//*****************matrice des ponderations (weight) pour conserver les valeurs intermediaires de "new Weight"
			if (myMatrix == NULL) throw "null 308";
		}
		catch (std::bad_alloc) { std::cout << "ligne 413" << "\n"; };


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

		PrintMatrixToListBox(* myMatrix, level, weightType);

		


		m_listPtrMatrix_weight.push_back(myMatrix);												// matrice des weights pour la propagation
		m_listPtrMatrix_newWeight.push_back(myNewMatrix);										// matrice des weights apres ajustement lors de la backpropagation. Conserve temporairement les nouvelles valeurs après ajustement.

		//****************************************************





		//m_listPtrMatrix_weight.push_back(new Matrix(neuron_next_level, neuron_this_level));

		
		try
		{
			myMatrix = new Matrix(1, neuron_this_level);										//*********************matrice des bias *************************
			if (myMatrix == NULL) throw "null 308";
		}
		catch (std::bad_alloc) { std::cout << "ligne 458" << "\n"; };
		

		myMatrix->init_bias_and_weight();
		

		try
		{
			myNewMatrix = new Matrix(1, neuron_this_level);										// matrice des bias pour conserver les nouveaux bias lors de l'étape de backpropagation.
			if (myMatrix == NULL) throw "null 308";
		}
		catch (std::bad_alloc) { std::cout << "ligne 468" << "\n"; };


		//**************************************************************************
		if (level == 1) {
			myMatrix->p[0][0] = 0.35;															//valeurs pour reprendre l'exemple du document.
			myMatrix->p[0][1] = 0.35;

		};


		if (level == 2) {
			myMatrix->p[0][0] = 0.60;															//valeurs pour reprendre l'exemple du document.
			myMatrix->p[0][1] = 0.60;

		};

		//**************************************************************************

		
		PrintMatrixToListBox(*myMatrix, level, biasType);

		m_listPtrMatrix_bias.push_back(myMatrix);
		m_listPtrMatrix_newBias.push_back(myNewMatrix);




		

		try
		{
			myMatrix = new Matrix(1, neuron_this_level);										//*********************matrice des calculs (z) *************************
			if (myMatrix == NULL) throw "null 308";
		}
		catch (std::bad_alloc) { std::cout << "ligne 502" << "\n"; };

		myMatrix->init_activation_and_z();

		PrintMatrixToListBox(*myMatrix, level, zType);


		m_listPtrMatrix_z.push_back(myMatrix);
	
		
		
		try
		{
			myMatrix = new Matrix(1, neuron_this_level);										//*********************matrice des activations: est le resultat du calcul du niveau precedent. Devient input pour prochain niveau *************************
			if (myMatrix == NULL) throw "null 308";
		}
		catch (std::bad_alloc) { std::cout << "ligne 517" << "\n"; };

		myMatrix->init_activation_and_z();
		
		PrintMatrixToListBox(*myMatrix, level, activationType);

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
		int numberOfSample;				// nombre d'échantillons dans le fichier
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

void CMFCMatrixAIAppDlg::multiplicationMatrice(Matrix& Ma, Matrix& Mb, Matrix& Mc, int level)		//Matrix "a" , "b" sont les inputs, Matrix "c": output
{
	//multiplication de matrices R x C (row x colonne).  Le nombre de colonne de la matrice "a" doit etre egal au nombre de "row" de la matrice "b" sinon kaput.  Resultat: dimension de la matrice C: a.row x b.colonne
	
	int tempRow = Mb.rows_;
	int tempCol = Ma.cols_;

	assert(Mb.rows_ == Ma.cols_);

	int k = Mb.cols_;
	double temp1, temp2, temp3;
	
	for (int Bc = 0; Bc < Mb.cols_; Bc++)					// Bc = colonnes de la matrice "B"
	{
		for (int Ar = 0; Ar < Mb.rows_; Ar++)				// Ar= row de la matrice "A"
		{

			Mc.p[Ar][Bc] = 0.0;								//initialise avant d'accumuler le produit des multiplications.

			for (int Ac = 0; Ac < Ma.cols_; Ac++)			// Ac= colonne de la matrice "A"
			{
				Mc.p[Ar][Bc] += (Ma.p[Ar][Ac] * Mb.p[Ac][Bc]);

			};
		};

	};
	CString cLigne;

	if (m_bool_verbose)
	{
		cLigne.Format(_T("Resultat de la multiplication: C int.(%d) = A(%d) x B(%d) \t"), level, level - 1, level);
		m_listBox1.InsertString(-1, cLigne);

		for (int i = 0; i < Mc.rows_; i++)
		{
			for (int j = 0; j < Mc.cols_; j++)
			{
				cLigne.Format(_T("r:%d c:%d [ %7.5f]  \t"), i, j, Mc.p[i][j]);
				m_listBox1.InsertString(-1, cLigne);
			};

			cLigne.Format(_T("\t "));

			m_listBox1.InsertString(-1, cLigne);
		};
	};
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

	if (m_bool_verbose)
	{
		cLigne.Format(_T("Resultat de l'addition: Z fin(%d). = Z int(%d) + B(%d) \t"), level, level, level);
		m_listBox1.InsertString(-1, cLigne);

		for (int i = 0; i < z.rows_; ++i)
		{
			for (int j = 0; j < z.cols_; ++j)
			{
				cLigne.Format(_T("r:%d c:%d [ %7.5f]  \t"), i, j, z.p[i][j]);
				m_listBox1.InsertString(-1, cLigne);
			};

			cLigne.Format(_T("\t "));

			m_listBox1.InsertString(-1, cLigne);
		};
	};
}

void CMFCMatrixAIAppDlg::initActivation(Matrix& z, Matrix&a, int level)						//level = le niveau suivant pour activation.  Transfert les sortie du niveau précédent en activation pour le niveau suivant.
{																							// La matrice "z" est la sortie du niveau n-1.  La matrice "a" est l'activation pour le niveau suivant (n).
	CString cLigne;
	
	for (int i = 0; i < z.rows_; ++i) {
		for (int j = 0; j < z.cols_; ++j) {

			a.p[i][j] = z.p[i][j];

		};
	};

	
	if (m_bool_verbose)
	{
		if (level < (m_number_layer - 1))
		{
			cLigne.Format(_T("Activation: Z fin(%d) a A (%d)   \t"), level - 1, level);
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

	//ici, on fait le test de calcul pour les matrices : A(L-1) x W(L) +B(L) -> Z(L).  Sigmoid (Z(L)) -> A(L)

	//multiplie matrice 1(Ao) avec matrice 2(Wo) et sauve le resultat dans matrice 3(Zo); ajoute le bias (Bo) a Zo, calcule le sigmoid, repete pour le niveau suivant.

	CString cLigne;
	int theNextSample_input, theNextSample_output;
	int sampleNumber = 0;
	int sampleSize = _ttoi(m_str_SampleSize);
	
	double activation_x_L0 = 0.0;		// activation à la couche "L"
	double activation_x_Lminus = 0.0;	// activation à la couche "L-1"
	
	double bias_x , weight_x= 0.0;		// bias et weight actuel (avant modification)
	
	
	int neurone_k_source, neurone_j_destination = 0;
	
	double error_jth_Neuron_L_Layer;
	
	m_fCostFunctionError = 0.0;

	UpdateData(TRUE);

	


	learning_rate = _ttof(m_str_learning_rate);						// va lire le "learning rate"

	cLigne.Format(_T("learning rate:  %6.4f  \t"), learning_rate);
	m_listbox_cost_function.InsertString(-1, cLigne);

	
	for (int tours = 0; tours < _wtoi(m_strTraining_tours); tours++)
	{

		for (sampleNumber = 0; sampleNumber < sampleSize; sampleNumber++)
		{

			

			theNextSample_input = GetNextSampleInput(sampleNumber);  // Développer une procédure ici...

			

			//CHANGER CECI POUR UNE FONCTION DE MATRIX : PLUS PROPRE...

			//*********************************
			m_double_inputArray_X[0] = 0.05;

			m_double_inputArray_X[1] = 0.10;

			//*********************************
			int layer;

			for (int n = 0; n < m_listPtrMatrix_activation.at(0)->cols_; n++)
			{
				m_listPtrMatrix_activation.at(0)->p[0][n] = m_double_inputArray_X[n];									// lire les valeurs des données à utiliser comme entrées du réseau
			}

			
			if (m_bool_verbose)
			{
				cLigne.Format(_T(" Matrice Entrée   %d  x %d  \t"), m_listPtrMatrix_activation.at(0)->rows_, m_listPtrMatrix_activation.at(0)->cols_);
				m_listBox1.InsertString(-1, cLigne);

				for (int i = 0; i < m_listPtrMatrix_activation.at(0)->rows_; ++i)
				{


					for (int j = 0; j < m_listPtrMatrix_activation.at(0)->cols_; ++j)
					{
						cLigne.Format(_T("r:%d c:%d [ %7.5f]  \t"), i, j, m_listPtrMatrix_activation.at(0)->p[i][j]);
						m_listBox1.InsertString(-1, cLigne); ;
					};

					cLigne.Format(_T("\t "));

					m_listBox1.InsertString(-1, cLigne);
				};
			};



			//****************************************************************** DEBUT: P R O P A G A T I O N vers l'avant **********************************************
			for (layer = 1; layer < (m_number_layer); layer++)													// layer 0 = entrée du système.  Layer =1 première couche de calcul.
			{


				multiplicationMatrice(*m_listPtrMatrix_activation.at(layer -1), *m_listPtrMatrix_weight.at(layer), *m_listPtrMatrix_z.at(layer), layer);	//calcul: entrée(A(L-1)) * entrée(W(L)) -> sortie(Z(L))

			
				
				additionMatrice(*m_listPtrMatrix_z.at(layer), *m_listPtrMatrix_bias.at(layer), layer);														//calcul: sortie(z) <- entrée (z) + entrée (b)

			
				if (m_str_activationSelection == "Sigmoid")
				{
					sigmoidMatrice(*m_listPtrMatrix_z.at(layer), layer);																					//calcul:sortie(z) <- sigmoid(entrée(z))
				};
				
				if (m_str_activationSelection == "RELU")
				{
					RELU(*m_listPtrMatrix_z.at(layer), layer);																								//calcul:sortie(z) <- RELU(entrée(z))
				};
			
				
				initActivation(*m_listPtrMatrix_z.at(layer), *m_listPtrMatrix_activation.at(layer), layer);								//calcul: a(L) <- z(L)
			};

			//****************************************************************** FIN: P R O P A G A T I O N vers l'avant **********************************************

			// Calcule l'erreur pour cet échantillon et fait la sommation.

			theNextSample_output = GetNextSampleOutput(sampleNumber);

			//outputArray = ConvertNextSampleToBinary(theNextSample_output);

			//*********************************************

			m_double_outputArray_Y[0] = 0.01;  //Test pour suivre l'exemple de la doc 
			m_double_outputArray_Y[1] = 0.99;
			//*********************************************
			
			m_fCostFunctionError = 0.0;


			for (int output = 0; output < m_structureTestEcriture.outputSampleBitSize; output++)
			{
				m_fCostFunctionError = m_fCostFunctionError + 0.5*(pow((m_double_outputArray_Y[output] - m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][output]), 2));

			};




		}; // fin du traitement des échantillons:  for (sampleNumber = 0; 
		
		
		// ****************************************************************DEBUT:   B A C K P R O P A G A T I O N*********************************

		m_display_tour.Format(_T(" %d   "), tours);
		m_display_erreur.Format(_T(" %15.13f    "), m_fCostFunctionError);

		UpdateData(FALSE);

		UpdateWindow();

		if (m_bool_verbose)
		{
			cLigne.Format(_T("Tour %d   erreur : %7.5f  \t"), tours, m_fCostFunctionError);
			m_listbox_cost_function.InsertString(-1, cLigne);
		};

		
			
		//changements commencent ici...
																					
		for (int layer = m_number_layer - 1; layer > 0; layer--)
		{

			//initialise le vecteur gradient pour L-1

			for (neurone_k_source = 0; neurone_k_source < m_neuron_per_layer[layer - 1]; neurone_k_source++)							// m_neuron_per_layer est un "array" qui contient le nombre de neurones pour chaque couche.
			{
				m_listPtrMatrix_gradient.at(layer - 1)->p[0][neurone_k_source] = 0.0;
			};

			// test modification GIT

			for (neurone_j_destination = 0; neurone_j_destination < m_neuron_per_layer[layer]; neurone_j_destination++)

				// m_number_layer -1 : parce que le compteur commence a zero...ex: 3 couches: Couche 0:(entrée), 1:(hidden layer), 2:(sortie). 
				// La derniere couche (sortie) = m_neuron_per_layer[layer-1], la premiere couche(entrée) = m_neuron_per_layer[0]
			{
				
				
				if (layer == (m_number_layer - 1))																						// Si c'est la derniere couche (la sortie)
				{
					activation_x_L0 = m_listPtrMatrix_activation.at(layer)->p[0][neurone_j_destination];								// m_listPtrMatrix_activation est un "vecteur" de "Matrix".
					
					if (m_str_activationSelection == "Sigmoid")
					{
						error_jth_Neuron_L_Layer = (activation_x_L0 - m_double_outputArray_Y[neurone_j_destination]) * activation_x_L0 * (1 - activation_x_L0);
					};

					if (m_str_activationSelection == "RELU")
					{
						error_jth_Neuron_L_Layer = (activation_x_L0 - m_double_outputArray_Y[neurone_j_destination]);
					};


				}
				else 
				{
					error_jth_Neuron_L_Layer = m_listPtrMatrix_gradient.at(layer)->p[0][neurone_j_destination];
				
				};

				double temp;

				for (neurone_k_source = 0; neurone_k_source < m_neuron_per_layer[layer -1]; neurone_k_source++)				// Nombre de neurones dans la couche précédente: "L minus one"
				{
					bias_x = m_listPtrMatrix_bias.at(layer)->p[0][neurone_j_destination];									// Lecture de la valeur du bias b(L) avant modification

					weight_x = m_listPtrMatrix_weight.at(layer)->p[neurone_k_source][neurone_j_destination];				// Lecture de la valeur de la ponderation w(L), avant modification

					activation_x_Lminus = m_listPtrMatrix_activation.at(layer-1)->p[0][neurone_k_source];					// Lecture de l'activation a(L-1)

					
					
					if (m_bool_verbose)
					{

						cLigne.Format(_T("bias_x:   %7.5f  \t"), bias_x);
						m_listbox_cost_function.InsertString(-1, cLigne);

						cLigne.Format(_T("Weight_x:   %7.5f  \t"), weight_x);
						m_listbox_cost_function.InsertString(-1, cLigne);

						cLigne.Format(_T("dA/dZ:   %7.5f  \t"), activation_x_L0 * (1 - activation_x_L0));
						m_listbox_cost_function.InsertString(-1, cLigne);


						cLigne.Format(_T("dA/dZ:   %7.5f  \t"), activation_x_L0 * (1 - activation_x_L0));
						m_listbox_cost_function.InsertString(-1, cLigne);

						cLigne.Format(_T("dZ/dW:   %7.5f  \t"), activation_x_Lminus);
						m_listbox_cost_function.InsertString(-1, cLigne);

						cLigne.Format(_T("delta:   %7.5f  \t"), error_jth_Neuron_L_Layer);
						m_listbox_cost_function.InsertString(-1, cLigne);

						cLigne.Format(_T("delta*outH1:   %7.5f  \t"), error_jth_Neuron_L_Layer* activation_x_L0);
						m_listbox_cost_function.InsertString(-1, cLigne);


					};

					temp = weight_x - learning_rate * error_jth_Neuron_L_Layer * activation_x_Lminus;
					

					m_listPtrMatrix_newWeight.at(layer)->p[neurone_k_source][neurone_j_destination] = weight_x - learning_rate * error_jth_Neuron_L_Layer * activation_x_Lminus;

					if (m_bool_verbose)
					{
						cLigne.Format(_T("W(%d-%d):   %7.5f  \t"), neurone_k_source, neurone_j_destination, m_listPtrMatrix_newWeight.at(layer)->p[neurone_k_source][neurone_j_destination]);
						m_listbox_cost_function.InsertString(-1, cLigne);
					};

					temp = bias_x - learning_rate * error_jth_Neuron_L_Layer;
					

					m_listPtrMatrix_newBias.at(layer)->p[0][neurone_j_destination] = bias_x - learning_rate * error_jth_Neuron_L_Layer;

					if (m_bool_verbose)
					{
						cLigne.Format(_T("B(%d):   %7.5f  \t"), neurone_j_destination, m_listPtrMatrix_newBias.at(layer)->p[0][neurone_j_destination]);
						m_listbox_cost_function.InsertString(-1, cLigne);
					};

					temp = m_listPtrMatrix_gradient.at(layer - 1)->p[0][neurone_k_source] + error_jth_Neuron_L_Layer * weight_x;
					
					
					m_listPtrMatrix_gradient.at(layer - 1)->p[0][neurone_k_source] = m_listPtrMatrix_gradient.at(layer - 1)->p[0][neurone_k_source] + error_jth_Neuron_L_Layer * weight_x;			//Gradient: sommation des dEdA(L-1) sur le neurone source.
					if (m_bool_verbose)
					{
						cLigne.Format(_T("Gradient(S:%d D:%d):   G:%7.5f  \t"), neurone_k_source, neurone_j_destination, m_listPtrMatrix_gradient.at(layer - 1)->p[0][neurone_k_source]);
						m_listbox_cost_function.InsertString(-1, cLigne);
					};


				};  // for neurone_k_source

			}; // for neurone_j_destination

		};// for layer...

			
			// ***************************** MISE A JOUR DES PONDERATIONS ET BIAS*********************************************************
			// Transfert des nouveaux W(L) et B(L) des matrices temporaires (newWeight, newBias) vers les matrices de calcul.
 			
			

		for (int layer = m_number_layer - 1; layer > 0; layer--)
		{
			copieMatrice(*m_listPtrMatrix_newWeight.at(layer), *m_listPtrMatrix_weight.at(layer));		// matrice source - > destination

			copieMatrice(*m_listPtrMatrix_newBias.at(layer), *m_listPtrMatrix_bias.at(layer));


		};
			
		saveToFileActivation_lossFunction();															// sauve activation + function loss dans un fichier pour analyse...

																	

	}; // For(nombre de tours d'apprentissage: m_strTraining_tours

	fileOutputStream.close();

	// Ecriture des valeurs des bias et weight, pour analyse.
	
	imprimeMatrices();							//imprime les matrices des ponderations (weight + bias).  Pour analyse...

}; // fin: OnBnClickedTest()


void CMFCMatrixAIAppDlg::saveToFileActivation_lossFunction()

{
	// ************************ Ecriture des activations vs target : pour analyse des resultats **************************
	CString cLigne;

	for (int neurone_j_destination = 0; neurone_j_destination < m_neuron_per_layer[m_number_layer - 1]; neurone_j_destination++)  //imprime dans un fichier pour analyse...
	{
		cLigne.Format(_T("Activation finale:   %7.5f        vs  %7.5f             \t"), m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][neurone_j_destination], (m_double_outputArray_Y[neurone_j_destination]));
		m_listbox_cost_function.InsertString(-1, cLigne);


		CString activation, target;

		std::string s_activation;

		s_activation = std::to_string(m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][neurone_j_destination]) + ",";
		fileOutputStream << s_activation;

		s_activation = std::to_string(m_double_outputArray_Y[neurone_j_destination]) + ",";

		fileOutputStream << s_activation;

		s_activation = m_display_erreur + ",";

		fileOutputStream << s_activation;

	};

	fileOutputStream << std::endl;
};


void CMFCMatrixAIAppDlg::imprimeMatrices()
{
	for (int level = 1; level < (m_number_layer); level++)
	{

		CString cLigne;
		//Matrix matrice;
		CString filename;


		cLigne.Format(_T("Weight_Matrix_level_%d_"), level);
		filename = cLigne + _T(".csv");

		m_listPtrMatrix_weight.at(level)->printTheMatrixToFile(m_str_REPERTOIRE, filename);



		cLigne.Format(_T("Bias_Matrix_level_%d_ "), level);
		filename = cLigne + _T(".csv");

		m_listPtrMatrix_bias.at(level)->printTheMatrixToFile(m_str_REPERTOIRE, filename);
	};
};

double CMFCMatrixAIAppDlg::calcul_erreur_cumul_L_minus_1(int neuron_source)
{
	//fait la somme des erreurs pour le "neuron" de la couche L-1 (utilisé pour backpropagation de la couche L-1 et précédentes)

	double erreur_cumulative = 0.0;
	double temp = 0.0;
	int neuron_terminaison;

	for (neuron_terminaison = 0; neuron_terminaison < m_neuron_per_layer[m_number_layer - 1]; neuron_terminaison++)   // m_number_layer -1 = couche "L", la derniere couche avant la sortie.
	{
		
		temp = ( m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][neuron_terminaison]- m_double_outputArray_Y[neuron_terminaison]);  //calcule l'erreur entre la valeur obtenue (...activation...) 
		temp = temp*(m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][neuron_terminaison])*((1- m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][neuron_terminaison]));
		temp = temp* m_listPtrMatrix_weight.at(m_number_layer - 1)->p[neuron_source][neuron_terminaison];
																																			//et la valeur attendue (m_double_outputArray_Y)
		erreur_cumulative = erreur_cumulative + temp;
	};

		return erreur_cumulative;
																																						
};



void CMFCMatrixAIAppDlg::sigmoidMatrice(Matrix& z, int level)
{
	CString cLigne;
	
	for (int i = 0; i < z.rows_; ++i) {
		for (int j = 0; j < z.cols_; ++j) {

			z.p[i][j] = (1.0 / (1 + exp(-z.p[i][j])));

		};
	};

	
};

void CMFCMatrixAIAppDlg::RELU(Matrix& z, int level)
{
	CString cLigne;

	for (int i = 0; i < z.rows_; ++i) {
		for (int j = 0; j < z.cols_; ++j) {

			if (z.p[i][j] < 0)
			{
				z.p[i][j] = 0.01* z.p[i][j];
			};
		};
	};


};



void CMFCMatrixAIAppDlg::OnBnClickedOpentrainingdata()
{
	// TODO: Add your control notification handler code here

	CFileDialog ldFile(TRUE);
	std::ifstream fsIn;
	CString cLigne;

	

	if (ldFile.DoModal() == IDOK)
	{
		m_str_NOMFICHIEROUVERT = CW2A(ldFile.GetFileName());
		m_str_REPERTOIRE = CW2A(ldFile.GetFolderPath());
		m_str_REPERTOIRE = m_str_REPERTOIRE + L"\\";

		
		m_TrainingDataFile = m_str_REPERTOIRE + m_str_NOMFICHIEROUVERT;				// met le nom du fichier ouvert dans la variable qui sera affichee dans le dialogue sous: fichier FBN

		m_outputDataFile = m_str_REPERTOIRE + _T("ML_AI_file.csv");

		fileOutputStream.open(m_outputDataFile);
		

		m_structureTestEcriture.numberOfSample = 0;									//nombre d'échantillons dans le fichier
		m_structureTestEcriture.inputSampleBitSize = 0;								//nombre de neurons pour l'entrée
		m_structureTestEcriture.outputSampleBitSize = 0;							//nombre de neurons pour la sortie  (étiquette de l'échantillon)

		sample mySample;

		mySample.input = 0;															//bits de l'échantillon (entrée du système)
		mySample.output = 0;														//valeur attendue du système (pour comparer avec l'activation de sortie du système) (étiquette de l'échantillon)




		fsIn.open(m_TrainingDataFile);

		if (fsIn.is_open())
		{
			fsIn.read((char*)&m_structureTestEcriture, sizeof(m_structureTestEcriture));	// lire nombre d'échantillons, nombre de bits pour entrée, nombre de bits pour sortie.
			
			
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


void CMFCMatrixAIAppDlg::cleanMemoryPointer()
{
	int level;

	for (level = 0; level < (m_number_layer); level++)
	{

		

		delete m_listPtrMatrix_gradient.at(level);				
		delete  m_listPtrMatrix_weight.at(level);
		delete  m_listPtrMatrix_newWeight.at(level);
		delete  m_listPtrMatrix_bias.at(level);
		delete  m_listPtrMatrix_newBias.at(level);
		delete  m_listPtrMatrix_z.at(level);
		delete  m_listPtrMatrix_activation.at(level);


	};

	
};


void CMFCMatrixAIAppDlg::PrintMatrixToListBox(Matrix& myMatrix, int level, int type)  //  type:  weight =0, bias =1, activation =2, Z=3;
{
	
	CString cLigne;

	cLigne.Format(_T("  \t"));
	m_listBox1.InsertString(-1, cLigne);
	
	if (type == 0) cLigne.Format(_T(" Matrice W(%d)  %d  x %d  \t"), level, myMatrix.rows_, myMatrix.cols_);
	if (type == 1) cLigne.Format(_T(" Matrice B(%d)  %d  x %d  \t"), level, myMatrix.rows_, myMatrix.cols_);
	if (type == 2) cLigne.Format(_T(" Matrice A(%d)  %d  x %d  \t"), level, myMatrix.rows_, myMatrix.cols_);
	if (type == 3) cLigne.Format(_T(" Matrice Z(%d)  %d  x %d  \t"), level, myMatrix.rows_, myMatrix.cols_);
	if (type == 4) cLigne.Format(_T(" Matrice G(%d)  %d  x %d  \t"), level, myMatrix.rows_, myMatrix.cols_);

	m_listBox1.InsertString(-1, cLigne);

	cLigne.Format(_T("  \t"));

	for (int i = 0; i < myMatrix.rows_; ++i)
	{

		for (int j = 0; j < myMatrix.cols_; ++j)
		{
			cLigne.Format(_T("r:%d c:%d [ %6.4f] "), i, j, myMatrix.p[i][j]);			// pour une rangee, affiche chaque colonne(col) de la matrice
			m_listBox1.InsertString(-1, cLigne);
		}

		cLigne.Format(_T("\t "));

		m_listBox1.InsertString(-1, cLigne);
	}


};

void CMFCMatrixAIAppDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
	cleanMemoryPointer();

	
	CDialogEx::OnOK();
}
