#include "network.h"
#include <random>


float sigmoid(float z)
{
	float result;
	result = exp(-z);
	
	return 1.0 / (1.0 + result);
};

float sigmoid_prime(float z)
{
	float temp = sigmoid(z);
	return temp * (1 - temp);

};

void init_bias_and_weight()
{
	// genere une distribution normal de nombre aleatoire.  parametres:  "distribution(moyenne, deviation_standard)"

	std::default_random_engine generator;
	std::normal_distribution<float> distribution(0.0, 1.0);

	//Reste a ajouter code pour initialiser les "weights" et "bias"

};

