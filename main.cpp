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
	vector<float> data;
	ifstream fileReader("./features/esp.feature");
	string line;
	int counter=0;
	while(getline(fileReader,line)) {
		if (counter%10000 == 0) {
			cout<<"still processing, currently "<<counter<<endl;
		}
		float a;
		istringstream iss(line);
		vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};
		for (unsigned i=0;i<tokens.size();i++) {
			istringstream(tokens[i])>>a;
			data.push_back(a);
		}
		counter++;
	}
	float *dataset=new float[data.size()];
	//float *result=new float[150000*128];
	float *result=0;
	for (unsigned i=0;i<data.size();i++) {
		dataset[i]=data[i];
	}
	IndexParameters para;
	para.algorithm=KMEANS;
	para.checks = 2048;
	para.cb_index=0.6;
	para.branching=10;
	para.iterations=15;
	para.centers_init=CENTERS_GONZALES;
	para.target_precision=-1;
	para.build_weight=0.01;
	para.memory_weight=1;
	flann_compute_cluster_centers(dataset,data.size()/128,128,150000,result,&para,NULL);
}
