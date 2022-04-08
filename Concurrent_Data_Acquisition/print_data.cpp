void print_pression(){
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

void print_temperature(){
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

void print_humidity(){
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

void print_orientation(){
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

void print_acceleration(){
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

void print_magnetisme(){
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
