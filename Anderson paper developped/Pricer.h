#pragma once
#include "Payoff.h"
#include "PathSimulator.h"


// Monte Carlo way of computing the Price of options in a Model
class MonteCarloPricer 
{
protected:
	PathSimulator* _path;// The simulation scheme choosed
	PayOff* _payoff;// the option Payoff
	double _maturity;// the maturity of the option
	int _number_of_simulations;
	Vector _equity; //Vector containing  the evolution of the derivative 

public:
	MonteCarloPricer(const PathSimulator& path, const PayOff& payoff, const double& maturity, const size_t& number_of_simulations, const Vector& equity);
	MonteCarloPricer* clone() const;
	MonteCarloPricer(const MonteCarloPricer& pricer);
	MonteCarloPricer& operator=(const MonteCarloPricer& pricer);
	double price() const;
	~MonteCarloPricer();

};


