#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>

using namespace std;
using Vector = std::vector<double>;

//Main reason here is to learn how to calibrate models using MLE, never got time to work all the details, all is missing is the optimization algorithm

// Function to calculate the log-likelihood of the Heston model
double calculateLogLikelihood(const Vector& observedData, const Vector& modelData)
{
    assert(observedData.size() == modelData.size());

    double logLikelihood = 0.0;
    for (size_t i = 0; i < observedData.size(); ++i) {
        logLikelihood += -0.5 * log(2 * M_PI) - 0.5 * log(modelData[i]) -
            0.5 * pow((observedData[i] - modelData[i]), 2) / modelData[i];
    }

    return logLikelihood;
}

// Function to calibrate the Heston model using maximum likelihood
void calibrateHestonModel(const Vector& observedData)
{
    // Initialize the parameters with some initial values
    double initialParam1 = 0.5;  // Replace with appropriate initial values
    double initialParam2 = 0.05;
    // ...

    // Set up the optimization algorithm (the Newton-Raphson algorithm)
    double epsilon = 1e-6;
    double param1 = initialParam1;
    double param2 = initialParam2;
    // kappa theta rho

    double prevLogLikelihood = -numeric_limits<double>::infinity();
    double currLogLikelihood = 0.0;
    
    // Perform the optimization until convergence(>1e-6)
    while (abs(currLogLikelihood - prevLogLikelihood) > epsilon) {
        // Compute the model data using the current parameter values
        Vector modelData; // Implement the calculation of model data using current parameters

        // Calculate the log-likelihood of the model
        currLogLikelihood = calculateLogLikelihood(observedData, modelData);

        // Update the parameter values using the optimization algorithm (e.g., Newton-Raphson)
        // ...

        // Update the previous log-likelihood value
        prevLogLikelihood = currLogLikelihood;
    }

    // Output the calibrated parameter values
    std::cout << "Calibrated Parameter 1: " << param1 << std::endl;
    std::cout << "Calibrated Parameter 2: " << param2 << std::endl;
    // ...
}
/*
int main()
{
    // Load observed data from a file or generate synthetic data
    std::Vector observedData; // Replace with your observed data

    // Call the calibration function
    calibrateHestonModel(observedData);

    return 0;
}*/
