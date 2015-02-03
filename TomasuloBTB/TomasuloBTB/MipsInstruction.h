#ifndef MIPSINSTRUCTION_H
#define MIPSINSTRUCTION_H
#include<iostream>
#include<string>
#include<bitset>
using namespace std;

class MipsInstruction{
public:
	MipsInstruction();
	MipsInstruction(int,int,string);
	MipsInstruction(const MipsInstruction& theIns);
	int binary_to_decimal(const string &);
	int signed_binary_to_decimal(const string &);
	int big_endian2little_endian(int);
	void codeReco(string);
	//check function
	bool checkBranch();
	bool checkJump();
	bool checkLoad();
	bool checkStore();

	//get Function
	string getInstruction();
	string getBinaryCode();
	string getOperation();

	int getindex_RS();
	int getindex_ROB();
	int getindex_BTB();

	int getRegS();
	int getRegT();
	int getRegD();

	bool getRegDFlag();
	bool getRegSFlag();
	bool getRegTFlag();
	//Add
	int getAdd();
	int getpredictedAddress();//Record predictedAddress
	int gettarAddress();
	//int gettrueTarget();//Record True Target Address
	//
	int getImorOffset();
	int getData();
	
	int getifClock();//IF Time
	int getisClock();//Issue Time
	int getexeClock();//Execute Time
	int getwbClock();//Write Back Time

	//set Function
	
	//void setInstruction();
	void setindex_RS(int);
	void setindex_ROB(int);
	void setindex_BTB(int);

	void setifClock(int);//IF Time
	void setisClock(int);//Issue Time
	void setexeClock(int);//Execute Time
	void setwbClock(int);//Write Back Time

	//void setBinaryCode();
	void setData(int);
	void setAdd(int);
	void setpredictedAddress(int);//Record predictedAddress
	void settarAddress(int); //set Target Address
	//void settrueTarget(int);//True Target Address
	void setImorOffset(int);

private:
	string BinaryCode;
	//index
	int index_RS;
	int index_ROB;
	int index_BTB;
	//

	int RegS;
	int RegT;
	int RegD;
	bool RegDFlag;
	bool RegSFlag;
	bool RegTFlag;

	bool branchFlag;
	bool jumpFlag;
	bool loadFlag;
	bool storeFlag;
	int Address;//address of instructions
	int predictedAddress;//Record predictedAddress
	int tarAddress;//target address
//	int trueTarget;//truetarget address


	int ImorOffset;//Instant Address
	int data;//If the Record is data type
	int ifClock;//IF time
	int isClock;//Issue time
	int exeClock;//Execute time
	int wbClock;//write back time

	string operation;//operation
	string opcode;
	string rs;
	string rt;
	string rd;
	string rh;
      string special;
	string Instruction;
};
#endif