#include"BranchTargetBuffer.h"

//Constructor

BranchNode::BranchNode(){
	   setAdd(-1);
	   setTar(-1);
	   settrueTar(-1);
	   setTakenFlag(-1);
	   setlruIndex(1);
	   setupdate_Flag(false);
};


//Get Function
int BranchNode::getAdd(){
	return address;
}
int BranchNode::getTar(){
	return Tar;
}
int BranchNode::gettrueTar(){
	return trueTar;
}
int BranchNode::getTakenFlag(){
	return takenFlag;
}
int BranchNode::getlruIndex(){
	return lruIndex;
}
int BranchNode::getrs_Index(){
	return rs_index;
}	
bool BranchNode::getupdate_Flag(){
	return update_Flag;
}

//Set Function
void BranchNode::setAdd(int pc){
	address=pc;
}
void BranchNode::setTar(int theTar){
	Tar=theTar;
}
void BranchNode::settrueTar(int theTar){
	trueTar=theTar;
}
void BranchNode::setTakenFlag(int flag){
	takenFlag=flag;
}
void BranchNode::setlruIndex(int index){
	lruIndex=index;
}
void BranchNode::setrs_Index(int rsi){
	rs_index=rsi;
}
void BranchNode::setupdate_Flag(bool upf){
	update_Flag=upf;
}

///BranchTargetBuffer


BranchTargetBuffer::BranchTargetBuffer(){}
BranchTargetBuffer::BranchTargetBuffer(int c){
	element.resize(c);
	capacity=c;
	nodeNum=0;
}
BranchNode BranchTargetBuffer::getNode(int index){
	return element[index];
}
int BranchTargetBuffer::getNodeNum(){
	return nodeNum;
}
//trueTar
int BranchTargetBuffer::gettrueTar(int index){
	return element[index].gettrueTar();
}

void BranchTargetBuffer::settrueTar(int tt,int index){
	element[index].settrueTar(tt);
}

//upf
bool BranchTargetBuffer::getupdate_Flag(int index){
	return element[index].getupdate_Flag();
}
void BranchTargetBuffer::setupdate_Flag(bool upf,int index){
	element[index].setupdate_Flag(upf);
}
//
//rsi
int BranchTargetBuffer::getrs_Index(int index){
	return element[index].getrs_Index();
}

void BranchTargetBuffer::setrs_Index(int rsi,int index){
	return element[index].setrs_Index(rsi);
}
//
int BranchTargetBuffer::checkBuffer(int PC){
	int index=-1;
	for(int i=0;i<nodeNum;i++){
		if(element[i].getAdd()==PC){
			index=i;
		}
	}
	return index;
}

int BranchTargetBuffer::insertBuffer(int PC,int tarPC){
	int index=checkBuffer(PC);
	if(index==-1){
		index=lruReplace();
		element[index].setAdd(PC);
		element[index].setTar(tarPC);
		nodeNum++;}
	updateLruIndex(index);
	return index;
}

void BranchTargetBuffer::updateBuffer(int add,int trueflag){
	for(int i=0;i<capacity;i++){
		if(element[i].getAdd()==add){
				element[i].setTakenFlag(trueflag);
			}
		   }
}
int BranchTargetBuffer::lruReplace(){
	int temp=-1;
	int index=-1;
		for(int i=0;i<capacity;i++){
			if(element[i].getlruIndex()>temp){
				temp=element[i].getlruIndex();}
		   }
		for(int j=0;j<capacity;j++){
			if(element[j].getlruIndex()==temp){
				index=j;
				break;}
		    }   
	return index;
}
void BranchTargetBuffer::updateLruIndex(int index){
	for(int i=0;i<capacity;i++){
		element[i].setlruIndex(element[i].getlruIndex()+1);
		if(i==index)element[i].setlruIndex(-1);
	}
}
int BranchTargetBuffer::onebPrediction(int index){
	return element[index].getTakenFlag();
}