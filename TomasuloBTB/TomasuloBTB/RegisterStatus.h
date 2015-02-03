#ifndef REGISTERSTATUS_H
#define REGISTERSTATUS_H
#include<iostream>
#include<vector>
#include <string>
using namespace std;

class RegisterNode{
public:
	RegisterNode();
	RegisterNode(const RegisterNode&);
	//Get Function	
	int getReorderNo();
	bool getBusy();
	int getTemporalValue();

	//Set Function
	void setReorderNo(int);
	void setBusy(bool);
	void setTemporalValue(int);
private:
	int ReorderNo;
	int temporalValue;
	bool Busy;
};
class RegisterStatus{
//friend class ReservationStation;
public:
	RegisterStatus(int);
	//Get Function	
	int getReorderNo(int);
	bool getBusy(int);
	int getTemporalValue(int);

	//Set Function
	void setReorderNo(int,int);
	void setBusy(bool,int);
	void setTemporalValue(int,int);
private:
	vector<RegisterNode> element;
	int capacity;
	//bool Busy;
};
#endif