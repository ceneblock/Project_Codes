#include "sensors.h"
#include <fstream>

// define a function to calculate the duration
float timestamp(struct timeval t_start, struct timeval t_end){
	float result;
	result = (t_end.tv_sec-t_start.tv_sec)*1000000 + t_end.tv_usec - t_start.tv_usec;
	return result;
}

Sensors::~Sensors()
{
  for(auto &t : threadVec)
  {
    t.join();
  }
}

std::shared_ptr<Sensors> Sensors::GetInstance(const char* configLocation)
{
  static std::shared_ptr<Sensors> sensors(new Sensors(configLocation));

  return sensors;
}

Sensors::Sensors(const char* configLocation)
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

void Sensors::collect_pression(){
	timeval t_start, t_end;
  std::unique_lock lck{m, std::defer_lock};
  for(int i = 0; i < num; ++i)
  {
    lck.lock();
    gettimeofday(&t_start, NULL);
    p = sh.ObtenirPression();
    gettimeofday(&t_end, NULL);
    d0[i][0] = p;
    d0[i][1] = timestamp(t_start, t_end);
    lck.unlock();
  }
}

void Sensors::collect_humidity(){
	timeval t_start, t_end;
  std::unique_lock lck{m, std::defer_lock};
  for(int i = 0; i < num; ++i)
  {
    lck.lock();
    gettimeofday(&t_start, NULL);
    h = sh.ObtenirHumidite();
    gettimeofday(&t_end, NULL);
    d1[i][0] = h;
    d1[i][1] = timestamp(t_start, t_end);
    lck.unlock();
  }
}

void Sensors::collect_temperature(){
	timeval t_start, t_end;
  std::unique_lock lck{m, std::defer_lock};
  for(int i = 0; i < num; ++i)
  {
    lck.lock();
    gettimeofday(&t_start, NULL);
    t = sh.ObtenirTemperature();
    gettimeofday(&t_end, NULL);
    d2[i][0] = t;
    d2[i][1] = timestamp(t_start, t_end);
    lck.unlock();
  }
}

void Sensors::collect_orientation(){
	timeval t_start, t_end;
  std::unique_lock lck{m, std::defer_lock};
  for(int i = 0; i < num; ++i)
  {
    lck.lock();
    gettimeofday(&t_start, NULL);
    sh.ObtenirOrientation(pitch,roll,yaw);
    gettimeofday(&t_end, NULL);
    d3[i][0] = pitch;
    d3[i][1] = roll;
    d3[i][2] = yaw;
    d3[i][3] = timestamp(t_start, t_end);
    lck.unlock();
  }
}

void Sensors::collect_acceleration(){
	timeval t_start, t_end;
  std::unique_lock lck{m, std::defer_lock};
  for(int i = 0; i < num; ++i)
  {
    lck.lock();
    gettimeofday(&t_start, NULL);
    sh.ObtenirAcceleration(xa,ya,za);
    gettimeofday(&t_end, NULL);
    d4[i][0] = xa;
    d4[i][1] = ya;
    d4[i][2] = za;
    d4[i][3] = timestamp(t_start, t_end);
    lck.unlock();
  }
}

void Sensors::collect_magnetisme(){
	timeval t_start, t_end;
  std::unique_lock lck{m, std::defer_lock};
  for(int i = 0; i < num; ++i)
  {
    lck.lock();
    gettimeofday(&t_start, NULL);
    sh.ObtenirMagnetisme(xm,ym,zm);
    gettimeofday(&t_end, NULL);
    d5[i][0] = xm;
    d5[i][1] = ym;
    d5[i][2] = zm;
    d5[i][3] = timestamp(t_start, t_end);
    lck.unlock();
  }
}

