#include "matplotlibcpp.h"
#include <SenseHat.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <vector>

#define N 1000

namespace plt = matplotlibcpp;


int main(){
    // define a SenseHAT object
    SenseHat carte;

    // define variables to store data
    float pression;
    float temperature;
    float humidite;
    float xa,ya,za,xm,ym,zm;
    float pitch,roll,yaw;
    
    std::vector<float> p;
    std::vector<float> t;
    std::vector<float> h;
    std::vector<float> XA;
    std::vector<float> YA;
    std::vector<float> ZA;
    std::vector<float> XM;
    std::vector<float> YM;
    std::vector<float> ZM;
    std::vector<float> PITCH;
    std::vector<float> ROLL;
    std::vector<float> YAW;
    
    // collect data and insert them into vectors in a loop
    for(int i=0; i<N; i++){
        pression    = carte.ObtenirPression();
        temperature = carte.ObtenirTemperature();
        humidite    = carte.ObtenirHumidite();
        carte.ObtenirAcceleration(xa,ya,za);
        carte.ObtenirOrientation(pitch,roll,yaw);
        carte.ObtenirMagnetisme(xm,ym,zm);
	
        p.push_back(pression);
        t.push_back(temperature);
        h.push_back(humidite);
        XA.push_back(xa);
        YA.push_back(ya);
        ZA.push_back(za);
        XM.push_back(xm);
        YM.push_back(ym);
        ZM.push_back(zm);
        PITCH.push_back(pitch);
        ROLL.push_back(roll);
        YAW.push_back(yaw);
    }
    
    // plot figures (value vs sample) to show the changes of each sensor's value
    
    plt::figure();
    plt::plot(p);
    plt::xlabel("Sample");
    plt::ylabel("Value");
    plt::title("Pressure");
    plt::save("value_p.png");
    
    plt::figure();
    plt::plot(t);
    plt::xlabel("Sample");
    plt::ylabel("Value");
    plt::title("Temperature");
    plt::save("value_t.png");
    
    plt::figure();
    plt::plot(h);
    plt::xlabel("Sample");
    plt::ylabel("Value");
    plt::title("Humidity");
    plt::save("value_h.png");
    plt::figure();
    
    plt::plot(XA);
    plt::plot(YA);
    plt::plot(ZA);
    plt::xlabel("Sample");
    plt::ylabel("Value");
    plt::title("Acceleration");
    plt::save("value_a.png");
    
    plt::figure();
    plt::plot(XM);
    plt::plot(YM);
    plt::plot(ZM);
    plt::xlabel("Sample");
    plt::ylabel("Value");
    plt::title("Magnetisme");
    plt::save("value_m.png");
    
    plt::figure();
    plt::plot(PITCH);
    plt::plot(ROLL);
    plt::plot(YAW);
    plt::xlabel("Sample");
    plt::ylabel("Value");
    plt::title("Orientation");
    plt::save("value_o.png");
    
}
