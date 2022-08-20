#include "sensors.h"
#include <ifstream>

// define a function to calculate the duration
float timestamp(struct timeval t_start, struct timeval t_end){
	float result;
	result = (t_end.tv_sec-t_start.tv_sec)*1000000 + t_end.tv_usec - t_start.tv_usec;
	return result;
}

sensors::sensors(const char* configLocation)
{
  std::ifstream ifs(configLocation, std::ifstream::in);
  if(ifs.is_open())
  {
    //read in the file
    int decimal = 0;
    ifs >> decimal;
    while(decimal)
    {
      v.push_back(decimal%2);
      decimal = decimal/2;  
    }
  }
  else
  {
    //do some default stuff here...
  }

}

// define functions to collect data from different sensors

void sensors::collect_pression(int i){
	gettimeofday(&t_start, NULL);
	p = sh.ObtenirPression();
	gettimeofday(&t_end, NULL);
	d0.data_[i][0] = p;
	d0.data_[i][1] = timestamp(t_start, t_end);
}

void sensors::collect_humidity(int i){
	gettimeofday(&t_start, NULL);
	h = sh.ObtenirHumidite();
	gettimeofday(&t_end, NULL);
	d1.data_[i][0] = h;
	d1.data_[i][1] = timestamp(t_start, t_end);
}

void sensors::collect_temperature(int i){
	gettimeofday(&t_start, NULL);
	t = sh.ObtenirTemperature();
	gettimeofday(&t_end, NULL);
	d2.data_[i][0] = t;
	d2.data_[i][1] = timestamp(t_start, t_end);
}

void sensors::collect_orientation(int i){
	gettimeofday(&t_start, NULL);
	sh.ObtenirOrientation(pitch,roll,yaw);
	gettimeofday(&t_end, NULL);
	d3.data_[i][0] = pitch;
	d3.data_[i][1] = roll;
	d3.data_[i][2] = yaw;
	d3.data_[i][3] = timestamp(t_start, t_end);
}

void sensors::collect_acceleration(int i){
	gettimeofday(&t_start, NULL);
	sh.ObtenirAcceleration(xa,ya,za);
	gettimeofday(&t_end, NULL);
	d4.data_[i][0] = xa;
	d4.data_[i][1] = ya;
	d4.data_[i][2] = za;
	d4.data_[i][3] = timestamp(t_start, t_end);
}

void sensors::collect_magnetisme(int i){
	gettimeofday(&t_start, NULL);
	sh.ObtenirMagnetisme(xm,ym,zm);
	gettimeofday(&t_end, NULL);
	d5.data_[i][0] = xm;
	d5.data_[i][1] = ym;
	d5.data_[i][2] = zm;
	d5.data_[i][3] = timestamp(t_start, t_end);
}

// define a function to execute collecting functions using the functioon pointer
void sensors::mainFcn (void (*collectFcn)(int i)){
	for (int i=0; i<num; i++){
		unique_lock<mutex> lck(m);
		collectFcn(i);
	}
}

void sensors::run()
{
 	if(v[0] == 1){
		threadVec.push_back(std::thread(mainFcn, collect_pression));
	}
	if(v[1] == 1){
		threadVec.push_back(std::thread(mainFcn, collect_humidity));
	}
	if(v[2] == 1){
		threadVec.push_back(std::thread(mainFcn, collect_temperature));
	}
	if(v[3] == 1){
		threadVec.push_back(std::thread(mainFcn, collect_orientation));
	}
	if(v[4] == 1){
		threadVec.push_back(std::thread(mainFcn, collect_acceleration));
	}
	if(v[5] == 1){
		threadVec.push_back(std::thread(mainFcn, collect_magnetisme));
	}	
} 

void sensors::print_pression(){
	if(v[0] == 1){
		float p(0), ts(0);
		for(int i=0; i<num; i++){
			p = p + d0.data_[i][0];
			ts = ts + d0.data_[i][1];
		}
		unique_lock<mutex> lck(m);
		cout << "Pression : " << p/num << " hPa" << endl;
		cout << "Pression Time: " << ts/num << " us" << endl;
	}
}

void sensors::print_temperature(){
	if(v[1] == 1){
		float t(0), ts(0);
		for(int i=0; i<num; i++){
			t = t + d1.data_[i][0];
			ts = ts + d1.data_[i][1];
		}
		unique_lock<mutex> lck(m);
		cout << "Temperature : " << t/num << " °C" << endl;
		cout << "Temperature Time: " << ts/num << " us" << endl;
	}
}

void sensors::print_humidity(){
	if(v[2] == 1){
		float h(0), ts(0);
		for(int i=0; i<num; i++){
			h = h + d2.data_[i][0];
			ts = ts + d2.data_[i][1];
		}
		unique_lock<mutex> lck(m);
		cout << "Humidite : " << h/num << " %" << endl;
		cout << "Humidity Time: " << ts/num << " us" << endl;
	}
}

void sensors::print_orientation(){
	if(v[3] == 1){
		float pitch(0), roll(0), yaw(0), ts(0);
		for(int i=0; i<num; i++){
			pitch = pitch + d3.data_[i][0];
			roll = pitch + d3.data_[i][1];
			yaw = pitch + d3.data_[i][2];
			ts = ts + d3.data_[i][3];
		}
		unique_lock<mutex> lck(m);
		cout << "Orientation pitch : " << pitch/num << " roll : " << roll/num << " yaw : " << yaw/num << endl;
		cout << "Orientation Time: " << ts/num << " us" << endl;
	}
}

void sensors::print_acceleration(){
	if(v[4] == 1){
		float xa(0), ya(0), za(0), ts(0);
		for(int i=0; i<num; i++){
			xa = xa + d4.data_[i][0];
			ya = ya + d4.data_[i][1];
			za = za + d4.data_[i][2];
			ts = ts + d4.data_[i][3];
		}
		unique_lock<mutex> lck(m);
		cout << "Acceleration x : " << xa/num << "(g) y : " << ym/num << "(g) z : " << zm/num << "(g)" << endl;
		cout << "Acceleration Time: " << ts/num << " us" << endl;
	}
}

void sensors::print_magnetisme(){
	if(v[5] == 1){
		float xm(0), ym(0), zm(0), ts(0);
		for(int i=0; i<num; i++){
			xm = xm + d4.data_[i][0];
			ym = ym + d4.data_[i][1];
			zm = zm + d4.data_[i][2];
			ts = ts + d4.data_[i][3];
		}
		unique_lock<mutex> lck(m);
		cout << "Magnetisme x : " << xm/num << "(µT) y : " << ym/num << "(µT) z : " << zm/num << "(µT)" << endl;
		cout << "Magnetisme Time: " << ts/num << " us" << endl;
	}
}
