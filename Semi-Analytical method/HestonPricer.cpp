
#include "HestonModel.h"
#include "Complex.h"
#include "GaussLegendreQuadrature.h"
#include <vector>
#include "AnalyticalHestonPricer.h"
#include <cmath>



HestonPricer::HestonPricer(const HestonModel& model, const double& strike, const double& maturity)
	: _model(model), _strike(strike), _maturity(maturity)
{
	// Initialisations spécifiques au constructeur de HestonPricer
}


