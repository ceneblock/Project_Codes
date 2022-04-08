#include "matplotlibcpp.h"
#include <SenseHat.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <numeric>
#include <string>

#define N 1000

namespace plt = matplotlibcpp;

// define a function to calculate the mean, variance and standard deviation of a vector
void cal_func(std::vector<float> v, std::string str){
    double mean = std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(), std::bind2nd(std::minus<double>(), mean));
    double var = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0) / v.size();
    double stdev = std::sqrt(var);
    std::cout << str << "'s " << "mean: " << mean << ", variance: " << var << " and standard deviation: " << stdev << std::endl;

}

// define a function to plot a value vs sample figure for pressure, humidity and temperature sensors
void plot_function1(std::vector<float> v, std::string str1, std::string str2){
    plt::figure();
    plt::plot(v);
    plt::xlabel("Sample");
    plt::ylabel("Value");
    plt::title(str1);
    plt::save(str2);
}

// // define a function to plot a value vs sample figure for the IMU chip
void plot_function2(std::vector<float> v1, std::vector<float> v2, std::vector<float> v3, std::string str1, std::string str2){
    plt::figure();
    plt::plot(v1);
    plt::plot(v2);
    plt::plot(v3);
    plt::xlabel("Sample");
    plt::ylabel("Value");
    plt::title(str1);
    plt::save(str2);
}

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
    
    // compute the mean, variance and standard deviation of data

    cal_func(p, "Pressure");
    cal_func(t, "Temperature");
    cal_func(h, "Humidity");
    cal_func(XA, "Acceleration(x axis)");
    cal_func(YA, "Acceleration(y axis)");
    cal_func(ZA, "Acceleration(z axis)");

    // plot figures (value vs sample) to show the changes of each sensor's value
    
    plot_function1(p, "Pressure", "value_p.png");
    plot_function1(t, "Temperature", "value_t.png");
    plot_function1(h, "Humidity", "value_h.png");
    plot_function2(XA, YA, ZA, "Acceleration", "value_a.png");
    plot_function2(XM, YM, ZM, "Magnetism", "value_m.png");
    plot_function2(PITCH, ROLL, YAW, "Orientation", "value_o.png");
    
}
