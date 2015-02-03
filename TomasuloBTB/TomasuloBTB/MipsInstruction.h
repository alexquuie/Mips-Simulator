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
	int getpredictedAddress();//Ԥ��Ŀ���ַ
	int gettarAddress();
	//int gettrueTarget();//��ȷĿ���ַ
	//
	int getImorOffset();
	int getData();
	
	int getifClock();//IF ʱ��
	int getisClock();//Issue ʱ��	
	int getexeClock();//executeʱ��
	int getwbClock();//write backʱ��

	//set Function
	
	//void setInstruction();
	void setindex_RS(int);
	void setindex_ROB(int);
	void setindex_BTB(int);

	void setifClock(int);//IF ʱ��
	void setisClock(int);//Issue ʱ��	
	void setexeClock(int);//executeʱ��
	void setwbClock(int);//write backʱ��

	//void setBinaryCode();
	void setData(int);
	void setAdd(int);
	void setpredictedAddress(int);//Ԥ��Ŀ���ַ
	void settarAddress(int); //Ŀ���ַ
	//void settrueTarget(int);//��ȷĿ���ַ
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
	int Address;//ָ���ַ
	int predictedAddress;//Ԥ��Ŀ���ַ
	int tarAddress;//Ŀ���ַ
//	int trueTarget;//��ȷĿ���ַ

	int ImorOffset;//������ַ
	int data;//����ΪData�͵�ʱ��
	int ifClock;//IF ʱ��
	int isClock;//Issue ʱ��	
	int exeClock;//executeʱ��
	int wbClock;//write backʱ��

	string operation;//����
	string opcode;
	string rs;
	string rt;
	string rd;
	string rh;
    string special;
	string Instruction;
};
#endif