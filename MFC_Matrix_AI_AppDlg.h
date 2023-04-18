
// MFC_Matrix_AI_AppDlg.h : header file
//

#include <list>
#include "matrix.h"
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <bitset>
#include <array>
#include <atlstr.h>
#include <exception>
#include <thread>

#include <math.h>
#include <random>
#include <time.h>
#include "tokenscanner.h"

#pragma once

using namespace std;

// CMFCMatrixAIAppDlg dialog
class CMFCMatrixAIAppDlg : public CDialogEx
{
	// Construction
public:
	CMFCMatrixAIAppDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_MATRIX_AI_APP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreateMatrix();
	
	int m_number_layer = 0;
	CString mStr_layer_1_neurons;
	CString mStr_layer_2_neurons;
	CString mStr_layer_3_neurons;
	CString mStr_layer_4_neurons;
	CString mStr_layer_5_neurons;

	CString m_str_NOMFICHIEROUVERT;
	CString m_str_REPERTOIRE;

	std::vector<Matrix*> m_listPtrMatrix_weight;
	std::vector<Matrix*> m_listPtrMatrix_bias;
	std::vector<Matrix*> m_listPtrMatrix_z;
	std::vector<Matrix*> m_listPtrMatrix_activation;
	std::vector<Matrix*> m_listPtrMatrix_newWeight;
	std::vector<Matrix*> m_listPtrMatrix_gradient;
	std::vector<Matrix*> m_listPtrMatrix_dCo_dBj;				

	TokenScanner scanner;

	int m_neuron_per_layer[100] = { 0 };

	void multiplicationMatrice(Matrix&, Matrix&, Matrix&, int n);
	void copieMatrice(Matrix& source, Matrix& destination);
	void additionMatrice(Matrix&, Matrix&, int n);
	void sigmoidMatrice(Matrix&, int n);
	void RELU(Matrix&, int n);
	void activation(Matrix&, Matrix&, int n);
	void imprimeMatrices();
	void saveToFileactivation_lossFunction();
	void cleanMemoryPointer();
	void PrintMatrixToListBox(Matrix& myMatrix, int type);
	void Propagation();
	void BackPropagation();
	double CostFunction();
	void CreateInputTest();
	void CreateOutputTest();

	int weightType = 0, biasType = 1, activationType =2, zType =3, gradientType = 4;

	double calcul_erreur_cumul_L_minus_1(int neuron);				// calcule l'erreur cumulative pour un neuron de la couche L-1 (utilisé lors du backpropagation)
	struct sampleStructure
	{
		int numberOfSample;											// nombre d'échantillons dans le fichier
		int inputSampleBitSize;										// nombre de bits par échantillon.  On suppose que les valeurs des inputs sont 0 ou 1.  Une autre version sera requise pour des valeurs de 0.0  à 1.0 (nombre réel).
		int outputSampleBitSize;
	};

	struct sample
	{
		int input;
		int output;
	};

	sampleStructure m_structureTestEcriture;

	CListBox m_listBox1;
	CListBox m_listbox_cost_function;

	afx_msg void OnBnClickedCreatetestinput();
	afx_msg void OnBnClickedTest();
	afx_msg void OnBnClickedOpentrainingdata();

	int GetNextSampleInput(int theSampleNumber);
	int GetNextSampleOutput(int theSampleNumber);

	std::ofstream fileOutputStream;

	std::array<int,10> ConvertNextSampleToBinary(int sampleInputDecimal);

	CString m_TrainingDataFile;
	CString m_outputDataFile;
	CString m_str_SampleSize;
	CString m_str_NeuronPerSampleInput;

	std::vector<sample> m_samples_vector;
	double m_fCostFunctionError;
	double learning_rate=0.1;
	std::array<double, 100> m_double_inputArray_X, m_double_outputArray_Y;

	
	CString m_strTraining_tours;


	CString m_str_learning_rate;
	CString m_display_tour;
	CString m_display_erreur;
	BOOL m_bool_verbose;
	CString m_CStr_activation_choice;
	//afx_msg void OnLbnDblclkactivationChoice();
	
	CComboBox m_comboListBox_activation;
	CString m_str_activationSelection;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeTour();
	afx_msg void OnEnChangeErreur();
	afx_msg void OnBnClickedSauvematrices();
	afx_msg void OnBnClickedButtonLireMatrices();


	BOOL m_bool_verb_activation;
};
