#ifndef BnS_H
#define BnS_H
// Gives the price of the vanilla option with the Black Scholes formula
double BlackScholesCallvanilla(double Spot,double Strike,double r,double d,double Vol,double Expiry);
// Gives the Vega of the vanilla option with the Black Scholes formula
double BlackScholesCallvanillaVega(double Spot, double Strike, double r, double d, double Vol, double Expiry);
// Gives the price of the forward starting option with the Black Scholes formula
double BlackScholesCallforward(double Spot, double Strike, double r, double d, double Vol, double Expiry,double start_time,double proportion);
// Gives the Vega of the forward starting option with the Black Scholes formula
double BlackScholesCallforwardVega(double Spot, double Strike, double r, double d, double Vol, double Expiry,double start_time,double proportion);
#endif