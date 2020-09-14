
// MFC_Matrix_AI_AppDlg.h : header file
//

#include <list>
#include "matrix.h"
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <bitset>
#include <array>
#pragma once


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
	afx_msg void OnEnChangeEdit1();

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


	int m_neuron_per_layer[10] = { 0 };

	void multiplicationMatrice(Matrix&, Matrix&, Matrix&, int n);
	void additionMatrice(Matrix&, Matrix&, int n);
	void sigmoidMatrice(Matrix&, int n);
	void initialiseActivationNiveauSuivant(Matrix&, Matrix&, int n);

	struct sampleStructure
	{
		int numberOfSample;			// nombre d'échantillons dans le fichier
		int inputSampleBitSize;				// nombre de bits par échantillon.  On suppose que les valeurs des inputs sont 0 ou 1.  Une autre version sera requise pour des valeurs de 0.0  à 1.0 (nombre réel).
		int outputSampleBitSize;
	};

	struct sample
	{
		int input;
		int output;
	};

	sampleStructure m_structureTestEcriture;

	CListBox m_listBox1;
	afx_msg void OnBnClickedCreatetestinput();
	afx_msg void OnBnClickedTest();
	afx_msg void OnBnClickedOpentrainingdata();

	int GetNextSampleInput(int theSampleNumber);
	int GetNextSampleOutput(int theSampleNumber);



	std::array<int,10> ConvertNextSampleToBinary(int sampleInputDecimal);

	CString m_TrainingDataFile;
	CString m_str_SampleSize;
	CString m_str_NeuronPerSampleInput;
	CString m_str_TrainingTours;
	std::vector<sample> m_samples_vector;
	float m_fCostFunctionError;

};
