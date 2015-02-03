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
}//IF 时间
int ReorderNode::getisClock(){
	return Instruction.getisClock();
}//Issue 时间	
int ReorderNode::getexeClock(){
	return Instruction.getexeClock();
}//execute时间
int ReorderNode::getwbClock(){
	return Instruction.getwbClock();
}//write back时间

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
}//IF 时间
void ReorderNode::setisClock(int isc){
	Instruction.setisClock(isc);
}//Issue 时间	
void ReorderNode::setexeClock(int exec){
	Instruction.setexeClock(exec);
}//execute时间
void ReorderNode::setwbClock(int wbc){
	 Instruction.setwbClock(wbc);
}//write back时间