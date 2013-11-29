#include "flann/headers/flann.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;
typedef vector<float> dary;
dary read(string);
void write(string,float*,int); 

int main(int argc, char* argv[]) {
	// build cluster centers
	/*
	float *result=new float[150000*128];
	dary data=read("./features/esp.feature");
	float *dataset=new float[data.size()];
	for (unsigned i=0;i<data.size();i++) {
		dataset[i]=data[i];
	}
	IndexParameters clusterPara;
	clusterPara.algorithm=KMEANS;
	clusterPara.checks = 2048;
	clusterPara.cb_index=0.6;
	clusterPara.branching=10;
	clusterPara.iterations=15;
	clusterPara.centers_init=CENTERS_GONZALES;
	clusterPara.target_precision=-1;
	clusterPara.build_weight=0.01;
	clusterPara.memory_weight=1;
	int num_clusters = min(flann_compute_cluster_centers(dataset,data.size()/128,128,150000,result,&clusterPara,NULL),150000);
	cout<<"calculate accomplished"<<endl;
	cout<<"num of clusters calculated: "<<num_clusters<<endl;
	write("esp.centers",result,num_clusters);
	*/
	/*
	IndexParameters indexPara;
	indexPara.algorithm = KDTREE;
	indexPara.checks = 2048;
	indexPara.trees=8;
	indexPara.target_precision = -1;
	indexPara.build_weight=0.01;
	indexPara.memory_weight=1;
	float* speed;
	dary d=read("esp.centers");
	float* dataset=new float[d.size()];
	for (unsigned i=0;i<d.size();i++) {
		dataset[i]=d[i];
	}
	FLANN_INDEX index=flann_build_index(dataset,d.size()/128,128,speed,&indexPara,0);
	cout<<"index built"<<endl;
	delete dataset;
	d=read("./features/esp.feature");
	dataset=new float[d.size()];
	for (unsigned i=0;i<d.size();i++) {
		dataset[i]=d[i];
	}
	FLANNParameters findPara;
	findPara.log_level=LOG_NONE;
	findPara.log_destination=NULL;
	findPara.random_seed=CENTERS_RANDOM;
	int* result=new int[d.size()/128];
	cout<<"start calculating nearest neighbors"<<endl;
	int neighbors=flann_find_nearest_neighbors_index(index,dataset,d.size()/128,result,1,1024,&findPara);
	cout<<"calculating nearest neighbors complete"<<endl;
	ofstream f("esp.neighbors");
	for (unsigned i=0;i<d.size()/128;i++) {
		if (i%10000==0)
			cout<<"writing esp.neighbors at line "<<i<<endl;
		f<<result[i]<<endl;
	}
	f.close();
	*/
	ifstream fo("./features/esp.size");
	ifstream fi("esp.neighbors");
	ifstream ilist("./features/imglist.txt");
	ofstream result("esp.trec");
	vector<int> data;
	string line;
	while(getline(fi,line)) {
		int s;
		istringstream iss(line);
		iss>>s;
		data.push_back(s);
	}
	fi.close();
	vector<string> imgs;
	while(getline(ilist,line)) {
		string n;
		istringstream iss(line);
		iss>>n;
		imgs.push_back(n);
	}
	ilist.close();
	int data_count=0;
	int count=0;
	while(getline(fo,line)) {
		int s;
		istringstream iss(line);
		iss>>s;
		result<<"<DOC>"<<endl;
		result<<"<DOCNO>"<<imgs[count]<<"</DOCNO>"<<endl;
		result<<"<TEXT>"<<endl;
		for (unsigned i=0;i<s;i++) {
			cout<<
		}
		result<<"</TEXT>"<<endl;
		result<<"</DOC>"<<endl;
		count++;
	}
}
dary read(string name) {
	dary data;
	ifstream f(name);
	string line;
	int counter=0;
	while (getline(f,line)) {
		if (counter%10000 == 0)
			cout<<"reading "<<name<<" at line "<<counter<<endl;
		float a;
		istringstream iss(line);
		vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};
		for (unsigned i=0;i<tokens.size();i++) {
			istringstream(tokens[i])>>a;
			data.push_back(a);
		}
		counter++;
	}
	f.close();
	return data;
}
void write(string name,float* dataset,int c) {
	ofstream f(name);
	for (unsigned i=0;i<c;i++) {
		if (i%10000==0)
			cout<<"writing "<<name<<" at line "<<i<<endl;
		for (unsigned j=0;j<127;j++) {
			f<<dataset[i*128+j]<<" ";
		}
		f<<dataset[i*128+127]<<endl;
	}	
}
