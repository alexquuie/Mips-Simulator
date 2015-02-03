#ifndef REORDERBUFFER_H
#define REORDERBUFFER_H
#include"MipsInstruction.h"
using namespace std;

class ReorderNode{
public:
	ReorderNode();
	ReorderNode(MipsInstruction);
	ReorderNode(const ReorderNode&);
	//Get Function
	bool checkBusy();
	bool checkReady();
	MipsInstruction getInstruction();
	int getDestination();
	int getValue();
	//getclock
	int getifClock();//IF 时间
	int getisClock();//Issue 时间	
	int getexeClock();//execute时间
	int getwbClock();//write back时间

	//Set Function
	void setBusyState(bool);
	void setReady(bool);
	void setInstruction(MipsInstruction);
	void setDestination(int);
	void setValue(int);
	//setclock
	void setifClock(int);//IF 时间
	void setisClock(int);//Issue 时间	
	void setexeClock(int);//execute时间
	void setwbClock(int);//write back时间

private:
	//int Entry;
	bool Busy;
	bool Ready;
	MipsInstruction Instruction;
	int Destination;
	int Value;
};

#endif