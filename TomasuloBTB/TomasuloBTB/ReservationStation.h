#ifndef RESERVATIONSTATION_H
#define RESERVATIONSTATION_H
#include <iostream>
#include<map>
#include <string>
#include<math.h>
#include"MipsInstruction.h"
#include"RegisterStatus.h"
using namespace std;

class ReservationNode{
public:
	ReservationNode();
	ReservationNode(MipsInstruction);
	ReservationNode(const ReservationNode&);
	//Get Function		
	MipsInstruction getInstruction();
	string getOpcode();
	bool checkBusy();
	int getVj();
	//bool getVjFlag();
	int getVk();
	//bool getVkFlag();
	int getQj();
	int getQk();
	int getDest();
	int getA();
	//bool getAFlag();
	int getResult();
	bool checkDone();
	string checknextStep();
	//getclock
	int getifClock();//IF ʱ��
	int getisClock();//Issue ʱ��	
	int getexeClock();//executeʱ��
	int getwbClock();//write backʱ��

	//Set Function
	void setOpcode(string);
	void setBusy(bool);
	void setVj(int);
	//void setVjFlag(bool);
	void setVk(int);
	//void setVkFlag(bool);
	void setQj(int);
	void setQk(int);
	void setDest(int);
	void setA(int);
	//void setAFlag(bool);
	void setResult(int);
	void setDone(bool);
	void setnextStep(string);
	//setclock
	void setifClock(int);//IF ʱ��
	void setisClock(int);//Issue ʱ��	
	void setexeClock(int);//executeʱ��
	void setwbClock(int);//write backʱ��
	//ALU Execute Function
	void ALUExecute(map<int,MipsInstruction>);
private:
	MipsInstruction Instruction;
	string opcode;
	bool Busy;
	int Vj;
	//bool VjFlag;
	int Vk;
	//bool VkFlag;
	int Qj;//ReorderBufferNo.
	int Qk;//ReorderBufferNo.
	int Destination;//ReorderBufferNo.
	int A;
	//bool AFlag;
	string nextStep;
	bool Done;
	int result;
};
#endif