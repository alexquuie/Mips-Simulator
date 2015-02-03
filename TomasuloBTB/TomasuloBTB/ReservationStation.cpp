#include"MipsInstruction.h"
#include"ReservationStation.h"

//Constructor
ReservationNode::ReservationNode(){
	setBusy(false);
	//setVjFlag(false);
	//setVkFlag(false);
	//setAFlag(false);	
	setDone(false);
	setVj(0);
	setVk(0);
	setQj(0);//ReorderBufferNo.
	setQk(0);//ReorderBufferNo.
	setDest(0);//ReorderBufferNo.
	setA(0);
	setA(0);
	setResult(0);
	setnextStep("");
};

ReservationNode::ReservationNode(MipsInstruction ins){
	Instruction=ins;
	setOpcode(ins.getInstruction());
	setBusy(false);
	//setVjFlag(false);
	//setVkFlag(false);
	//setAFlag(false);	
	setDone(false);
	setVj(0);
	setVk(0);
	setQj(0);//ReorderBufferNo.
	setQk(0);//ReorderBufferNo.
	setDest(0);//ReorderBufferNo.
	setA(0);
	setResult(0);
	setnextStep("");
	if(ins.getRegDFlag())setDest(ins.getRegD());
};


ReservationNode::ReservationNode(const ReservationNode& rs){
	Instruction=rs.Instruction;
	opcode=rs.opcode;
	Busy=rs.Busy;
	Vj=rs.Vj;
	//VjFlag=rs.VjFlag;
	Vk=rs.Vk;
	//VkFlag=rs.VkFlag;
	Qj=rs.Qj;//ReorderBufferNo.
	Qk=rs.Qk;//ReorderBufferNo.
	Destination=rs.Destination;//ReorderBufferNo.
	A=rs.A;
	//AFlag=rs.AFlag;
	Done=rs.Done;
	result=rs.result;
	nextStep=rs.nextStep;
}

//Get Function
MipsInstruction ReservationNode::getInstruction(){
	return Instruction;
}
string ReservationNode::getOpcode(){
	return opcode;
}

bool ReservationNode::checkBusy(){
	return Busy;
}

int ReservationNode::getVj(){
	return Vj;
}
//bool ReservationNode::getVjFlag(){
//	return VjFlag;
//}
int ReservationNode::getVk(){
	return Vk;
}
//bool ReservationNode::getVkFlag(){
//	return VkFlag;
//}
int ReservationNode::getQj(){
	return Qj;
}

int ReservationNode::getQk(){
	return Qk;
}

int ReservationNode::getDest(){
	return Destination;
}

int ReservationNode::getA(){
	return A;
}
//bool ReservationNode::getAFlag(){
//	return AFlag;
//}
int ReservationNode::getResult(){
	return result;
}
string ReservationNode::checknextStep(){
return nextStep;
}

bool ReservationNode::checkDone(){
	return Done;
}

//getclock
int ReservationNode::getifClock(){
	return Instruction.getifClock();
}//IF 时间
int ReservationNode::getisClock(){
	return Instruction.getisClock();
}//Issue 时间	
int ReservationNode::getexeClock(){
	return Instruction.getexeClock();
}//execute时间
int ReservationNode::getwbClock(){
	return Instruction.getwbClock();
}//write back时间

//Set Function
void ReservationNode::setOpcode(string Ins){
	opcode=Ins;
}

void ReservationNode::setBusy(bool B){
	Busy=B;
}

void ReservationNode::setVj(int V){
	Vj = V;
}

//void ReservationNode::setVjFlag(bool b){
//	VjFlag=b;
//}

void ReservationNode::setVk(int V){
	Vk = V;
}

//void ReservationNode::setVkFlag(bool b){
//	VkFlag=b;
//}

void ReservationNode::setQj(int Q){
	Qj = Q;
}

void ReservationNode::setQk(int Q){
	Qk = Q;
}

void ReservationNode::setDest(int D){
	Destination = D;
}

void ReservationNode::setA(int Add){
	A = Add;
}

//void ReservationNode::setAFlag(bool b){
//	A=b;
//}
void ReservationNode::setResult(int r){
	result=r;
}
void ReservationNode::setDone(bool b){
	Done=b;
}
void ReservationNode::setnextStep(string s){
nextStep=s;
}

//setclock
void ReservationNode::setifClock(int ifc){
	Instruction.setifClock(ifc);
}//IF 时间
void ReservationNode::setisClock(int isc){
	Instruction.setisClock(isc);
}//Issue 时间	
void ReservationNode::setexeClock(int exec){
	Instruction.setexeClock(exec);
}//execute时间
void ReservationNode::setwbClock(int wbc){
	 Instruction.setwbClock(wbc);
}//write back时间

void ReservationNode::ALUExecute(map<int,MipsInstruction> Mem){
	int res=0;
	string opcode=Instruction.getOperation();

	//FP Operation
	if(opcode=="ADDI"){
		res = Vj+Instruction.getImorOffset();
	} 

	if(opcode=="ADDIU"){
		res = Vj+Instruction.getImorOffset();
	} 

	if(opcode=="SLT"){
		if(Vj<Vk)res = 1;
		else res = 0;
	} 
	if(opcode=="SLTI"){
		if(Vj<Instruction.getImorOffset())res = 1;
		else res = 0;
	} 
	if(opcode=="SLTU"){
		if(Vj<Vk)res = 1;
		else res = 0;
	} 
	if(opcode=="SLL"){
		res = Vk*pow(2.0,Instruction.getImorOffset());
	} 
	if(opcode=="SRL"){
		res = Vk/pow(2.0,Instruction.getImorOffset());
	} 
	if(opcode=="SRA"){
		res = Vk/pow(2.0,Instruction.getImorOffset());
	} 
	if(opcode=="SUB"){
		res = Vj-Vk;
	}  
	if(opcode=="SUBU"){
		res = Vj-Vk;
	}  
	if(opcode=="ADD"){
		res = Vj+Vk;
	}  
	if(opcode=="ADDU"){
		res = Vj+Vk;
	}  
	if(opcode=="AND"){
		res=(Vj&0xffffffff)&(Vk&0xffffffff);
	}  
	if(opcode=="OR"){
		res=(Vj&0xffffffff)|(Vk&0xffffffff);
	}  
	if(opcode=="XOR"){
		res=(Vj&0xffffffff)^(Vk&0xffffffff);
	}   
	if(opcode=="NOR"){
		res=~(Vj&0xffffffff)|(Vk&0xffffffff);
	}   
	//Branch
	if(opcode=="J"){
		res=1;
	} 
	if(opcode=="BEQ"){
		if(Vj==Vk) res=1;
		else res=0;
	} 
	if(opcode=="BNE"){
		if(Vj!=Vk) res=1;
		else res=0;
	} 
	if(opcode=="BGEZ"){
		if(Vj>=0) res=1;
		else res=0;
	} 
	if(opcode=="BGTZ"){
		if(Vj>0) res=1;
		else res=0;
	} 
	if(opcode=="BLEZ"){
		if(Vj<=0) res=1;
		else res=0;
	} 
	if(opcode=="BLTZ"){
		if(Vj<0) res=1;
		else res=0;
	} 

//	setDone(true);
	result=res;
}
