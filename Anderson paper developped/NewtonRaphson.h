#pragma once
#include <cmath>
//using template class to re use the methode for generic variables ( little help with chatgbt)
template<class T, double (T::* Value)(double) const,double (T::* Derivative)(double) const >
	double NewtonRaphson(double Target,double Start,double Tolerance,const T& TheObject)
{
	double y = (TheObject.*Value)(Start);
	double x = Start;
	while (abs(y - Target) > Tolerance)
	{
		double d = (TheObject.*Derivative)(x);
		x += (Target - y) / d;
		y = (TheObject.*Value)(x);
	}
	return x;
}
