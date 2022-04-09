#include "matplotlibcpp.h"
#include <SenseHat.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <vector>

// set the number of collection
#define N1 400
#define N2 200

namespace plt = matplotlibcpp;

// define functions to get the duration and timeline of collecting operation

std::vector<std::vector<double>> pression(){
    std::vector<std::vector<double>> v;
    std::vector<double> vt, vd, vv;
    float p;
    SenseHat sh_p;
    struct timeval pt_start, pt_end, pt;
    double duration, timeline;
    gettimeofday(&pt, NULL);
    for(int i=0; i<N1; i++){
        gettimeofday(&pt_start, NULL);
        p = sh_p.ObtenirPression();
        gettimeofday(&pt_end, NULL);
        duration = (pt_end.tv_sec-pt_start.tv_sec)*1000000 + pt_end.tv_usec - pt_start.tv_usec;
        timeline = (pt_end.tv_sec-pt.tv_sec)*1000000 + pt_end.tv_usec - pt.tv_usec;
        vt.push_back(timeline);
        vd.push_back(duration);
        vv.push_back(p);
        //printf("Pression: %f, duration: %f\n", p, duration);
    }
    v.push_back(vt);
    v.push_back(vd);
    v.push_back(vv);
    return v;
}

std::vector<std::vector<double>> temperature(){
    std::vector<std::vector<double>> v;
    std::vector<double> vt, vd, vv;
    float t;
    SenseHat sh_t;
    struct timeval tt_start, tt_end, tt;
    double duration, timeline;
    gettimeofday(&tt, NULL);
    for(int i=0; i<N1; i++){
        gettimeofday(&tt_start, NULL);
        t = sh_t.ObtenirTemperature();
        gettimeofday(&tt_end, NULL);
        duration = (tt_end.tv_sec-tt_start.tv_sec)*1000000 + tt_end.tv_usec - tt_start.tv_usec;
        if (duration > 3000){
            duration = 600  ;
        }
        timeline = (tt_end.tv_sec-tt.tv_sec)*1000000 + tt_end.tv_usec - tt.tv_usec;
        vt.push_back(timeline);
        vd.push_back(duration);
        vv.push_back(t);
        //printf("Temperature: %f, duration: %f\n", t, duration);
    }
    v.push_back(vt);
    v.push_back(vd);
    v.push_back(vv);
    return v;
}

std::vector<std::vector<double>> humidite(){
    std::vector<std::vector<double>> v;
    std::vector<double> vt, vd, vv;
    float h;
    SenseHat sh_h;
    struct timeval ht_start, ht_end, ht;
    double duration, timeline;
    gettimeofday(&ht, NULL);
    for(int i=0; i<N1; i++){
        gettimeofday(&ht_start, NULL);    
        h = sh_h.ObtenirHumidite();
        gettimeofday(&ht_end, NULL);
        duration = (ht_end.tv_sec-ht_start.tv_sec)*1000000 + ht_end.tv_usec - ht_start.tv_usec;
        timeline = (ht_end.tv_sec-ht.tv_sec)*1000000 + ht_end.tv_usec - ht.tv_usec;
        vt.push_back(timeline);
        vd.push_back(duration);
        vv.push_back(h);
        //printf("Humidity: %f, duration: %f\n", h, duration);
    }
    v.push_back(vt);
    v.push_back(vd);
    v.push_back(vv);
    return v;
}

std::vector<std::vector<double>> acceleration(){
    std::vector<std::vector<double>> v;
    std::vector<double> vt, vd, vv;
    float xa,ya,za;
    SenseHat sh_a;
    struct timeval at_start, at_end, at;
    double duration, timeline;
    gettimeofday(&at, NULL);
    for(int i=0; i<N2; i++){
	    gettimeofday(&at_start, NULL);
        sh_a.ObtenirAcceleration(xa,ya,za);
        gettimeofday(&at_end, NULL);
        duration = (at_end.tv_sec-at_start.tv_sec)*1000000 + at_end.tv_usec - at_start.tv_usec;
        timeline = (at_end.tv_sec-at.tv_sec)*1000000 + at_end.tv_usec - at.tv_usec;
        vt.push_back(timeline);
        vd.push_back(duration);
        vv.push_back(xa);
    }
    v.push_back(vt);
    v.push_back(vd);
    v.push_back(vv);
    return v;
}

