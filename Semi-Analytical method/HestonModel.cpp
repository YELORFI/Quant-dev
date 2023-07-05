
#include "HestonModel.h"


HestonModel::HestonModel(  // d�finition du construteur par liste d'initialisation
    const double& initial_spot,
    const double& initial_variance,
    const double& drift,
    const double& mean_reversion_speed,
    const double& mean_reversion_level,
    const double& vol_of_vol,
    const double& correlation)
    : _initial_spot(initial_spot),
    _initial_variance(initial_variance),
    _drift(drift),
    _mean_reversion_speed(mean_reversion_speed),
    _mean_reversion_level(mean_reversion_level),
    _vol_of_vol(vol_of_vol),
    _correlation(correlation)
{
    
}


// d�finition des getters

double HestonModel::initial_spot() const
{
    return _initial_spot;
}

double HestonModel::initial_variance() const
{
    return _initial_variance;
}

double HestonModel::drift() const
{
    return _drift;
}

double HestonModel::mean_reversion_speed() const
{
    return _mean_reversion_speed;
}

double HestonModel::mean_reversion_level() const
{
    return _mean_reversion_level;
}

double HestonModel::vol_of_vol() const
{
    return _vol_of_vol;
}

double HestonModel::correlation() const
{
    return _correlation;
}

