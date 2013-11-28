#include "flann/headers/flann.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;

int main(int argc, char* argv[]) {
	vector<vector<int> > data;
	ifstream fileReader("./features/esp.feature");
	string line;
	int counter=0;
	while(getline(fileReader,line)) {
		if (counter%10000 == 0) {
			cout<<"still processing, currently "<<counter<<endl;
		}
		int a;
		istringstream iss(line);
		vector<int> tmp;
		vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};
		for (unsigned i=0;i<tokens.size();i++) {
			istringstream(tokens[i])>>a;
			tmp.push_back(a);
		}
		data.push_back(tmp);
		counter++;
	}
	for (unsigned i=0;i<data[0].size();i++) {
		cout<<data[0][i]<<" ";
	}
	cout<<endl;
}
