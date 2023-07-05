#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H



class Complex {
public:
	Complex(const double& real, const double& imaginary) : _real(real), _imaginary(imaginary) {}; // constructeur
	double real_part() const; // getter
	double imaginary_part() const; // getter
	Complex operator+(const Complex& complex) const; //somme
	Complex operator-(const Complex& complex) const; // réduction
	Complex operator*(const Complex& complex) const; // multiplication	
	Complex operator/(const Complex& complex) const; // division
	static Complex exponential(const Complex& complex); //exponentiel
	static Complex logarithm(const Complex& complex); // logarithme
	static Complex square_root(const Complex& complex); // racine carré
protected:
	bool isZero() const; // verifier si le nombre est nul
	double module() const; // calculer le module 
	double argument() const; // calculer l'argument
	double _real; //partie reel
	double _imaginary; // partie imaginaire
};
#endif




