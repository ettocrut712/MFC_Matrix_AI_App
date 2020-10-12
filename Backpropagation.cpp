
/*double CMFCMatrixAIAppDlg::calcul_erreur_cumul_L_minus_1(int neuron_source)
{
	//fait la somme des erreurs pour le "neuron" de la couche L-1 (utilisé pour backpropagation de la couche L-1 et précédentes)

	double erreur_cumulative = 0.0;
	double temp = 0.0;
	int neuron_terminaison;

	for (neuron_terminaison = 0; neuron_terminaison < m_neuron_per_layer[m_number_layer - 1]; neuron_terminaison++)   // m_number_layer -1 = couche "L", la derniere couche avant la sortie.
	{

		temp = (m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][neuron_terminaison] - m_double_outputArray_Y[neuron_terminaison]);  //calcule l'erreur entre la valeur obtenue (...activation...) 
		temp = temp * (m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][neuron_terminaison]) * ((1 - m_listPtrMatrix_activation.at(m_number_layer - 1)->p[0][neuron_terminaison]));
		temp = temp * m_listPtrMatrix_weight.at(m_number_layer - 1)->p[neuron_source][neuron_terminaison];
		//et la valeur attendue (m_double_outputArray_Y)
		erreur_cumulative = erreur_cumulative + temp;



	};




	return erreur_cumulative;


};*/

int layer = 0;

/*std::array<double, 20> m_array_error_jth_Neuron_L_Layer;																	
																															// Calcul des erreurs pour les neurones de la couche "L-1"
for (neuron_destination = 0; neuron_destination < m_neuron_per_layer[layer]; neuron_destination++)
{
	m_array_error_jth_Neuron_L_Layer[neuron_destination] = calcul_erreur_cumul_L_minus_1(neuron_destination);
};*/

for (layer = m_number_layer - 1; layer > 0; layer--)																		// layer > 0 parce que layer=0 ce sont les données d'entrée.  Donc pas de calcul à faire pour cette couche. 
{

	//initialise le vecteur gradient pour L-1

	for (neuron_L_source = 0; neuron_L_source < m_neuron_per_layer[layer - 1]; neuron_L_source++)
	{
		m_listPtrMatrix_gradient.at(layer - 1)->p[0][neuron_L_source] = 0.0;
	};

	for (neuron_L_destination = 0; neuron_L_destination < m_neuron_per_layer[layer]; neuron_L_destination++)
																															
	{
							

		if (layer = m_number_layer - 1)																						// couche = layer "0" ou L0 = sortie
		{
			activation_x_L0 = m_listPtrMatrix_activation.at(layer)->p[0][neuron_L_destination];
			error_jth_Neuron_L_Layer = (activation_x_L0 - m_double_outputArray_Y[neuron_L_destination]) * activation_x_L0 * (1 - activation_x_L0);
		}

		else
		{
			error_jth_Neuron_L_Layer = m_listPtrMatrix_gradient.at(layer)->p[0][neuron_L_destination];
			//error_jth_Neuron_L_Layer = m_array_error_jth_Neuron_L_Layer[neuron_destination];
		};


		for (neuron_L_source = 0; neuron_L_source < m_neuron_per_layer[layer-1]; neuron_L_source++)							// Nombre de neurones dans la couche précédente: "L minus one"
		{
			bias_x = m_listPtrMatrix_bias.at(layer)->p[0][neuron_L_destination];											// Lecture de la valeur du bias B(L) avant modification. Le bias n'a pas de source.  Source = 0;

			weight_x = m_listPtrMatrix_weight.at(layer)->p[neuron_L_source][neuron_L_destination];							// Lecture de la valeur de la ponderation W(L), avant modification
						
			activation_x_Lminus = m_listPtrMatrix_activation.at(layer -1)->p[0][neuron_L_source];							// Lecture de l'activation A(layer-1)

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

				cLigne.Format(_T("delta*outH1:   %7.5f  \t"), error_jth_Neuron_L_Layer * activation_x_L0);
				m_listbox_cost_function.InsertString(-1, cLigne);


			};


			//CALCUL des nouvelles PONDERATION *****************
			
			
			 
				m_listPtrMatrix_newWeight.at(layer)->p[neuron_L_source][neuron_L_destination] = weight_x - learning_rate * error_jth_Neuron_L_Layer * activation_x_Lminus; 
				m_listPtrMatrix_newBias.at(layer)->p[0][neuron_L_destination]  = bias_x   - learning_rate * error_jth_Neuron_L_Layer;
				m_listPtrMatrix_gradient.at(layer-1)->p[0][neuron_L_source] = m_listPtrMatrix_gradient.at(layer - 1)->p[0][neuron_L_source] + error_jth_Neuron_L_Layer * weight_x;			//Sommation des dEdA(L-1) sur le neurone source.
			

			
			


			

			if (m_bool_verbose)
			{
				cLigne.Format(_T("B(%d-%d):   %7.5f  \t"), 0, neuron_L_destination, m_listPtrMatrix_newBias.at(layer)->p[0][neuron_L_destination]);
				m_listbox_cost_function.InsertString(-1, cLigne);
			};

		};
	};

};