void Sensors::run()
{
 	if(v[0] == 1){
		threadVec.push_back(std::thread(&Sensors::collect_pression, this));
	}
	if(v[1] == 1){
		threadVec.push_back(std::thread(&Sensors::collect_humidity, this));
	}
	if(v[2] == 1){
		threadVec.push_back(std::thread(&Sensors::collect_temperature, this));
	}
	if(v[3] == 1){
		threadVec.push_back(std::thread(&Sensors::collect_orientation, this));
	}
	if(v[4] == 1){
		threadVec.push_back(std::thread(&Sensors::collect_acceleration, this));
	}
	if(v[5] == 1){
		threadVec.push_back(std::thread(&Sensors::collect_magnetisme, this));
	}
} 

void Sensors::print_pression(){
	if(v[0] == 1){
		float p(0), ts(0);
		for(int i=0; i<num; i++){
			p =   p + d0[i][0];
			ts = ts + d0[i][1];
		}
		std::unique_lock<std::mutex> lck(m);
		std::cout << "Pression : " << p/num << " hPa" << endl;
		std::cout << "Pression Time: " << ts/num << " us" << endl;
	}
}

void Sensors::print_temperature(){
	if(v[1] == 1){
		float t(0), ts(0);
		for(int i=0; i<num; i++){
			t =   t + d1[i][0];
			ts = ts + d1[i][1];
		}
		std::unique_lock<std::mutex> lck(m);
		std::cout << "Temperature : " << t/num << " °C" << endl;
		std::cout << "Temperature Time: " << ts/num << " us" << endl;
	}
}

void Sensors::print_humidity(){
	if(v[2] == 1){
		float h(0), ts(0);
		for(int i=0; i<num; i++){
			h =   h + d2[i][0];
			ts = ts + d2[i][1];
		}
		std::unique_lock<std::mutex> lck(m);
		std::cout << "Humidite : " << h/num << " %" << endl;
		std::cout << "Humidity Time: " << ts/num << " us" << endl;
	}
}

void Sensors::print_orientation(){
	if(v[3] == 1){
		float pitch(0), roll(0), yaw(0), ts(0);
		for(int i=0; i<num; i++){
			pitch = pitch + d3[i][0];
			roll =  pitch + d3[i][1];
			yaw =   pitch + d3[i][2];
			ts =       ts + d3[i][3];
		}
		std::unique_lock<std::mutex> lck(m);
		std::cout << "Orientation pitch : " << pitch/num << " roll : " << roll/num << " yaw : " << yaw/num << endl;
		std::cout << "Orientation Time: " << ts/num << " us" << endl;
	}
}

void Sensors::print_acceleration(){
	if(v[4] == 1){
		float xa(0), ya(0), za(0), ts(0);
		for(int i=0; i<num; i++){
			xa = xa + d4[i][0];
			ya = ya + d4[i][1];
			za = za + d4[i][2];
			ts = ts + d4[i][3];
		}
		std::unique_lock<std::mutex> lck(m);
		std::cout << "Acceleration x : " << xa/num << "(g) y : " << ym/num << "(g) z : " << zm/num << "(g)" << endl;
		std::cout << "Acceleration Time: " << ts/num << " us" << endl;
	}
}

void Sensors::print_magnetisme(){
	if(v[5] == 1){
		float xm(0), ym(0), zm(0), ts(0);
		for(int i=0; i<num; i++){
			xm = xm + d4[i][0];
			ym = ym + d4[i][1];
			zm = zm + d4[i][2];
			ts = ts + d4[i][3];
		}
		std::unique_lock<std::mutex> lck(m);
		std::cout << "Magnetisme x : " << xm/num << "(µT) y : " << ym/num << "(µT) z : " << zm/num << "(µT)" << endl;
		std::cout << "Magnetisme Time: " << ts/num << " us" << endl;
	}
}

void Sensors::test()
{
  sh.Effacer(NOIR);
  COULEUR vert  = sh.ConvertirRGB565("#009900");
  COULEUR rouge = sh.ConvertirRGB565(255,0,0);

  for (int i=0; i<8; i++){
	sh.AllumerPixel(1, i, BLEU);
	sh.AllumerPixel(0, i, rouge);
	sh.AllumerPixel(2, i, vert);
	sleep(1);
  }
}
