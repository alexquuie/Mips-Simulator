#include"MipsInstruction.h"
#include"ReorderBuffer.h"

//Constructor
ReorderNode::ReorderNode(){}

ReorderNode::ReorderNode(MipsInstruction T){
	setInstruction(T);
	if(T.getRegDFlag()){
		setDestination(T.getRegD());
	};
	setBusyState(false);
	setReady(false);
};
ReorderNode::ReorderNode(const ReorderNode& tmp){
	Busy=tmp.Busy;
	Ready=tmp.Ready;
	Instruction=tmp.Instruction;
	Destination=tmp.Destination;
	Value=tmp.Value;
}
//Get Function
bool ReorderNode::checkBusy(){
	return Busy;
}


bool ReorderNode::checkReady(){
	return Ready;
}

MipsInstruction ReorderNode::getInstruction(){
	return Instruction;
}

int ReorderNode::getDestination(){
	return Destination;
}

int ReorderNode::getValue(){
	return Value;
}
//getclock
int ReorderNode::getifClock(){
	return Instruction.getifClock();
}//IF ʱ��
int ReorderNode::getisClock(){
	return Instruction.getisClock();
}//Issue ʱ��	
int ReorderNode::getexeClock(){
	return Instruction.getexeClock();
}//executeʱ��
int ReorderNode::getwbClock(){
	return Instruction.getwbClock();
}//write backʱ��

//Set Function
void ReorderNode::setBusyState(bool B){
	Busy=B;
}

void ReorderNode::setReady(bool R){
	Ready=R;
}
void ReorderNode::setInstruction(MipsInstruction Ins){
	Instruction=Ins;
}


void ReorderNode::setDestination(int Des){
	Destination = Des;
}

void ReorderNode::setValue(int v){
	Value = v;
}
//setclock
void ReorderNode::setifClock(int ifc){
	Instruction.setifClock(ifc);
}//IF ʱ��
void ReorderNode::setisClock(int isc){
	Instruction.setisClock(isc);
}//Issue ʱ��	
void ReorderNode::setexeClock(int exec){
	Instruction.setexeClock(exec);
}//executeʱ��
void ReorderNode::setwbClock(int wbc){
	 Instruction.setwbClock(wbc);
}//write backʱ��