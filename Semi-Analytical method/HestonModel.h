#pragma once
#ifndef HestonModel_H
#define HestonModel_H



class HestonModel
{
public:
	HestonModel(
		const double& initial_spot,
		const double& initial_variance,
		const double& drift,
		const double& mean_reversion_speed,
		const double& mean_reversion_level,
		const double& vol_of_vol,
		const double& correlation);
	// getter methods
	double initial_spot() const;
	double initial_variance() const;
	double drift() const;
	double mean_reversion_speed() const;
	double mean_reversion_level() const;
	double vol_of_vol() const;
	double correlation() const;
private:
	double _initial_spot; // S_0
	double _initial_variance; // V_0
	double _drift; // rate r
	double _mean_reversion_speed; // kappa
	double _mean_reversion_level; // theta
	double _vol_of_vol; // sigma_V
	double _correlation; // rho
};
#endif