#include "GAUSSLEGENDREQUADRATURE.h"
#include <cmath>

using Vector = std::vector<double>;

// définition du constructeur par liste d'initialisation en définnisant les points et les poids
GaussLegendreQuadrature::GaussLegendreQuadrature(const size_t& number_sample_points)
	: _number_sample_points(number_sample_points)
{
	// Resize the weights and points vectors
	_weights.resize(number_sample_points);
	_points.resize(number_sample_points);

	// utilisation des poids comme ils sont définis dans l'examen 2021/2022
	for (size_t i = 0; i < number_sample_points; i++)
	{
		double x = -1.0 + (2.0 * i / (number_sample_points - 1));
		double w = x / ((1 - x) * (1 - x));
		_points[i] = x;
		_weights[i] = w;
	}
}


double GaussLegendreQuadrature::integrate(std::function<double(double)> func) const
{
	double integral = 0.;
	for (size_t idx = 1; idx < _number_sample_points-1; ++idx)
	{
		double xi = _points[idx];
		double wi = _weights[idx];
		double x = xi / (1 - xi * xi); // définition des fonctions comme ils sont définis dans l'examen 2021/2022
		double fx = func(x);
		double gx = fx * ((1 + xi * xi) / std::pow((1 - xi * xi), 2));
		integral += wi * gx;
	}

	return integral;
}