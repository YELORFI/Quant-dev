#include <iostream>
#include "Bins.h"
#include "BnS.h" 
#include "BoxMuller.h"
#include "NewtonRaphson.h"
#include "Models.h"
#include "PathSimulator.h"
#include "DupireLocalVolatilitySurface.h"
#include "ImpliedVolatilitySurface.h"
#include "Payoff.h"
#include "Pricer.h" 
#include "ThomasSolver.h" 

//Brute force include implementation files, Vscode won't do it automatically(do better)
#include "Bins.cpp"
#include "BnS.cpp" 
#include "BoxMuller.cpp"
#include "Models.cpp"
#include "PathSimulator.cpp"
#include "DupireLocalVolatilitySurface.cpp"
#include "ImpliedVolatilitySurface.cpp"
#include "Payoff.cpp"
#include "Pricer.cpp"
#include "ThomasSolver.cpp" 
using namespace std;
using Vector = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;

int main()
{
    /*FILE *file, *f;
    if ((file = fopen("C:\\Users\\Yassir EL-ORFI\\Downloads\\draft 2\\draft 2\\0Data.csv" ,"w"))== NULL)
    {fprintf(stderr, "Cannot open input file.\n");
    return 1; }*/

    BsCallvanilla Call(0, 0, 10, 100, 100); 
    /*
    0,                  Rate
    0,                  Dividende
    10,                 Maturity
    100,                Spot
    100                 Strike
    */
    double vol = NewtonRaphson<BSCall, &BSCall::Price, &BSCall::Vega>(21.71805807260404, 0.5, 0.1, Call);
    /*
    21.71805807260404,  Initial guess, 
    0.5,                Start
    0.1,                Tolerance(precision)
    Call,               The object( Template T in this case is BscallVanilla)
    
    */
    cout << vol << " - vola" << endl;
    double Price = BlackScholesCallvanilla(100, 100, 0, 0, vol,10);
    cout << Price << " - BScall" << endl;


    /*outs 
    0.175149 - vola
    21.817 - BScall
    */



    srand(clock());
    Pair init_spot_variance(100, 0.0945);   //init spot
    equal_number b(100,5);                  //bins
    Vector s(9);                    // spots
    Vector t(8);                    //time (scheme)
    Matrix sigma(8, Vector(9));     //matrix volatiliteis
    s[0] = 20; s[1] = 40; s[2] = 60; s[3] = 80; s[4] = 100; s[5] = 120; s[6] = 140; s[7] = 160; s[8] = 180;
    t[0] = 0.25; t[1] = 0.5; t[2] = 0.75; t[3] = 1; t[4] = 2; t[5] = 3; t[6] = 4; t[7] = 5;
    sigma[0][0] = 0.39; sigma[0][1] = 0.31; sigma[0][2] = 0.24; sigma[0][3] = 0.22; sigma[0][4] = 0.16; sigma[0][5] = 0.19; sigma[0][6] = 0.23; sigma[0][7] = 0.29; sigma[0][8] = 0.38;
    sigma[1][0] = 0.44; sigma[1][1] = 0.36; sigma[1][2] = 0.27; sigma[1][3] = 0.21; sigma[1][4] = 0.17; sigma[1][5] = 0.21; sigma[1][6] = 0.27; sigma[1][7] = 0.35; sigma[1][8] = 0.4;
    sigma[2][0] = 0.45; sigma[2][1] = 0.3; sigma[2][2] = 0.25; sigma[2][3] = 0.21; sigma[2][4] = 0.18; sigma[2][5] = 0.22; sigma[2][6] = 0.29; sigma[2][7] = 0.37; sigma[2][8] = 0.45;
    sigma[3][0] = 0.48; sigma[3][1] = 0.42; sigma[3][2] = 0.34; sigma[3][3] = 0.28; sigma[3][4] = 0.2; sigma[3][5] = 0.26; sigma[3][6] = 0.31; sigma[3][7] = 0.42; sigma[3][8] = 0.5;
    sigma[4][0] = 0.52; sigma[4][1] = 0.43; sigma[4][2] = 0.34; sigma[4][3] = 0.26; sigma[4][4] = 0.21; sigma[4][5] = 0.27; sigma[4][6] = 0.38; sigma[4][7] = 0.45; sigma[4][8] = 0.55;
    sigma[5][0] = 0.54; sigma[5][1] = 0.46; sigma[5][2] = 0.34; sigma[5][3] = 0.27; sigma[5][4] = 0.23; sigma[5][5] = 0.28; sigma[5][6] = 0.36; sigma[5][7] = 0.49; sigma[5][8] = 0.58;
    sigma[6][0] = 0.57; sigma[6][1] = 0.50; sigma[6][2] = 0.46; sigma[6][3] = 0.35; sigma[6][4] = 0.25; sigma[6][5] = 0.32; sigma[6][6] = 0.45; sigma[6][7] = 0.54; sigma[6][8] = 0.6;
    sigma[7][0] = 0.60; sigma[7][1] = 0.52; sigma[7][2] = 0.41; sigma[7][3] = 0.31; sigma[7][4] = 0.26; sigma[7][5] = 0.34; sigma[7][6] = 0.4; sigma[7][7] = 0.55; sigma[7][8] = 0.62;
    
    //vol surface
    ImpliedVolatilitySurface Impliedsurface(t, s, sigma,0);   
    DupireLocalVolatilitySurface Localsurface(Impliedsurface, 0.0001, 0.0001, 100);

    /*
    0.0001,             Maturity epsilon, 
    0.0001,             Strike epsilon
    100,                Spot
    */ 

    //Heston Model
    Heston_local_sto_vol_Model model(0,-0.315,init_spot_variance,1.05,0.95, 0.0855,Localsurface,b);
    /*
    0,                  Rate, 
    -0.315,             Correlation
    1.05,               kappa
    0.95,               volo_vol
    0.0855,             theta
    b                   bin
    */ 
    
    Vector scheme{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1}; //[0:1] scheme
    vector<Pair> ssv(100, init_spot_variance);

    PathSimulatorEuler Eu_scheme(model, scheme);
    PathSimulatorMilstein Mil_scheme(model, scheme);
    PathSimulatorQE QE_scheme(model, scheme);   
    /*for (int i=0; i<=10;i++){
        fprintf(file,"%f \t%f \t%f \n",Eu_scheme.next_step(i, init_spot_variance, ssv).first, Mil_scheme.next_step(i, init_spot_variance, ssv).first, QE_scheme.next_step(i, init_spot_variance, ssv).first);};

    fclose(file);*/

    /*outs the 0data.csv external use*/
    
   
    double spot=QE_scheme.next_step(10, init_spot_variance, ssv).first;
    BsCallvanilla Call2(0, 0, 10,spot, 100);
    double vol2 = NewtonRaphson<BSCall, &BSCall::Price, &BSCall::Vega>(21.71805807260404, 0.5, 0.1, Call2);
    cout << vol2 << " - vola2" << endl;
    double Price2 = BlackScholesCallvanilla(spot,100 , 0, 0, vol2, 10);
    cout << Price2 << " - BScall2" << endl;

    /* outs 
    0.198861 - vola2
    21.781 - BScall2*/
    return 0;
}