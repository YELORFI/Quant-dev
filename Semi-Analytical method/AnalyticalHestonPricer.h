#ifndef ANALYTICALHESTONPRICER_H
#define ANALYTICALHESTONPRICER_H

#include "HESTONPRICER.h"
class AnalyticalHestonPricer : public HestonPricer
{
public:
	AnalyticalHestonPricer(const HestonModel& model,
		const double& strike,
		const double& maturity,
		const size_t& gauss_legendre_sample_size);
	AnalyticalHestonPricer* clone() const override;
	double price() const override;
public:
	Complex func_u(const size_t& i) const;
	Complex func_y(const size_t& i, const double& omega) const;
	Complex func_a(const size_t& i, const double& omega) const;
	Complex func_delta(const size_t& i, const double& omega) const;
	Complex func_b(const size_t& i, const double& omega) const;
	Complex func_g(const size_t& i, const double& omega) const;
	Complex func_C(const size_t& i, const double& tau, const double& omega) const;
	Complex func_D(const size_t& i, const double& tau, const double& omega) const;
	Complex func_Phi(const size_t& i, const double& tau,
		const double& x, const double& V, const double& omega) const;
	double func_integrand(const size_t& i, const double& tau, const double& x,
		const double& V, const double& omega) const;
	double func_P(const size_t& i, const double& tau, const double& x, const double& V) const;
	size_t _gauss_legendre_sample_size;
	
};
#pragma once
#endif