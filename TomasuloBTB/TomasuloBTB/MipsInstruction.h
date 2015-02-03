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
	int getpredictedAddress();//预测目标地址
	int gettarAddress();
	//int gettrueTarget();//正确目标地址
	//
	int getImorOffset();
	int getData();
	
	int getifClock();//IF 时间
	int getisClock();//Issue 时间	
	int getexeClock();//execute时间
	int getwbClock();//write back时间

	//set Function
	
	//void setInstruction();
	void setindex_RS(int);
	void setindex_ROB(int);
	void setindex_BTB(int);

	void setifClock(int);//IF 时间
	void setisClock(int);//Issue 时间	
	void setexeClock(int);//execute时间
	void setwbClock(int);//write back时间

	//void setBinaryCode();
	void setData(int);
	void setAdd(int);
	void setpredictedAddress(int);//预测目标地址
	void settarAddress(int); //目标地址
	//void settrueTarget(int);//正确目标地址
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
	int Address;//指令地址
	int predictedAddress;//预测目标地址
	int tarAddress;//目标地址
//	int trueTarget;//正确目标地址

	int ImorOffset;//立即地址
	int data;//当他为Data型的时候
	int ifClock;//IF 时间
	int isClock;//Issue 时间	
	int exeClock;//execute时间
	int wbClock;//write back时间

	string operation;//操作
	string opcode;
	string rs;
	string rt;
	string rd;
	string rh;
    string special;
	string Instruction;
};
#endif