#pragma once
// random generator by Box-Muller 
double Gausienne();
    
//Needed for the inverse of normal cumulative distribution function
double RationalApproximation(double t);

//Inverse of normal cumulative distribution function
double NormalCDFInverse(double p);

//Normal cumulative distribution function
double NormalCDF(double k);
