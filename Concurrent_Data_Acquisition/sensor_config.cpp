string location = "config.txt";
vector<int> v;

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

