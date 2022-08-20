#ifndef SENSORS_H
#define SENSORS_H
// declare a function to calculate the collecting duration
float timestamp(struct timeval t_start, struct timeval t_end);

#include <array>
#include <vector>
#include <thread>
class sensors
{
  
  public:
    // declare functions to collect data from different sensors

    sensors(const char* configLocation);

    void collect_pression(int i);
    void collect_humidity(int i);
    void collect_temperature(int i);
    void collect_orientation(int i);
    void collect_acceleration(int i);
    void collect_magnetisme(int i);

    // declare a function to unify all collecting functions using the function pointer
    void mainFcn(void (*collectFcn)(int i));

    void run();

    void print_pression();
    void print_temperature();
    void print_humidity();
    void print_orientation();
    void print_acceleration();
    void print_magnetisme();

  private:
    float t,h,p,xm,ym,zm,xa,ya,za,pitch,roll,yaw;
    struct timeval t_start, t_end;
    struct timeval pt_start, pt_end;
    std::array<float, 2> d0;
    std::array<float, 2> d1;
    std::array<float, 2> d2;
    std::array<float, 4> d3;
    std::array<float, 4> d4;
    std::array<float, 4> d5;

    std::vector<int> v;

    std::vector<std::thread> threadVec;
};
#endif
