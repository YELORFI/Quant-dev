#ifndef HestonPricer_H
#define HestonPricer_H
#include "HestonModel.h"
#include "Complex.h"
#include "GaussLegendreQuadrature.h"
#include <vector>
using Vector = std::vector<double>;
using Pair = std::pair<double, double>;
using PairVector = std::vector<Pair>;
class HestonPricer
{
public:
	HestonPricer(const HestonModel& model, const double& strike, const double& maturity);
	virtual HestonPricer* clone() const = 0;
	virtual double price() const = 0;


protected:
	HestonModel _model;
	double _strike;
	double _maturity;
};
#endif
