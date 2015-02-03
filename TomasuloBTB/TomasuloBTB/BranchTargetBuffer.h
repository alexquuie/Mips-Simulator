#ifndef BRANCHTARGETBUFFER_H
#define BRANCHTARGETBUFFER_H
#include<vector>
#include <iostream>
#include <string>
using namespace std;

class BranchNode{
public:
	BranchNode();
	//Get Function
	int getAdd();
	int getTar();
	int gettrueTar();
	int getTakenFlag();
	int getlruIndex();	
	int getrs_Index();	
	bool getupdate_Flag();

	//Set Function
    void setAdd(int);
	void setTar(int);
	void settrueTar(int);
	void setTakenFlag(int);
	void setlruIndex(int);
	void setrs_Index(int);	
	void setupdate_Flag(bool);
private:
	int address;
	int Tar;	
	int trueTar;	
	int takenFlag;
	int lruIndex;
	int rs_index;
	bool update_Flag;
};

class BranchTargetBuffer{
public:
	BranchTargetBuffer();
	BranchTargetBuffer(int);
	//get Function
	BranchNode getNode(int);
	int getNodeNum();
	//ADT method
	//truetar
	int gettrueTar(int);
	void settrueTar(int,int);
	//upf
	bool getupdate_Flag(int);
	void setupdate_Flag(bool,int);
	//rsi
	int getrs_Index(int);
	void setrs_Index(int,int);
	//
	int checkBuffer(int);
	int insertBuffer(int,int);
	void updateBuffer(int,int);
	int lruReplace();
	void updateLruIndex(int);
	int onebPrediction(int);
private:
	vector<BranchNode> element;
	int capacity;
	int nodeNum;
};
#endif