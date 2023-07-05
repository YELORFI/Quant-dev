#ifndef GAUSSLEGENDREQUADRATURE_H
#define GAUSSLEGENDREQUADRATURE_H
#include <vector>
#include <functional>



using Vector = std::vector<double>;
class GaussLegendreQuadrature
{
public:
	GaussLegendreQuadrature(const size_t& number_sample_points);
	// Integration of f over the real interval ]- infinity, + infinity[
	double integrate(std::function<double(double)> func) const;
private:
	size_t _number_sample_points;
	// Those data members are constructed in the constructor
	Vector _weights; // (w_i)
	Vector _points; // (x_i)
};
#endif




