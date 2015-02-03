#include"RegisterStatus.h"

//class RegisterNode
RegisterNode::RegisterNode(){
	ReorderNo=-1;
	temporalValue=0;
	Busy=false;
}
RegisterNode::RegisterNode(const RegisterNode& reg){
	ReorderNo=reg.ReorderNo;
	temporalValue=reg.temporalValue;
	Busy=reg.Busy;
}
//Get Function	
int RegisterNode::getReorderNo(){
	return ReorderNo;
}

bool RegisterNode::getBusy(){
	return  Busy;
}

int RegisterNode::getTemporalValue(){
	return temporalValue;
}

//Set Function
void RegisterNode::setReorderNo(int No){
	ReorderNo=No;
}

void RegisterNode::setBusy(bool S){
	Busy=S;
}

void RegisterNode::setTemporalValue(int v){
	temporalValue=v;
}

RegisterStatus::RegisterStatus(int c){
	element.resize(c);
	capacity=c;
}
	//Get Function	
int RegisterStatus::getReorderNo(int index){
	return element[index].getReorderNo();
}
bool RegisterStatus::getBusy(int index){
	return element[index].getBusy();
}
int RegisterStatus::getTemporalValue(int index){
	return element[index].getTemporalValue();
}

	//Set Function
void RegisterStatus::setReorderNo(int No,int index){
	element[index].setReorderNo(No);
}
void RegisterStatus::setBusy(bool S,int index){
	element[index].setBusy(S);
}
void RegisterStatus::setTemporalValue(int v,int index){
	element[index].setTemporalValue(v);
}