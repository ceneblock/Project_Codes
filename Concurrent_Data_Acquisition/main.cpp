#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <SenseHat.h>
#include <time.h>
#include <mutex>
#include <ctime>
#include <cstddef>
#include <new>
#include <raspicam/raspicam.h>
#include <thread>

// include all .cpp and .h files
#include "sensor_config.h"
#include "collect_data.h"
#include "print_data.h"
#include "get_image.h"
using namespace std;


#ifdef CONFIG_H
#include "sensor_config.cpp"
#endif
#ifdef COLLECT_H
#include "collect_data.cpp"
#endif
#ifdef PRINT_H
#include "print_data.cpp"
#endif
#ifdef IMAGE_H
#include "get_image.cpp"
#endif

int main(){
	// let the LED Matrix looks like a progress bar
	sh.Effacer(); 
    COULEUR vert  = sh.ConvertirRGB565("#009900");
    COULEUR rouge = sh.ConvertirRGB565(255,0,0);

    for (int i=0; i<8; i++){
		sh.AllumerPixel(1, i, BLEU);
		sh.AllumerPixel(0, i, rouge);
		sh.AllumerPixel(2, i, vert);
		sleep(1);
    }
	
    // read the configurable information from a file to a vector
    v = config();
    vector<thread> vth;
	
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
	
	// create threads to make all functions that are used for processing run concurrently. 
	thread th0(print_pression);
	thread th1(print_temperature);
	thread th2(print_humidity);
	thread th3(print_orientation);
	thread th4(print_acceleration);
	thread th5(print_magnetisme);

    // join them to avoid premature termination of the program
	th0.join();
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	
	// capture a image using the Raspberry Pi camera
    if (get_image() == -1){
		cout << "Get image failed" << endl;    
    }
}
