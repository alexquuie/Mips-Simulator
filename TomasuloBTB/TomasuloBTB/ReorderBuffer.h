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
	int getifClock();//IF ʱ��
	int getisClock();//Issue ʱ��	
	int getexeClock();//executeʱ��
	int getwbClock();//write backʱ��

	//Set Function
	void setBusyState(bool);
	void setReady(bool);
	void setInstruction(MipsInstruction);
	void setDestination(int);
	void setValue(int);
	//setclock
	void setifClock(int);//IF ʱ��
	void setisClock(int);//Issue ʱ��	
	void setexeClock(int);//executeʱ��
	void setwbClock(int);//write backʱ��

private:
	//int Entry;
	bool Busy;
	bool Ready;
	MipsInstruction Instruction;
	int Destination;
	int Value;
};

#endif