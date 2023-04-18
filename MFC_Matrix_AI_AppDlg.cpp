﻿
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
	, mStr_layer_1_neurons(_T("2"))
	, mStr_layer_2_neurons(_T("2"))
	, mStr_layer_3_neurons(_T("2"))
	, mStr_layer_4_neurons(_T("0"))
	, mStr_layer_5_neurons(_T("0"))
	, m_TrainingDataFile(_T(""))
	, m_str_SampleSize(_T(""))
	, m_str_NeuronPerSampleInput(_T(""))
	, m_strTraining_tours(_T("1"))
	
	, m_str_learning_rate(_T(""))
	, m_display_tour(_T("0"))
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
	DDX_Check(pDX, IDC_CHECK_Verb_activation, m_bool_verb_activation);
	DDX_Control(pDX, IDC_COMBO_activation, m_comboListBox_activation);
	DDX_CBString(pDX, IDC_COMBO_activation, m_str_activationSelection);
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

	ON_EN_CHANGE(IDC_TOUR, &CMFCMatrixAIAppDlg::OnEnChangeTour)
	ON_EN_CHANGE(IDC_ERREUR, &CMFCMatrixAIAppDlg::OnEnChangeErreur)
	ON_BN_CLICKED(IDC_SauveMatrices, &CMFCMatrixAIAppDlg::OnBnClickedSauvematrices)
	ON_BN_CLICKED(IDC_BUTTON_LireMatrices, &CMFCMatrixAIAppDlg::OnBnClickedButtonLireMatrices)
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
	mStr_layer_1_neurons="2";
	mStr_layer_2_neurons = "2";
	mStr_layer_3_neurons = "2";
	mStr_layer_4_neurons = "0";
	mStr_layer_5_neurons = "0";
	m_str_SampleSize = "0";
	m_str_NeuronPerSampleInput ="0";
	m_display_tour = "1";
	
	int count = m_comboListBox_activation.GetCount();
	int index = m_comboListBox_activation.GetCurSel();
	
	m_comboListBox_activation.SetCueBanner(_T("Select activation..."));			//Dans la liste des activations possibles (RELU, Sigmoid), choisit Sigmoid par default (pour le moment).
	m_str_activationSelection = "Sigmoid";
	
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

	if (m_number_layer > 0) cleanMemoryPointer();					// efface la configuration precedente ici.

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


	Matrix *myMatrix;

	//*******************************************************

	cLigne.Format(_T("  \t"));
	m_listBox1.InsertString(-1, cLigne);

	cLigne.Format(_T("****CREATION DES MATRICES*** \n"));
	m_listBox1.InsertString(-1, cLigne);


	for (level = 0; level < (m_number_layer); level++)
	{

		try {
			myMatrix = new Matrix(m_neuron_per_layer[level], 1);					//*********************matrice des activations Aj
			myMatrix->reset_matrix_to_zero();
			m_listPtrMatrix_activation.push_back(myMatrix);							//Matrice avec les activations (Sigmoid ou ReLU) (Aj)
			
			cLigne.Format(_T(" Matrice activation  Level: %d  \n"), level);
			m_listBox1.InsertString(-1, cLigne);

			myMatrix = new Matrix(m_neuron_per_layer[level], 1);					
			myMatrix->reset_matrix_to_zero();
			m_listPtrMatrix_dCo_dBj.push_back(myMatrix);							//matrice des gradients pour les polarisations.  UTILISE POUR CALCUL DE dCo_dAk(L-1)

			cLigne.Format(_T(" Matrice dCo_dBj: %d  \n"), level);
			m_listBox1.InsertString(-1, cLigne);

			myMatrix = new Matrix(m_neuron_per_layer[level], 1);
			myMatrix->reset_matrix_to_zero();
			m_listPtrMatrix_z.push_back(myMatrix);									//Matrice des resultat (Zj)
			
			cLigne.Format(_T(" Matrice z: %d  \n"), level);
			m_listBox1.InsertString(-1, cLigne);

			myMatrix = new Matrix(m_neuron_per_layer[level], 1);
			myMatrix->reset_matrix_to_zero();
			m_listPtrMatrix_gradient.push_back(myMatrix);							//Le gradient est defini comme (Aj - Target) ou la difference entre la valeur de sortie et le resultat attendu.							
			
			cLigne.Format(_T(" Matrice gradient: %d  \n"), level);
			m_listBox1.InsertString(-1, cLigne);

			myMatrix = new Matrix(m_neuron_per_layer[level], 1);					//Matrice des polarisations (bias)
			
			if (level == 0)
			{
				myMatrix->reset_matrix_to_zero();
			}
			else
			{
				myMatrix->init_bias_and_weight();
			};

			m_listPtrMatrix_bias.push_back(myMatrix);
			
			cLigne.Format(_T(" Matrice bias  Level: %d  \n"), level);
			m_listBox1.InsertString(-1, cLigne);

			if (m_bool_verbose)
			{
				PrintMatrixToListBox(*myMatrix, biasType);
			};
		}

		catch (std::bad_alloc) {
			std::cout << "Creation des matrices: L310:  bad_alloc" << "\n";
		};
	};

	try {
		myMatrix = new Matrix(2, 1);												// matrice dummy W pour le niveau zero. Permet d'eviter un decalage entre la nomenclature W(0,1,2...) de cette matrice et les autres matrices (B)0,1,2,...)
		myMatrix->reset_matrix_to_zero();
		m_listPtrMatrix_weight.push_back(myMatrix);

		cLigne.Format(_T(" Matrice Weight (W)  Level: %d  \n"), 0);
		m_listBox1.InsertString(-1, cLigne);
		
		if (m_bool_verbose)
		{
			PrintMatrixToListBox(*myMatrix, weightType);
		};

											

		myMatrix = new Matrix(2, 1);												// matrice dummy nW pour le niveau zero. Permet d'eviter un decalage entre la nomenclature W(0,1,2...) de cette matrice et les autres matrices (B)0,1,2,...)
		myMatrix->reset_matrix_to_zero();
		m_listPtrMatrix_newWeight.push_back(myMatrix);
		
		cLigne.Format(_T(" Matrice newWeight (nW)  Level: %d  \n"), 0);
		m_listBox1.InsertString(-1, cLigne);
		
	}

	catch (std::bad_alloc) {
		std::cout << "Creation des matrices (Wjk): L380:  bad_alloc" << "\n";
	};

	for (level = 1; level < (m_number_layer); level++)
	{

		try {
			myMatrix = new Matrix(m_neuron_per_layer[level], m_neuron_per_layer[level-1]);	
			myMatrix->init_bias_and_weight();
			m_listPtrMatrix_weight.push_back(myMatrix);

			cLigne.Format(_T(" Matrice Weight (W)  Level: %d  \n"), level);
			m_listBox1.InsertString(-1, cLigne);
			
			if (m_bool_verbose)
			{
				PrintMatrixToListBox(*myMatrix, weightType);
			};
																//Matrice des ponderations (Wjk)

			myMatrix = new Matrix(m_neuron_per_layer[level], m_neuron_per_layer[level - 1]);
			m_listPtrMatrix_newWeight.push_back(myMatrix);												//Matrice pour les valeur temporaire de  W , lors des calculs.
			
			cLigne.Format(_T(" Matrice newWeight (nW)  Level: %d  \n"), level);
			m_listBox1.InsertString(-1, cLigne);
		}

		catch (std::bad_alloc) {
			std::cout << "Creation des matrices (Wjk): L340:  bad_alloc" << "\n";
		};
	};

	cLigne.Format(_T("****FIN CREATION DES MATRICES*** \n"));
	m_listBox1.InsertString(-1, cLigne);

	
	CreateInputTest();							//genere des donnes (input) allant dans l'interval: 0 - 1;
	CreateOutputTest();							//genere des donnes (resultat attendu : Y output) dans l'interval: 0 - 1;

	

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
	CString cLigne;

	assert(Mb.rows_ == Ma.cols_);

		
	for (int Bc = 0; Bc < Mb.cols_; Bc++)					// Bc = colonnes de la matrice "B"
	{
		for (int Ar = 0; Ar < Ma.rows_; Ar++)				// Ar= row de la matrice "A"
		{

			Mc.p[Ar][Bc] = 0.0;								//initialise avant d'accumuler le produit des multiplications.

			for (int Ac = 0; Ac < Ma.cols_; Ac++)			// Ac= colonne de la matrice "A"
			{
				Mc.p[Ar][Bc] += (Ma.p[Ar][Ac] * Mb.p[Ac][Bc]);

			};
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


void CMFCMatrixAIAppDlg::additionMatrice(Matrix& Ma, Matrix& Mb, int level)		//Matrice:  Ma = Ma + Mb.  Entrees; Ma, Mb.  Sortie: Ma
{

	CString cLigne;

	assert(Mb.cols_ == Ma.cols_);
	assert(Mb.rows_ == Ma.rows_);

	for (int i = 0; i < Ma.rows_; ++i) {
		for (int j = 0; j < Ma.cols_; ++j) {

			Ma.p[i][j] = (Ma.p[i][j] + Mb.p[i][j]);

		};
	};

	
}

void CMFCMatrixAIAppDlg::activation(Matrix& z, Matrix&a, int level)						//level = le niveau suivant pour activation.  Transfert les sortie du niveau précédent en activation pour le niveau suivant.
{																						// La matrice "z" est la sortie du niveau n-1.  La matrice "a" est l'activation pour le niveau suivant (n).
	CString cLigne;
	
	int i = 0;

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

	return 0;//mySample.output;
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

void CMFCMatrixAIAppDlg::Propagation()
{
	
	CString cLigne;
	int layer;

	for (layer = 1; layer < (m_number_layer); layer++)													// layer 0 = entrée du système.  Layer =1 première couche de calcul.
	{


		multiplicationMatrice(*m_listPtrMatrix_weight.at(layer), *m_listPtrMatrix_activation.at(layer - 1), *m_listPtrMatrix_z.at(layer), layer);	//calcul: entrée(W(L)) * entrée(A(L-1)) -> sortie(Z(L))

		if (m_bool_verbose)
		{
			cLigne.Format(_T("Propagation: multiplication: (Layer: %d): Z(L) <-- W(L: %d) x A(L: %d) \t"), layer, layer, layer - 1);
			m_listBox1.InsertString(-1, cLigne);
			PrintMatrixToListBox(*m_listPtrMatrix_weight.at(layer), weightType);
			PrintMatrixToListBox(*m_listPtrMatrix_activation.at(layer - 1), activationType);					//int weightType = 0, biasType = 1, activationType =2, zType =3 gradientType = 4;
			PrintMatrixToListBox(*m_listPtrMatrix_z.at(layer), zType);
			cLigne.Format(_T("Propagation: addition: (Layer: %d)  A(L: %d)= B(L: %d) + Z(L: %d) \t"), layer, layer, layer, layer);
			m_listBox1.InsertString(-1, cLigne);
		};

		additionMatrice(*m_listPtrMatrix_z.at(layer), *m_listPtrMatrix_bias.at(layer), layer);														//calcul: sortie(z) <- entrée (z) + entrée (b)

		if (m_bool_verbose)
		{
			PrintMatrixToListBox(*m_listPtrMatrix_bias.at(layer), biasType);
			PrintMatrixToListBox(*m_listPtrMatrix_z.at(layer), zType);
		};

		copieMatrice(*m_listPtrMatrix_z.at(layer), *m_listPtrMatrix_activation.at(layer));															// Z(L) -> A(L)

		if (m_str_activationSelection == "Sigmoid")
		{
			sigmoidMatrice(*m_listPtrMatrix_activation.at(layer), layer);																			//calcul:sortie(z) <- sigmoid(entrée(z))
		};

		if (m_str_activationSelection == "RELU")
		{
			RELU(*m_listPtrMatrix_activation.at(layer), layer);																						//calcul:sortie(z) <- RELU(entrée(z))
		};


		char myString[60];
		strcpy_s(myString, (LPCSTR)m_str_activationSelection.GetString());

		if (m_bool_verb_activation)
		{
			cLigne.Format(_T("Propagation: : (Layer: %d) A(L:%d) <--  (%hs   )(Z(L: %d)) \t"), layer, layer, myString, layer); // m_str_activationSelection
			m_listBox1.InsertString(-1, cLigne);

			PrintMatrixToListBox(*m_listPtrMatrix_activation.at(layer), activationType);
		};
	};  // for layer (propagation)
};

void CMFCMatrixAIAppDlg::BackPropagation()
{
	double dCo_dBj = 0.0, dCo_dWkj = 0.0, dCo_dAkLminus = 0.0;
	CString cLigne;

	double activation_L = 0.0;					// activation à la couche "L"
	double activation_x_Lminus = 0.0;			// activation à la couche "L-1"
	double bias_x = 0.0, weight_x = 0.0;		// bias et weight actuel (avant modification)
	int neurone_k_source, neurone_j_destination = 0;

	learning_rate = _ttof(m_str_learning_rate);	// va lire le "learning rate"

	for (int layer = m_number_layer - 1; layer > 0; layer--)
	{

		// **************************Calcule du gradient bias dCo/dBj) pour cette couche****************************

		for (neurone_j_destination = 0; neurone_j_destination < m_neuron_per_layer[layer]; neurone_j_destination++)
		{

			//dCo_dAkLminus = 0.0;



			if (m_str_activationSelection == "Sigmoid")
			{
				activation_L = m_listPtrMatrix_activation.at(layer)->p[neurone_j_destination][0];									// activation = Ak(j)
				dCo_dBj = m_listPtrMatrix_gradient.at(layer)->p[neurone_j_destination][0] * activation_L * (1 - activation_L);		//dCo/dBj
			}

			if (m_str_activationSelection == "RELU")
			{
				dCo_dBj = m_listPtrMatrix_gradient.at(layer)->p[neurone_j_destination][0];											//dCo/dBj
			};



			m_listPtrMatrix_dCo_dBj.at(layer)->p[neurone_j_destination][0] = dCo_dBj;												//matrice des gradients pour les polarisations.  UTILE POUR CALCUL DE dCo_dAk(L-1)


			m_listPtrMatrix_bias.at(layer)->p[neurone_j_destination][0] = m_listPtrMatrix_bias.at(layer)->p[neurone_j_destination][0] - learning_rate * m_listPtrMatrix_dCo_dBj.at(layer)->p[neurone_j_destination][0];

			if (m_bool_verbose)
			{
				cLigne.Format(_T("BackProp:(dCo/dBj) lev %d, j %d,k:%d  bias: %e  \n"), layer, neurone_j_destination, 0, m_listPtrMatrix_bias.at(layer)->p[neurone_j_destination][0]);
				m_listbox_cost_function.InsertString(-1, cLigne);
			};
		};


		//******************************Debut: Calcul du gradient ponderation (dCo/dWjk) ************************************************

		for (neurone_j_destination = 0; neurone_j_destination < m_neuron_per_layer[layer]; neurone_j_destination++)
		{

			for (neurone_k_source = 0; neurone_k_source < m_neuron_per_layer[layer - 1]; neurone_k_source++)						// Nombre de neurones dans la couche précédente: "L minus one"
			{

				if (m_str_activationSelection == "Sigmoid")
				{
					activation_L = m_listPtrMatrix_activation.at(layer)->p[neurone_j_destination][0];								// activation = Ak(j)
					dCo_dWkj = m_listPtrMatrix_gradient.at(layer)->p[neurone_j_destination][0] * activation_L * (1 - activation_L) * m_listPtrMatrix_activation.at(layer - 1)->p[neurone_k_source][0];
				}

				if (m_str_activationSelection == "RELU")
				{
					dCo_dWkj = m_listPtrMatrix_gradient.at(layer)->p[neurone_j_destination][0] * m_listPtrMatrix_activation.at(layer - 1)->p[neurone_k_source][0];
				};

				m_listPtrMatrix_newWeight.at(layer)->p[neurone_j_destination][neurone_k_source] = m_listPtrMatrix_weight.at(layer)->p[neurone_j_destination][neurone_k_source] - learning_rate * dCo_dWkj;  // bon ordre des parmetres de p[] ???

				if (m_bool_verbose)
				{
					cLigne.Format(_T("BP:  neurones:j %d, k%d (dCo/dWk): %e  \n"),  neurone_j_destination, neurone_k_source, dCo_dWkj);
					m_listbox_cost_function.InsertString(-1, cLigne);


					cLigne.Format(_T("BP:  neurones-> j: %d, k: %d nouv ponderation: %e  \n"), neurone_j_destination, neurone_k_source, m_listPtrMatrix_newWeight.at(layer)->p[neurone_j_destination][neurone_k_source]);
					m_listbox_cost_function.InsertString(-1, cLigne);
				};
			};

		};
		//**************************Fin: Calcul du gradient ponderation (dCo/dWjk)************************************************



		//**************************Debut: Calcul du gradient ponderation (dCo/dAk)****************************************************

		for (neurone_j_destination = 0; neurone_j_destination < m_neuron_per_layer[layer - 1]; neurone_j_destination++)
		{

			for (neurone_k_source = 0; neurone_k_source < m_neuron_per_layer[layer]; neurone_k_source++)						// Nombre de neurones dans la couche précédente: "L minus one"
			{
				dCo_dAkLminus += m_listPtrMatrix_dCo_dBj.at(layer)->p[neurone_k_source][0] * m_listPtrMatrix_weight.at(layer)->p[neurone_k_source][neurone_j_destination];
			};

			m_listPtrMatrix_gradient.at(layer - 1)->p[neurone_j_destination][0] = -learning_rate * dCo_dAkLminus;

			if (m_bool_verbose)
			{
				cLigne.Format(_T(" \n, BP:dCo_al(L-1)  level: %d neurones  j: %d, k: %d    dCo_ak(L-1):  %7.5f  \n"), layer, neurone_j_destination, neurone_k_source, dCo_dAkLminus);
				m_listbox_cost_function.InsertString(-1, cLigne);

				cLigne.Format(_T(" \n, BP:gradient  level: %d neurones  j: %d, k: %d    G:  %7.5f  \n"), layer, neurone_j_destination, neurone_k_source, m_listPtrMatrix_gradient.at(layer - 1)->p[neurone_j_destination][0]);
				m_listbox_cost_function.InsertString(-1, cLigne);
			};

			dCo_dAkLminus = 0.0;
		};

		//**************************Fin: Calcul du gradient ponderation (dCo/dAk)****************************************************

		copieMatrice(*m_listPtrMatrix_newWeight.at(layer), *m_listPtrMatrix_weight.at(layer));			//copie new weights -> weights


	};// for layer...

};


double CMFCMatrixAIAppDlg::CostFunction()
{
	
	CString cLigne;

	m_fCostFunctionError = 0.0;

	//m_neuron_per_layer[m_number_layer]

	for (int output = 0; output < m_neuron_per_layer[m_number_layer - 1]; output++)
	{
		
		double one, two;
		one = m_double_outputArray_Y[output];
		two = m_listPtrMatrix_activation.at(m_number_layer - 1)->p[output][0];
		
		m_fCostFunctionError = m_fCostFunctionError + (pow((m_double_outputArray_Y[output] - m_listPtrMatrix_activation.at(m_number_layer - 1)->p[output][0]), 2));

		if (m_bool_verbose)
		{
			cLigne.Format(_T("Propagation: cost function  target: %6.4f    sortie:  %6.4f \n"), m_double_outputArray_Y[output], m_listPtrMatrix_activation.at(m_number_layer - 1)->p[output][0]);
			m_listBox1.InsertString(-1, cLigne);
		};
	};

	m_display_erreur.Format(_T(" %15.13f    "), m_fCostFunctionError);

	UpdateData(TRUE);
	
	//calcul gradient pour dernier niveau

	for (int neurone_j_destination = 0; neurone_j_destination < m_neuron_per_layer[m_number_layer - 1]; neurone_j_destination++)
	{

		m_listPtrMatrix_gradient.at(m_number_layer - 1)->p[neurone_j_destination][0] = m_listPtrMatrix_activation.at(m_number_layer - 1)->p[neurone_j_destination][0] - m_double_outputArray_Y[neurone_j_destination];

	};

	return m_fCostFunctionError;
};


void CMFCMatrixAIAppDlg::CreateInputTest()
{
	struct tm y2k = { 0 };

	double counter = 1;


	SYSTEMTIME time;
	GetSystemTime(&time);
	long time_ms = (time.wSecond * 1000) + time.wMilliseconds;

	std::default_random_engine generator{ static_cast<long unsigned int>(time_ms) };
	std::normal_distribution<double> distribution(0.0, 1.0);

	for (int i = 0; i < m_neuron_per_layer[0]; ++i)
	{
			m_double_inputArray_X[i] = distribution(generator);
	};

};



void CMFCMatrixAIAppDlg::CreateOutputTest()
{
	struct tm y2k = { 0 };

	double counter = 1;


	SYSTEMTIME time;
	GetSystemTime(&time);
	long time_ms = (time.wSecond * 1000) + time.wMilliseconds;

	std::default_random_engine generator{ static_cast<long unsigned int>(time_ms) };
	std::normal_distribution<double> distribution(0.0, 1.0);

	for (int i = 0; i < m_neuron_per_layer[m_number_layer-1]; ++i)
	{
		
		m_double_outputArray_Y[i] = distribution(generator);
	};

};


void CMFCMatrixAIAppDlg::OnBnClickedTest()
{
	// TODO: Add your control notification handler code here

	//ici, on fait le test de calcul pour les matrices : A(L-1) x W(L) +B(L) -> Z(L).  Sigmoid (Z(L)) -> A(L)

	//multiplie matrice 1(Ao) avec matrice 2(Wo) et sauve le resultat dans matrice 3(Zo); ajoute le bias (Bo) a Zo, calcule le sigmoid, repete pour le niveau suivant.

	CString cLigne;


	UpdateData(TRUE);

	
	

//	CreateInputTest();							//genere des donnes (input) allant dans l'interval: 0 - 1;
//	CreateOutputTest();							//genere des donnes (resultat attendu : Y output) dans l'interval: 0 - 1;

	for (int tours = 1; tours < _wtoi(m_strTraining_tours)+1; tours++)
	{

		int layer;

		for (int n = 0; n < m_listPtrMatrix_activation.at(0)->rows_; n++)
		{
			m_listPtrMatrix_activation.at(0)->p[n][0] = m_double_inputArray_X[n];									// lire les valeurs des données test à utiliser comme entrées du réseau
		}

		if (m_bool_verbose)
		{
			cLigne.Format(_T(" Matrice Entrée (Xo)   %d  x %d  \n"), m_listPtrMatrix_activation.at(0)->rows_, m_listPtrMatrix_activation.at(0)->cols_);
			m_listBox1.InsertString(-1, cLigne);

			for (int i = 0; i < m_listPtrMatrix_activation.at(0)->rows_; ++i)
			{


				for (int j = 0; j < m_listPtrMatrix_activation.at(0)->cols_; ++j)
				{
					cLigne.Format(_T("r:%d c:%d [ %7.5f]  \n"), i, j, m_listPtrMatrix_activation.at(0)->p[i][j]);
					m_listBox1.InsertString(-1, cLigne); ;
				};

				cLigne.Format(_T("\n "));

				m_listBox1.InsertString(-1, cLigne);
			};
		};


		Propagation();

		//CostFunction();
		m_display_erreur.Format(_T(" %15.13f    "), CostFunction());
		
		m_display_tour.Format(_T(" %d   "), tours);

		BackPropagation();

		UpdateData(FALSE);
		UpdateWindow();

	}; // fin: tour

}; // for btn clicked test



void CMFCMatrixAIAppDlg::saveToFileactivation_lossFunction()

{
	// ************************ Ecriture des activations vs target : pour analyse des resultats **************************
	CString cLigne;

	for (int neurone_j_destination = 0; neurone_j_destination < m_neuron_per_layer[m_number_layer - 1]; neurone_j_destination++)  //imprime dans un fichier pour analyse...
	{
		cLigne.Format(_T("activation finale:   %7.5f        vs  %7.5f             \t"), m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][neurone_j_destination], (m_double_outputArray_Y[neurone_j_destination]));
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

			if (z.p[i][j] < 0.0)
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


	if (m_listPtrMatrix_gradient.size() > 0)
	{
		

		for (level = 0; level < (m_number_layer); level++)
		{


			delete  m_listPtrMatrix_activation.at(level);
			delete  m_listPtrMatrix_gradient.at(level);
			delete  m_listPtrMatrix_weight.at(level);
			delete  m_listPtrMatrix_newWeight.at(level);
			delete  m_listPtrMatrix_bias.at(level);
			delete  m_listPtrMatrix_z.at(level);
			delete  m_listPtrMatrix_dCo_dBj.at(level);


		};

		m_listPtrMatrix_activation.clear();
		m_listPtrMatrix_gradient.clear();
		m_listPtrMatrix_weight.clear();
		m_listPtrMatrix_newWeight.clear();
		m_listPtrMatrix_bias.clear();
		m_listPtrMatrix_z.clear();
		m_listPtrMatrix_dCo_dBj.clear();
	};
	
};


void CMFCMatrixAIAppDlg::PrintMatrixToListBox(Matrix& myMatrix, int type)  //  type:  weight =0, bias =1, activation =2, Z=3, gradient = 4;
{
	
	CString cLigne;

	cLigne.Format(_T("  \t"));
	m_listBox1.InsertString(-1, cLigne);
	
	if (type == 0) cLigne.Format(_T(" Matrice W()  %d  x %d  \t"), myMatrix.rows_, myMatrix.cols_);
	if (type == 1) cLigne.Format(_T(" Matrice B()  %d  x %d  \t"), myMatrix.rows_, myMatrix.cols_);
	if (type == 2) cLigne.Format(_T(" Matrice A()  %d  x %d  \t"), myMatrix.rows_, myMatrix.cols_);
	if (type == 3) cLigne.Format(_T(" Matrice Z()  %d  x %d  \t"), myMatrix.rows_, myMatrix.cols_);
	if (type == 4) cLigne.Format(_T(" Matrice G()  %d  x %d  \t"), myMatrix.rows_, myMatrix.cols_);

	m_listBox1.InsertString(-1, cLigne);

	cLigne.Format(_T("  \t"));

	for (int i = 0; i < myMatrix.rows_; ++i)
	{

		for (int j = 0; j < myMatrix.cols_; ++j)
		{
			cLigne.Format(_T("r:%d c:%d [ %6.4f] "), i, j, myMatrix.p[i][j]);			// pour une rangee, affiche chaque colonne(col) de la matrice
			m_listBox1.InsertString(-1, cLigne);
		}

		cLigne.Format(_T("\n "));

		m_listBox1.InsertString(-1, cLigne);
	}


};

void CMFCMatrixAIAppDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
	cleanMemoryPointer();

	
	CDialogEx::OnOK();
}




void CMFCMatrixAIAppDlg::OnEnChangeTour()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMFCMatrixAIAppDlg::OnEnChangeErreur()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMFCMatrixAIAppDlg::OnBnClickedSauvematrices()
{
	// TODO: Add your control notification handler code here

	

	CFileDialog ldFile(TRUE);
	std::ifstream fsIn;
	CString cLigne,  rows, cols;
	std::string s_valeur, repertoire, fichier, str_nom_fichier;
	int level, row, col;

	

	std::ofstream outFile;

	if (ldFile.DoModal() == IDOK)
	{
		m_str_NOMFICHIEROUVERT = ldFile.GetFileName();
		m_str_NOMFICHIEROUVERT = m_str_NOMFICHIEROUVERT + L".txt";
		m_str_REPERTOIRE = ldFile.GetFolderPath();
		m_str_REPERTOIRE = m_str_REPERTOIRE + L"\\";

		std::string repertoire(CW2A(m_str_REPERTOIRE.GetString()));
		std::string fichier(CW2A(m_str_NOMFICHIEROUVERT.GetString()));

		fichier = repertoire + fichier; 
		
		outFile.open(fichier, std::ios::out);
	};

	//************imprime le nombre de couches ****************************
	
	//outFile << "nombre de couches: ";
	outFile << std::to_string(m_number_layer)+",";
	outFile << std::endl;

	//*************imprime le nombre de neurones par couche****************

	for (level = 0; level < (m_number_layer); level++)
	{

		//outFile << "Couche # " + std::to_string(level);
		//outFile << " # neurones:";
		outFile << std::to_string(m_listPtrMatrix_bias.at(level)->rows_)+",";					//utilise le nombre de bias pour compter le nombre de neurones (1 bias par neurone).
		

	};

	outFile << std::endl;

	

	
	
	
	for (level = 0; level < (m_number_layer); level++)
	{

		//outFile << std::endl;
		row = m_listPtrMatrix_bias.at(level)->rows_;
		//outFile << "Couche # " + std::to_string(level);
		//outFile << std::endl;

		//outFile << "matrice bias:";

		//***********imprime le bias pour la couche**************************

		for (int i = 0; i < row; ++i)				// niveau "0" de bias contient des valeurs dummy non utilisees. C'est le niveau des entrees : X(input).  Donc pas besoin de bias ici.
													// necessaire d'avoir un niveau "0" pour conserver la synchronisation de la numerotation des niveaux et des matrices.
			{
				
					
					outFile << std::to_string(m_listPtrMatrix_bias.at(level)->p[i][0]) + ",";
				
			};


			outFile << std::endl;
			
			row = m_listPtrMatrix_weight.at(level)->rows_;
			col = m_listPtrMatrix_weight.at(level)->cols_;

			//outFile << "matrice pondération:";
			//outFile << std::endl;

			//********imprime les ponderations pour la couche en cours **********

			for (int i = 0; i < row; ++i)			// niveau "0" de "bias"weight" contient des valeurs dummy non utilisees. C'est le niveau des entrees : X(input).  Donc pas besoin de ponderation ici.
													// necessaire d'avoir un niveau "0" pour conserver la synchronisation de la numerotation des niveaux et des matrices.
			{
				for (int j = 0; j < col; j++)
				{

					outFile << std::to_string(m_listPtrMatrix_weight.at(level)->p[i][j]) + ",";
					 
				};
				
				outFile << std::endl;
			};

			//outFile << std::endl;
	};

		outFile.close();

	UpdateData(FALSE);
}



void CMFCMatrixAIAppDlg::OnBnClickedButtonLireMatrices()
{
	// TODO: Add your control notification handler code here



	std::ifstream inFile;
	CFileDialog ldFile(TRUE);
	char buffer[500];
	
	m_strTraining_tours = "1";

	if (ldFile.DoModal() == IDOK)
	{
		m_str_NOMFICHIEROUVERT = ldFile.GetFileName();
		
		m_str_REPERTOIRE = ldFile.GetFolderPath();
		m_str_REPERTOIRE = m_str_REPERTOIRE + L"\\";

		std::string repertoire(CW2A(m_str_REPERTOIRE.GetString()));
		std::string fichier(CW2A(m_str_NOMFICHIEROUVERT.GetString()));

		fichier = repertoire + fichier;

		

		inFile.open(fichier, std::ifstream::in);
		
		
		inFile.getline(buffer, 300);
		scanner.setInput(buffer);
		scanner.ignoreWhitespace(FALSE);
		scanner.setSeparator(",");

		if (m_number_layer > 0) cleanMemoryPointer();					// efface la configuration precedente ici.

		m_number_layer = stod(scanner.firstToken());

		inFile.getline(buffer, 300);
		scanner.setInput(buffer);

		m_neuron_per_layer[0] = stod(scanner.firstToken());

		for (int layer = 1; layer < m_number_layer; layer++)
		{
			
			m_neuron_per_layer[layer] = stod(scanner.nextToken());

		};

		mStr_layer_1_neurons.Format(L"%d", m_neuron_per_layer[0]);    // met a jour les donnes affichees.
		mStr_layer_2_neurons.Format(L"%d", m_neuron_per_layer[1]);
		mStr_layer_3_neurons.Format(L"%d", m_neuron_per_layer[2]);
		mStr_layer_4_neurons.Format(L"%d", m_neuron_per_layer[3]);
		mStr_layer_5_neurons.Format(L"%d", m_neuron_per_layer[4]);

		UpdateData(FALSE);

		OnBnClickedCreateMatrix();

		for (int level = 0; level < (m_number_layer); level++)
		{


			//***********lire le bias pour la couche**************************

			inFile.getline(buffer, 300);
			scanner.setInput(buffer);
			scanner.ignoreWhitespace(FALSE);
			scanner.setSeparator(",");
			
			
			for (int i = 0; i < m_listPtrMatrix_bias.at(level)->rows_; ++i)				// niveau "0" de bias contient des valeurs dummy non utilisees. C'est le niveau des entrees : X(input).  Donc pas besoin de bias ici.
				// necessaire d'avoir un niveau "0" pour conserver la synchronisation de la numerotation des niveaux et des matrices.
			{

				if (i == 0) 
				{
					m_listPtrMatrix_bias.at(level)->p[i][0] = stod(scanner.firstToken());
				}
				
				else 
				{
					m_listPtrMatrix_bias.at(level)->p[i][0] = stod(scanner.nextToken());
				};

			};

			
			//********lire les ponderations pour la couche en cours **********

			scanner.ignoreWhitespace(FALSE);
			scanner.setSeparator(",");


			for (int i = 0; i < m_listPtrMatrix_weight.at(level)->rows_; ++i)			// niveau "0" de "bias"weight" contient des valeurs dummy non utilisees. C'est le niveau des entrees : X(input).  Donc pas besoin de ponderation ici.
													// necessaire d'avoir un niveau "0" pour conserver la synchronisation de la numerotation des niveaux et des matrices.
			{

				inFile.getline(buffer, 300);
				scanner.setInput(buffer);

				for (int j = 0; j < m_listPtrMatrix_weight.at(level)->cols_; j++)
				{

					if (j == 0) 
					{
						m_listPtrMatrix_weight.at(level)->p[i][j] = stod(scanner.firstToken());
					}
					else 
					{
						m_listPtrMatrix_weight.at(level)->p[i][j] = stod(scanner.nextToken());
					};

				};


			};

			
		};


	};

};
