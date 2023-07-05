
#include "Payoff.h"
#include "math.h"

PayOff::PayOff(const double& strike) 
	: _strike(strike)
{
}
double PayOff::strike()
{
	return _strike;
}
PayOffCall::PayOffCall(const double& strike) 
	: PayOff(strike)
{
}
double PayOffCall::operator()(const Vector& Spot) const
{
	return max(Spot[0] - _strike, 0.0);
}

PayOffCall* PayOffCall::clone() const
{
	return new PayOffCall(*this);
}

PayOffPut::PayOffPut(const double& strike): PayOff(strike)
{
}


double PayOffPut::operator()(const Vector& Spot) const
{
	return max(_strike - Spot[0], 0.0);
}

PayOffPut* PayOffPut::clone() const
{
	return new PayOffPut(*this);
}

