#include "flann/headers/flann.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;
int main(int argc,char* argv[]) {
	if (argc!=4) {
		cout<<"format:"<<endl;
		cout<<"build-new [center file] [key file] [output]"<<endl;
		exit(1);
	}
	string center_file=argv[1];
	string in_file=argv[2];
	string out_file=argv[3];
	vector<float> raw_data;
	ifstream fcenter(center_file.c_str());
	ifstream fin(in_file.c_str());
	ofstream fout(out_file.c_str());
	string line;
	while(getline(fcenter,line)) {
		float a;
		istringstream iss(line);
		vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};
		for (unsigned i=0;i<tokens.size();i++) {
			istringstream(tokens[i])>>a;
			raw_data.push_back(a);
		}
	}
	fcenter.close();
	float *centers = new float[raw_data.size()];
	for (unsigned i=0;i<raw_data.size();i++) {
		centers[i]=raw_data[i];
	}
	vector<float> features_data;
	while(getline(fin,line)) {
		float a;
		istringstream iss(line);
		vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};
		for (unsigned i=4;i<tokens.size();i++) {
			istringstream(tokens[i])>>a;
			features_data.push_back(a);
		}
	}
	fin.close();
	float *features=new float[features_data.size()];
	for (unsigned i=0;i<features_data.size();i++) {
		features[i]=features_data[i];
	}
	float *speed;
	IndexParameters indexPara;
	indexPara.algorithm = KDTREE;
	indexPara.checks = 2048;
	indexPara.trees=8;
	indexPara.target_precision = -1;
	indexPara.build_weight=0.01;
	indexPara.memory_weight=1;
	FLANN_INDEX index=flann_build_index(centers,raw_data.size()/128,128,speed,&indexPara,0);
	FLANNParameters findPara;
	findPara.log_level=LOG_NONE;
	findPara.log_destination=NULL;
	findPara.random_seed=CENTERS_RANDOM;
	int* result=new int[features_data.size()/128];
	int neighbors=flann_find_nearest_neighbors_index(index,features,features_data.size()/128,result,1,1024,&findPara);
	for (unsigned i=0;i<features_data.size()/128-1;i++) {
		fout<<result[i]<<" ";	
	}	
	fout<<result[features_data.size()/128-1];
	fout.close();
}
