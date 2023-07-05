#include "AnalyticalHestonPricer.h"
#include "Complex.h"
#include "GaussLegendreQuadrature.h"
#include <cmath>
#include "HestonModel.h"
#include <iostream>
AnalyticalHestonPricer::AnalyticalHestonPricer(const HestonModel& model, const double& strike, const double& maturity,
    const size_t& gauss_legendre_sample_size)
    : HestonPricer(model, strike, maturity), _gauss_legendre_sample_size(gauss_legendre_sample_size) {}


 Complex AnalyticalHestonPricer::func_u(const size_t& i) const
{
    double u = (i == 1) ? -1. : 1.;
    return Complex(u,0.0);
}
Complex AnalyticalHestonPricer::func_y(const size_t& i, const double& omega) const
{
    double y_real = (i == 1) ? -1. : 0.;
    return Complex(y_real, omega);
}
Complex AnalyticalHestonPricer::func_a(const size_t& i, const double& omega) const
{

    Complex kappa(_model.mean_reversion_speed(),0.0);
    Complex rho(_model.correlation(),0.0);
    Complex sigma_v(_model.vol_of_vol(),0.0);
    Complex y = func_y(i, omega);
    return kappa - rho * sigma_v * y;
}
Complex AnalyticalHestonPricer::func_delta(const size_t& i, const double& omega) const
{
    Complex a = func_a(i, omega);
    Complex sigma_v(_model.vol_of_vol(),0.0);
    Complex u = func_u(i);
    Complex j(0., 1.);
    Complex omega_c(omega,0.0);
    return a * a + sigma_v * sigma_v * (u * j * omega_c + omega_c * omega_c);
}
Complex AnalyticalHestonPricer::func_b(const size_t& i, const double& omega) const
{
    return Complex::square_root(func_delta(i, omega));
}
Complex AnalyticalHestonPricer::func_g(const size_t& i, const double& omega) const
{
    Complex a = func_a(i, omega);

    Complex b = func_b(i, omega);
    return (a - b) / (a + b);
}
Complex AnalyticalHestonPricer::func_D(const size_t& i,
    const double& tau, const double& omega) const
{
    Complex tau_c(tau,0.0);
    Complex sigma_v(_model.vol_of_vol(),0.0);
    Complex a = func_a(i, omega);
    Complex b = func_b(i, omega);
    Complex g = func_g(i, omega);
    Complex res = (a - b) * (Complex(1.,0.0) - Complex::exponential(Complex(-1.,0.0) * b * tau_c))
        / (sigma_v * sigma_v * (Complex(1.,0.0) - g * Complex::exponential(Complex(-1.,0.0) * b * tau_c)));
    return res;
}
Complex AnalyticalHestonPricer::func_C(const size_t& i,
    const double& tau, const double& omega) const
{

    Complex kappa(_model.mean_reversion_speed(),0.0);
    Complex sigma_v(_model.vol_of_vol(),0.0);
    Complex tau_c(tau,0.0);
    Complex r(_model.drift(),0.0);
    Complex theta(_model.mean_reversion_level(),0.0);
    Complex a = func_a(i, omega);
    Complex b = func_b(i, omega);
    Complex g = func_g(i, omega);

    Complex res_1 = Complex(0, omega * tau * r.real_part()) ;


    Complex res = res_1 + (kappa * theta / (sigma_v * sigma_v)) * ((a - b) * tau_c) - Complex(2,0) * Complex::logarithm((Complex(1.,0) -g * Complex::exponential(Complex(-1.,0) * b * tau_c))
        / (Complex(1.,0.0) - g));

    return res;
}
Complex AnalyticalHestonPricer::func_Phi(const size_t& i, const double& tau, const double& x,
    const double& V, const double& omega) const
{

    Complex C = func_C(i, tau, omega);
    Complex D = func_D(i, tau, omega);

    Complex res = Complex::exponential(C + D * Complex(V,0) + Complex(0, omega * x) );
    return res;

}

double AnalyticalHestonPricer::func_integrand(const size_t& i, const double& tau, const double&
    x, const double& V, const double& omega)const

{
    Complex Phi = func_Phi(i, tau, x, V, omega);


    Complex res = Phi * Complex::exponential(Complex(0.0,-omega * std::log(_strike))  / (Complex(0.0, omega)));

    return res.real_part();
}

double AnalyticalHestonPricer::func_P(const size_t& i,
    const double& tau, const double& x, const double& V) const
{
    GaussLegendreQuadrature glq(_gauss_legendre_sample_size);
    std::function<double(double)> func =
        [this, i, tau, x, V](double omega) {return func_integrand(i, tau, x, V, omega); };
    double integral = glq.integrate(func);
    const double Pi = std::acos(-1.0);
    return 0.5 * (1. + integral / Pi);
}

double AnalyticalHestonPricer::price() const 
{
    double s0 = _model.initial_spot();
    double v0 = _model.initial_variance();
    AnalyticalHestonPricer analyticalPricer(_model, _strike, _maturity, 100); // Crée une instance d'AnalyticalHestonPricer

    double P1 = analyticalPricer.func_P(1, _maturity, std::log(s0), v0);
    double P2 = analyticalPricer.func_P(2, _maturity, std::log(s0), v0);
    double res = s0 * P1 - _strike * std::exp(-_model.drift() * _maturity) * P2;;
    double res = _strike * std::exp(-_model.drift() * _maturity) * P2 - s0 * P1;

    std::cout << "Le prix calcule de l'option est : " << s0 * P1 << std::endl;
    std::cout << "Le prix calcule de l'option est : " << _strike * std::exp(-_model.drift() * _maturity) * P2 << std::endl;
    return res;
}

AnalyticalHestonPricer* AnalyticalHestonPricer::clone() const
{
    return new AnalyticalHestonPricer(*this);
}


