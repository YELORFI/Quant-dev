#pragma once
#include "Models.h"
#include <random>
#include <chrono>

// Designed class for simulating the models
class PathSimulator
{
public:
	virtual PathSimulator* clone() const = 0;
	PathSimulator(const Model_with_vol& model, const Vector time_points);
	PathSimulator(const PathSimulator& path_simulator);
	PathSimulator& operator=(const PathSimulator& path_simulator);
	
	virtual ~PathSimulator();	
	Pair path_maturity();		
	Model_with_vol *get_model();
	size_t index_maturity() const;

	virtual Pair next_step(const size_t& time_idx, const Pair& spot_variance, vector<Pair>& spot_variance_sample) const = 0;
	
protected:
	// Model to simulate
	Model_with_vol* model;
	// Time's points discretization
	Vector _time_points; // [t_0 = 0, t_1, ..., t_M]
};

// Euler's scheme for discretization
class PathSimulatorEuler : public PathSimulator
{
public:
	PathSimulatorEuler* clone() const override;
	PathSimulatorEuler(const Heston_local_sto_vol_Model& model, const Vector time_points);
	Pair next_step(const size_t& time_idx, const Pair& spot_variance, vector<Pair>& spot_variance_sample) const override;
};


// Milstein's scheme for discretization
class PathSimulatorMilstein : public PathSimulator
{
public:
	PathSimulatorMilstein* clone() const override;
	PathSimulatorMilstein(const Heston_local_sto_vol_Model& model, const Vector time_points);
	Pair next_step(const size_t& time_idx, const Pair& spot_variance, vector<Pair>& spot_variance_sample) const override;
};



//Scheme QE for discretization
class PathSimulatorQE : public PathSimulator
{
public:
	PathSimulatorQE* clone() const override;
	PathSimulatorQE(const Model_with_vol& model, const Vector time_points);
	Pair next_step(const size_t& time_idx, const Pair& spot_variance, vector<Pair>& spot_variance_sample) const override;
};










