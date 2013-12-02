#LUCENE_PATH=lucene-4.6.0/
#LUCENE_CLASS_PATH=$(LUCENE_PATH)/core/lucene-core-4.6.0.jar:$(LUCENE_PATH)/queryparser/lucene-query/lucene-queryparser-4.6.0.jar:$(LUCENE_PATH)/analysis/common/lucene-analyzers-common-4.6.0.jar
all:build-trec build-new


build-index: IndexTREC.java TrecDocIterator.java
	javac -classpath $(LUCENE_CLASS_PATH) TrecDocIterator.java IndexTREC.java
build-trec: main.cpp 
	g++ -std=c++0x main.cpp -o build-trec -I ./flann/headers ./flann/libs/linux/libflann_x64.a -lstdc++
build-new: build-new.cpp
	g++ -std=c++0x build-new.cpp -o build-new -I ./flann/headers ./flann/libs/linux/libflann_x64.a -lstdc++
