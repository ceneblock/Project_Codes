mutex m;
SenseHat sh;
int num = 10;
float t,h,p,xm,ym,zm,xa,ya,za,pitch,roll,yaw;
struct timeval t_start, t_end;
struct timeval pt_start, pt_end;
data<float, 2> d0 = {(size_t)num};
data<float, 2> d1 = {(size_t)num};
data<float, 2> d2 = {(size_t)num};
data<float, 4> d3 = {(size_t)num};
data<float, 4> d4 = {(size_t)num};
data<float, 4> d5 = {(size_t)num};

float timestamp(struct timeval t_start, struct timeval t_end){
	float result;
	result = (t_end.tv_sec-t_start.tv_sec)*1000000 + t_end.tv_usec - t_start.tv_usec;
	return result;
}

void collect_pression(int i){
	gettimeofday(&t_start, NULL);
	p = sh.ObtenirPression();
	gettimeofday(&t_end, NULL);
	d0.data_[i][0] = p;
	d0.data_[i][1] = timestamp(t_start, t_end);
}

void collect_humidity(int i){
	gettimeofday(&t_start, NULL);
	h = sh.ObtenirHumidite();
	gettimeofday(&t_end, NULL);
	d1.data_[i][0] = h;
	d1.data_[i][1] = timestamp(t_start, t_end);
}

void collect_temperature(int i){
	gettimeofday(&t_start, NULL);
	t = sh.ObtenirTemperature();
	gettimeofday(&t_end, NULL);
	d2.data_[i][0] = t;
	d2.data_[i][1] = timestamp(t_start, t_end);
}

void collect_orientation(int i){
	gettimeofday(&t_start, NULL);
	sh.ObtenirOrientation(pitch,roll,yaw);
	gettimeofday(&t_end, NULL);
	d3.data_[i][0] = pitch;
	d3.data_[i][1] = roll;
	d3.data_[i][2] = yaw;
	d3.data_[i][3] = timestamp(t_start, t_end);
}

void collect_acceleration(int i){
	gettimeofday(&t_start, NULL);
	sh.ObtenirAcceleration(xa,ya,za);
	gettimeofday(&t_end, NULL);
	d4.data_[i][0] = xa;
	d4.data_[i][1] = ya;
	d4.data_[i][2] = za;
	d4.data_[i][3] = timestamp(t_start, t_end);
}

void collect_magnetisme(int i){
	gettimeofday(&t_start, NULL);
	sh.ObtenirMagnetisme(xm,ym,zm);
	gettimeofday(&t_end, NULL);
	d5.data_[i][0] = xm;
	d5.data_[i][1] = ym;
	d5.data_[i][2] = zm;
	d5.data_[i][3] = timestamp(t_start, t_end);
}

void mainFcn (void (*collectFcn)(int i)){
	for (int i=0; i<num; i++){
		unique_lock<mutex> lck(m);
		collectFcn(i);
	}
}

