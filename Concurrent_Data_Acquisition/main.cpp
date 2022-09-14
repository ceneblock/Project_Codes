#include <vector>
#include <SenseHat.h>
#include <mutex>
#include <thread>
#include "sensors.h"

int main(){
  // initialize a mutex and a SenseHat object
  // let the LED Matrix looks like a progress bar
  
  Sensors::GetInstance("config.txt")->test();
  Sensors::GetInstance("config.txt")->run();
  //sensors.test();  
	
  /*	
  // determine which sensors should be used and create threads to run their collecting functions using the funcction pointer
	if(v[0] == 1){
		vth.push_back(thread(mainFcn, collect_pression));
	}
	if(v[1] == 1){
		vth.push_back(thread(mainFcn, collect_humidity));
	}
	if(v[2] == 1){
		vth.push_back(thread(mainFcn, collect_temperature));
	}
	if(v[3] == 1){
		vth.push_back(thread(mainFcn, collect_orientation));
	}
	if(v[4] == 1){
		vth.push_back(thread(mainFcn, collect_acceleration));
	}
	if(v[5] == 1){
		vth.push_back(thread(mainFcn, collect_magnetisme));
	}	
	
	// join all joinable threads that are created before
	for(thread & th: vth){
	    if(th.joinable()){
			th.join();
		}	
	}
	// create threads to print results concurrently and it's better to use vector<thread> like below
	thread th0(print_pression);
	thread th1(print_temperature);
	thread th2(print_humidity);
	thread th3(print_orientation);
	thread th4(print_acceleration);
	thread th5(print_magnetisme);

    // join them to avoid termination of the program
	th0.join();
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
  */
}
