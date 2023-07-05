#include "Payoff.h"
#include "PathSimulator.h"

#include <cmath>

MonteCarloPricer::MonteCarloPricer(const PathSimulator& path, const PayOff& payoff, const double& maturity, const size_t& number_of_simulations,const Vector& equity)
	:_path(path.clone()),_payoff(payoff.clone()),_maturity(maturity), _number_of_simulations(number_of_simulations),_equity(equity)
{
}

MonteCarloPricer* MonteCarloPricer::clone() const
{
	return new MonteCarloPricer(*this);
}

MonteCarloPricer::MonteCarloPricer(const MonteCarloPricer& pricer)
	:_path(pricer._path->clone()), _number_of_simulations(pricer._number_of_simulations),_payoff(pricer._payoff->clone()),_maturity(pricer._maturity),_equity(pricer._equity)
{
}

MonteCarloPricer& MonteCarloPricer::operator=(const MonteCarloPricer& pricer)
{
	if (this != &pricer)
	{
		this->_path = pricer._path->clone();
		this->_payoff = pricer._payoff->clone();
		this->_maturity = pricer._maturity;
		this->_number_of_simulations = pricer._number_of_simulations;
		this->_equity = pricer._equity;
}
	return *this;
}

MonteCarloPricer::~MonteCarloPricer()
{
	delete _path;
	delete _payoff;
}



double MonteCarloPricer::price() const
{
	double S = 0;
	PathSimulator* PATH=_path;

		for (size_t i = 0; i < _number_of_simulations; i++)
	{
		S = S + (*_payoff)(_equity) * (exp(PATH->get_model()->risk_free_rate() * _maturity));
		/* original coda
				s=s+(*_payoff)(_path->path_maturity(_maturity).first)*exp(-_path->get_model()->risk_free_rate() * _maturity);
	*/
	}
	return S / _number_of_simulations;
}