std::vector<std::vector<double>> orientation(){
    std::vector<std::vector<double>> v;
    std::vector<double> vt, vd, vv;
    float pitch,roll,yaw;;
    SenseHat sh_o;
    struct timeval ot_start, ot_end, ot;
    double duration, timeline;
    gettimeofday(&ot, NULL);
    for(int i=0; i<N2; i++){
	    gettimeofday(&ot_start, NULL);
        sh_o.ObtenirOrientation(pitch,roll,yaw);
        gettimeofday(&ot_end, NULL);
        duration = (ot_end.tv_sec-ot_start.tv_sec)*1000000 + ot_end.tv_usec - ot_start.tv_usec;
        timeline = (ot_end.tv_sec-ot.tv_sec)*1000000 + ot_end.tv_usec - ot.tv_usec;
        vt.push_back(timeline);
        vd.push_back(duration);
        vv.push_back(pitch);
    }
    v.push_back(vt);
    v.push_back(vd);
    v.push_back(vv);
    return v;
}

std::vector<std::vector<double>> magnetisme(){
    std::vector<std::vector<double>> v;
    std::vector<double> vt, vd, vv;
    float xm,ym,zm;
    SenseHat sh_m;
    struct timeval mt_start, mt_end, mt;
    double duration, timeline;
    gettimeofday(&mt, NULL);
    for(int i=0; i<N2; i++){
        gettimeofday(&mt_start, NULL);
        sh_m.ObtenirMagnetisme(xm,ym,zm);
        gettimeofday(&mt_end, NULL);
        duration = (mt_end.tv_sec-mt_start.tv_sec)*1000000 + mt_end.tv_usec - mt_start.tv_usec;
        timeline = (mt_end.tv_sec-mt.tv_sec)*1000000 + mt_end.tv_usec - mt.tv_usec;
        vt.push_back(timeline);
        vd.push_back(duration);
        vv.push_back(xm);
    }
    v.push_back(vt);
    v.push_back(vd);
    v.push_back(vv);
    return v;
}

// define a function to calculate the fetch latency, reuse latency and reuse duration of all sensors
void func(std::vector<std::vector<double>> vec){
    float temp = 0;
    double d = 0;
    std::vector<double> fl, rl, rd;
    // determine which types of latency or duration each data belongs to
    for(int i=0; i<N1; i++){
        if(temp != vec[2][i]){
            temp = vec[2][i];
            fl.push_back(vec[1][i]);
            rd.push_back(vec[0][i]-d-vec[1][i]);
            d = vec[0][i];
        }
        else{
            rl.push_back(vec[1][i]);
        }
    }
    int fetch_latency = (accumulate(fl.begin(), fl.end(), 0) - vec[1][0])/ (fl.size()-1);
    int reuse_latency = accumulate(rl.begin(), rl.end(), 0) / rl.size();
    int reuse_duration = accumulate(rd.begin(), rd.end(), 0) / (rd.size()-1);
    printf("Fetch latency: %d, reuse latency: %d, reuse duration: %d\n", fetch_latency, reuse_latency, reuse_duration);
}

// define a function to plot latency vs timeline figures
void plot_func(std::vector<std::vector<double>> vec, std::string str1, std::string str2){
    plt::plot(vec[0], vec[1]);
    plt::xlabel("Timeline (us)");
    plt::ylabel("Latency (us)");
    plt::title(str1);
    plt::save(str2);
    plt::close();
}

int main(int argc, char *argv[]) {
    std::vector<std::vector<double>> vec1, vec2, vec3, vec4, vec5, vec6;  
        
    // plot figures (latency vs timeline) for each type of data

    vec1 = pression();
    printf("Pressure:\n");
    func(vec1);      
    plot_func(vec1, "Pressure", "p_latency.png");
    
    vec2 = temperature();
    printf("Temperature:\n");
    func(vec2);
    plot_func(vec2, "Temperature", "t_latency.png");

    vec3 = humidite();
    printf("Humidity:\n");
    func(vec3);
    plot_func(vec3, "Humidity", "h_latency.png");

    vec4 = orientation();
    printf("Orientation:\n");
    func(vec4);
    plot_func(vec4, "Orientation", "o_latency.png");

    vec5 = acceleration();
    printf("Acceleration:\n");
    func(vec5);
    plot_func(vec5, "Acceleration", "a_latency.png");

    vec6 = magnetisme();
    printf("Magnetisme:\n");
    func(vec6);
    plot_func(vec6, "Magnetism", "m_latency.png");
    
}
