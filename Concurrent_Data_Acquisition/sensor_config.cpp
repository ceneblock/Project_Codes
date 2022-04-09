string location = "config.txt";
vector<int> v;

// define a function to read, convert and store the configuration information from a txt file
// the order of configuration is: pressure, humidity, temperature, orientation, acceleration and magnetism
// 1 means the user wants to use this sensor and 0 means the user doesn't want to use this sensor

vector<int> config(){
	string s;
	ifstream infile;
	infile.open(location);
	infile >> s;
	int decimal = stoi(s,nullptr,2);
	vector<int> v;
	while(decimal){
		v.push_back(decimal%2);
		decimal = decimal/2;	
	}
	return v;
}

