#include <functional>
#include <cmath>
#include <vector>
#include "AnalyticalHestonPricer.h"
#include "HestonModel.h"
#include <iostream>

int main()
{
    // Création d'un objet HestonModel avec des valeurs de test
    double initial_spot = 100.0;
    double initial_variance = 0.05;
    double drift = 0.05;
    double mean_reversion_speed = 1.0;
    double mean_reversion_level = 0.04;
    double vol_of_vol = 0.2;
    double correlation = -0.5;

    HestonModel model(initial_spot, initial_variance, drift, mean_reversion_speed, mean_reversion_level, vol_of_vol, correlation);

    // Création d'un AnalyticalHestonPricer avec le modèle créé
    double strike = 95.0;
    double maturity = 1.0;
    size_t gauss_legendre_sample_size = 10000;

    AnalyticalHestonPricer pricer(model, strike, maturity, gauss_legendre_sample_size);

    // Calcul du prix en utilisant la méthode price()
    double price = pricer.price();

    // Affichage du prix calculé
    std::cout << "Le prix calculé est : " << price << std::endl;

    return 0;
}