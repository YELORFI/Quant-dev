#include "Complex.h"
#include <cmath>

double Complex::real_part() const // getter pour retrouver la partie reel 
{
	return _real;
}
double Complex::imaginary_part() const // getter pour retrouver la partie imaginaire 
{
	return _imaginary;
}

bool Complex::isZero() const {  // methode de verification si le nombre complexe est nul
	return (_real == 0.0 && _imaginary == 0.0);
}


double Complex::module() const { // methode pour calculer le module
	return std::sqrt(_real * _real + _imaginary * _imaginary);
}


double Complex::argument() const { // methode pour calculer l'argument
	if (isZero()) {
		// Gérer le cas où le nombre complexe est nul
		return 0.0; 
	}
	else {
		// Calculer l'argument du nombre complexe non nul
		return std::atan2(_imaginary, _real);
	}
}


Complex Complex::operator+(const Complex& complex) const { // operation de la somme pour les nombres complexes
	return Complex(_real + complex._real, _imaginary + complex._imaginary);
}

Complex Complex::operator-(const Complex& complex) const { // operation de la réduction pour les nombres complexes
	return Complex(_real - complex._real, _imaginary - complex._imaginary);
}

Complex Complex::operator*(const Complex& complex) const { // operation de la multiplication pour les nombres complexes
	double real = _real * complex._real - _imaginary * complex._imaginary;
	double imaginary = _real * complex._imaginary + _imaginary * complex._real;
	return Complex(real, imaginary);
}

Complex Complex::operator/(const Complex& complex) const { // operation de la division pour les nombres complexes
	double denominator = complex._real * complex._real + complex._imaginary * complex._imaginary;
	if (denominator == 0.0) { // Gérer le cas où le dénominateur est nul
		throw "Cannot divide by zero";
	}
	double real = (_real * complex._real + _imaginary * complex._imaginary) / denominator;
	double imaginary = (_imaginary * complex._real - _real * complex._imaginary) / denominator;
	return Complex(real, imaginary);
}


 Complex Complex::exponential(const Complex& complex) { // définition de l'exponentiel complexe
	double real = std::exp(complex._real) * std::cos(complex._imaginary);
	double imaginary = std::exp(complex._real) * std::sin(complex._imaginary);
	return Complex(real, imaginary);
}

 Complex Complex::logarithm(const Complex& complex) { // définition du logarithme complexe
	if (complex.isZero()) { // Gérer le cas où le nombre complexe est nul
		throw "Cannot compute logarithm of zero";
	}

	double modulus = complex.module();
	double argument = complex.argument();

	return Complex(std::log(modulus), argument);
}



 Complex Complex::square_root(const Complex& complex) { // définition de la racine d'un nombre complexe
	if (complex.isZero()) { // Gérer le cas où le nombre complexe est nul
		return Complex(0.0, 0.0); // Racine carrée de zéro est zéro
	}

	double modulus = complex.module();
	double argument = complex.argument();

	double sqrtModulus = std::sqrt(modulus);
	double sqrtArgument = argument / 2.0;

	double real = sqrtModulus * std::cos(sqrtArgument);
	double imaginary = sqrtModulus * std::sin(sqrtArgument);

	return Complex(real, imaginary);
}
