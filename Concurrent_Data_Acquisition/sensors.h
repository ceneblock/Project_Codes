#ifndef SENSORS_H
#define SENSORS_H
// declare a function to calculate the collecting duration
float timestamp(struct timeval t_start, struct timeval t_end);

#include <array>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>

#include <SenseHat.h>
class Sensors
{
  
  public:
    // declare functions to collect data from different sensors

    static std::shared_ptr<Sensors> GetInstance(const char* configLocation = "config.txt");

    ~Sensors();

    void collect_pression();
    void collect_humidity();
    void collect_temperature();
    void collect_orientation();
    void collect_acceleration();
    void collect_magnetisme();

    // declare a function to unify all collecting functions using the function pointer
    void mainFcn(void (*collectFcn)(int i));

    void run();

    void print_pression();
    void print_temperature();
    void print_humidity();
    void print_orientation();
    void print_acceleration();
    void print_magnetisme();

    void test();
  private:
    Sensors(const char* configLocation);
    
    float t,h,p,xm,ym,zm,xa,ya,za,pitch,roll,yaw;
    //struct timeval t_start, t_end;
    //struct timeval pt_start, pt_end;
    std::array<std::array<float, 2>, 10> d0;
    std::array<std::array<float, 2>, 10> d1;
    std::array<std::array<float, 2>, 10> d2;
    std::array<std::array<float, 4>, 10> d3;
    std::array<std::array<float, 4>, 10> d4;
    std::array<std::array<float, 4>, 10> d5;

    std::vector<int> v;

    std::vector<std::thread> threadVec;

    SenseHat sh;
    std::mutex m;

    const int num = 10;
};
#endif
