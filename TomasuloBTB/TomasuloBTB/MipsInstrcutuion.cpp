#include "MipsInstruction.h"

MipsInstruction::MipsInstruction(){
	branchFlag=false;
		jumpFlag=false;
	    loadFlag=false;
	    storeFlag=false;
	    RegDFlag=false;
	    RegSFlag=false;
	    RegTFlag=false;

		RegD=-1;
		RegS=-1;
        RegT=-1;
        Address=0;
	    ImorOffset=0;
		predictedAddress=-1;
	    tarAddress=-1;
		//trueTarget=-1;
	    ImorOffset=0;
		data=-1;

		index_RS=-1;
	    index_ROB=-1;
	    index_BTB=-1;

		ifClock=0;//IF Time
	    isClock=0;//Issue Time
	    exeClock=0;//Execute Time
	    wbClock=0;//Write Back Time

}

MipsInstruction::MipsInstruction(int v,int PC,string s){
	if(s=="ins")
		branchFlag=false;
		jumpFlag=false;
	    loadFlag=false;
	    storeFlag=false;
	    RegDFlag=false;
	    RegSFlag=false;
	    RegTFlag=false;

		RegD=-1;
		RegS=-1;
        RegT=-1;
        Address=PC;
	    ImorOffset=0;
		predictedAddress=-1;
	    tarAddress=-1;
		//trueTarget=-1;

	    ImorOffset=0;
		data=-1;
		index_RS=-1;
	    index_ROB=-1; 
		index_BTB=-1;

		ifClock=0;//IF Time
	    isClock=0;//Issue Time
	    exeClock=0;//Execute Time
	    wbClock=0;//Write Back Time

		v=big_endian2little_endian(v);
		bitset<32> chain(v);
		BinaryCode = chain.to_string();
		codeReco(BinaryCode);
	if(s=="data"){
		branchFlag=false;
		jumpFlag=false;
	    loadFlag=false;
	    storeFlag=false;
	    RegDFlag=false;
	    RegSFlag=false;
	    RegTFlag=false;
        index_RS=-1;
	    index_ROB=-1;
		index_BTB=-1;

		RegD=-1;
		RegS=-1;
        RegT=-1;
        Address=PC;
		predictedAddress=-1;
	    tarAddress=-1;
		//trueTarget=-1;

	    ImorOffset=0;
		
		ifClock=0;//IF Time
	    isClock=0;//Issue Time
	    exeClock=0;//Execute Time
	    wbClock=0;//Write Back Time

		v=big_endian2little_endian(v);
		bitset<32> chain(v);
		BinaryCode = chain.to_string();
		data=binary_to_decimal(BinaryCode);	
		}

}

MipsInstruction::MipsInstruction(const MipsInstruction& theIns){
	BinaryCode=theIns.BinaryCode;
	RegD=theIns.RegD;
	RegS=theIns.RegS;
	RegT=theIns.RegT;

	branchFlag=theIns.branchFlag;
	jumpFlag=theIns.jumpFlag;
	loadFlag=theIns.loadFlag;
	storeFlag=theIns.storeFlag;
	RegDFlag=false;
	RegSFlag=false;
	RegTFlag=false;
	Address=theIns.Address;
	ifClock=theIns.ifClock;//IF Time
	isClock=theIns.isClock;//Issue Time
	exeClock=theIns.exeClock;//Execute Time
	wbClock=theIns.wbClock;//Write Back Time
	
	predictedAddress=theIns.predictedAddress;
	tarAddress=theIns.tarAddress;
	//trueTarget=theIns.trueTarget;

	ImorOffset=theIns.ImorOffset;
	data=theIns.data;
	index_RS=theIns.index_RS;
	index_ROB=theIns.index_ROB;
	index_BTB=theIns.index_BTB;
	
	ImorOffset=theIns.ImorOffset;
	if(data<0)codeReco(BinaryCode);	
}

template<typename T>
typename enable_if<is_convertible<T, _Longlong>::value, string>::type to_string(T rhs){
    return to_string(static_cast<_Longlong>(rhs));
}
int MipsInstruction::binary_to_decimal(const string &str){
	int len = str.length();
	int sum = 0;
	if(len>32){
		cerr<<"Error, the string is too long!"<<endl; 
		return 0;
	} 
	else
	for(int i=0;i<len;i++){
		if(str[len-i-1]=='1')sum+=(int)pow(2.0,i);
	}
	return sum;
}

int MipsInstruction::signed_binary_to_decimal(const string &str){
	int len = str.length();
	int sum = 0;
	if(len>32){
		cerr<<"Error, the string is too long!"<<endl; 
		return 0;
	} 
	else
	{		
		int sum_tmp=0;
		for(int i=0;i<len-1;i++){
			if(str[len-i-1]=='1')sum_tmp+=(int)pow(2.0,i);
		}
		if(str[0]=='1'){
			sum=sum_tmp-pow(2.0,len-1);}
		else sum=sum_tmp;
		return sum;
	}	
}


int MipsInstruction::big_endian2little_endian(int i)
{
    return((i&0xff)<<24)+((i&0xff00)<<8)+((i&0xff0000)>>8)+((i>>24)&0xff);
}

void MipsInstruction::codeReco(string chain){		
	opcode=chain.substr(0,6);
	rs=chain.substr(6,5);
	rt=chain.substr(11,5);
	rd=chain.substr(16,5);
	rh=chain.substr(21,5);	
	special=chain.substr(26,6);
	string res_str;
	
	// string::compare return 0 when two strings are equal;	
	if(opcode.compare("000000")==0){
		//opcode is "000000"
		if(special.compare("001101")==0){
			res_str="BREAK";
			operation="BREAK";
		}
		if(rh.compare("00000")==0&&special.compare("101010")==0){
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			RegD=binary_to_decimal(rd);
			RegDFlag=true;
	        RegSFlag=true;
	        RegTFlag=true;

			res_str="SLT R"+to_string(RegD)+", R"+
				to_string(RegS)+", R"+to_string(RegT);
			operation="SLT";
			
		}
		if(rh.compare("00000")==0&&special.compare("101011")==0){
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			RegD=binary_to_decimal(rd);
			RegDFlag=true;
	        RegSFlag=true;
	        RegTFlag=true;

			res_str="SLTU R"+to_string( RegD)+", R"+
				to_string( RegS)+", R"+to_string( RegT);
			operation="SLTU";
		}
		//
		if(rs.compare("00000")==0&&rt.compare("00000")==0&&rd.compare("00000")==0
			&&rh.compare("00000")==0&&special.compare("000000")==0){
				res_str="NOP";
				operation="NOP";
		}
		else if(rs.compare("00000")==0&& special.compare("000000")==0 &&!(rt.compare("00000")==0&&rd.compare("00000")==0
			&&rh.compare("00000")==0 ) ){
				RegD=binary_to_decimal(rd);
			    RegS=binary_to_decimal(rt);
				RegDFlag=true;
	            RegSFlag=true;
				ImorOffset=binary_to_decimal(rh);
				res_str="SLL R"+to_string( RegD)+", R"+
					to_string( RegS)+", #"+to_string(ImorOffset);		
				operation="SLL";
		}
		
		if(special.compare("000010")==0){
			RegD=binary_to_decimal(rd);
			RegS=binary_to_decimal(rt);
			RegDFlag=true;
			RegSFlag=true;
			ImorOffset=binary_to_decimal(rh);

			res_str="SRL R"+to_string( RegD)+", R"+
				to_string(RegS)+", #"+to_string( ImorOffset );			
			operation="SRL";
		}
		if(special.compare("000011")==0){
			RegD=binary_to_decimal(rd);
			RegS=binary_to_decimal(rs);
			RegDFlag=true;
			RegSFlag=true;
			ImorOffset=binary_to_decimal(rh);

			res_str="SRA R"+to_string( RegD)+", R"+
				to_string(RegS)+", #"+to_string( ImorOffset );	
			operation="SRA";
		}
		if(rh.compare("00000")==0&&special.compare("100010")==0){
			RegD=binary_to_decimal(rd);
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			RegDFlag=true;
			RegSFlag=true;
			RegTFlag=true;

			res_str="SUB R"+to_string(RegD)+", R"+
				to_string(RegS)+", R"+to_string(RegT);
			operation="SUB";
		}
		if(rh.compare("00000")==0&&special.compare("100011")==0){
			RegD=binary_to_decimal(rd);
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			RegDFlag=true;
			RegSFlag=true;
			RegTFlag=true;

			res_str="SUBU R"+to_string(RegD)+", R"+
				to_string(RegS)+", R"+to_string(RegT);
			operation="SUBU";
		}
		if(rh.compare("00000")==0&&special.compare("100000")==0){
			RegD=binary_to_decimal(rd);
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			RegDFlag=true;
			RegSFlag=true;
			RegTFlag=true;

			res_str="ADD R"+to_string( RegD )+", R"+
				to_string( RegS )+", R"+to_string( RegT );		
			operation="ADD";
		}
		if(rh.compare("00000")==0&&special.compare("100001")==0){
			RegD=binary_to_decimal(rd);
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			RegDFlag=true;
			RegSFlag=true;
			RegTFlag=true;

			res_str="ADDU R"+to_string( RegD)+", R"+
				to_string( RegS )+", R"+to_string( RegT );	
			operation="ADDU";
		}
		if(rh.compare("00000")==0&&special.compare("100100")==0){
			RegD=binary_to_decimal(rd);
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			RegDFlag=true;
			RegSFlag=true;
			RegTFlag=true;

			res_str="AND R"+to_string( RegD )+", R"+
				to_string( RegS )+", R"+to_string( RegT );
			operation="AND";
		}
		if(rh.compare("00000")==0&&special.compare("100101")==0){
			RegD=binary_to_decimal(rd);
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			RegDFlag=true;
			RegSFlag=true;
			RegTFlag=true;

			res_str="OR R"+to_string( RegD )+", R"+
				to_string(RegS)+", R"+to_string(RegT);
			operation="OR";
		}
		if(rh.compare("00000")==0&&special.compare("100110")==0){
			RegD =binary_to_decimal(rd);
			RegS =binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			RegDFlag=true;
			RegSFlag=true;
			RegTFlag=true;

		    res_str="XOR R"+to_string( RegD)+", R"+
				to_string( RegS )+", R"+to_string( RegT );	
			operation="XOR";
		}
		if(rh.compare("00000")==0&&special.compare("100111")==0){
			RegD=binary_to_decimal(rd);
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			RegDFlag=true;
			RegSFlag=true;
			RegTFlag=true;

			res_str="NOR R"+to_string( RegD)+", R"+
				to_string( RegS )+", R"+to_string(RegT);
			operation="NOR";
		}
	}
	else if(opcode.compare("000010")==0){
		//opcode is "000010"
		//!!!
		tarAddress=binary_to_decimal(rs+rt+rd+rh+special)*4;
		res_str="J #"+to_string(tarAddress);
		jumpFlag=true;
		operation="J";
	}
	else{
		//opcode is arbitrary;
		if(opcode.compare("101011")==0){
			//!!!!!!!
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			ImorOffset= binary_to_decimal(rd+rh+special);
			RegTFlag=true;
			RegSFlag=true;

			res_str="SW R"+to_string(RegT)+", "
				+to_string( ImorOffset )+"(R"
				+to_string( RegS)+")";	
			storeFlag = true;
		}
	    else if(opcode.compare("100011")==0){
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);
			ImorOffset= binary_to_decimal(rd+rh+special);
			RegSFlag=true;
			RegTFlag=true;

			res_str="LW R"+to_string(RegT)+", "
				+to_string( ImorOffset )+"(R"
				+to_string( RegS)+")";	
			loadFlag = true;
			operation="LW";
		}
		else if(opcode.compare("000100")==0){
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);

			RegSFlag=true;
			RegTFlag=true;

			tarAddress = Address+signed_binary_to_decimal(rd+rh+special)*4+4; 
			
			res_str="BEQ R"+to_string(RegS)+", R"
				+to_string( RegT )+", #"
				+to_string( signed_binary_to_decimal(rd+rh+special)*4 );//the 16-bit offset field shifted left 2 bits
			branchFlag = true;
			operation="BEQ";
		}
		else if(opcode.compare("000101")==0){
			RegS=binary_to_decimal(rs);
			RegT=binary_to_decimal(rt);

			RegSFlag=true;
			RegTFlag=true;

			tarAddress = Address+signed_binary_to_decimal(rd+rh+special)*4+4; 
			
			res_str="BNE R"+to_string(RegS)+", R"
				+to_string( RegT )+", #"
				+to_string( signed_binary_to_decimal(rd+rh+special)*4 );
			branchFlag = true;
			operation="BNE";
		}
		else if(opcode.compare("000001")==0 && rt.compare("00001")==0){
			RegS=binary_to_decimal(rs);
			RegSFlag=true;
			
			tarAddress = Address+signed_binary_to_decimal(rd+rh+special)*4+4; 

			res_str="BGEZ R"+to_string(RegS)+", #"
				+to_string( signed_binary_to_decimal(rd+rh+special)*4 );
			branchFlag = true;
			operation="BGEZ";
		}
		else if(opcode.compare("000111")==0 && rt.compare("00000")==0){
			RegS=binary_to_decimal(rs);
			RegSFlag=true;

			tarAddress = Address+signed_binary_to_decimal(rd+rh+special)*4+4; 

			res_str="BGTZ R"+to_string(RegD)+", #"
				+to_string( signed_binary_to_decimal(rd+rh+special)*4 );
			branchFlag = true;
			operation="BGTZ";
		}
		else if(opcode.compare("000110")==0 && rt.compare("00000")==0){
			RegS=binary_to_decimal(rs);
			RegSFlag=true;
			
			tarAddress = Address+signed_binary_to_decimal(rd+rh+special)*4+4; 

			res_str="BLEZ R"+to_string(RegS)+", #"
				+to_string( signed_binary_to_decimal(rd+rh+special)*4 );
			branchFlag = true;
			operation="BLEZ";
		}
		else if(opcode.compare("000001")==0 && rt.compare("00000")==0){
			RegS=binary_to_decimal(rs);
			RegSFlag=true;
			tarAddress = Address+signed_binary_to_decimal(rd+rh+special)*4+4; 

			res_str="BLTZ R"+to_string(RegS)+", #"
				+to_string( signed_binary_to_decimal(rd+rh+special)*4 );
			branchFlag = true;
			operation="BLTZ";
		}
	    else if(opcode.compare("001000")==0){
			RegS=binary_to_decimal(rs);
			RegD=binary_to_decimal(rt);
			RegSFlag=true;
			RegDFlag=true;

			ImorOffset=signed_binary_to_decimal(rd+rh+special);
			
			res_str="ADDI R"+to_string( RegD)+", R"+
					to_string( RegS)+", #"+to_string(ImorOffset);	
			operation="ADDI";
		}
		else if(opcode.compare("001001")==0){
			RegS=binary_to_decimal(rs);
			RegD=binary_to_decimal(rt);
			RegSFlag=true;
			RegDFlag=true;
			ImorOffset=signed_binary_to_decimal(rd+rh+special);
			res_str="ADDIU R"+to_string(RegD)+", R"+
					to_string( RegS)+", #"+to_string( ImorOffset=signed_binary_to_decimal(rd+rh+special) );
			operation="ADDIU";
		}
		else if(opcode.compare("001010")==0){
			RegS=binary_to_decimal(rs);
			RegD=binary_to_decimal(rt);
			RegSFlag=true;
			RegDFlag=true;

			res_str="SLTI R"+to_string(RegD)+", R"+
					to_string(RegS)+", #"+to_string( signed_binary_to_decimal(rd+rh+special));	
			operation="SLTI";
		}
		else{
			cout<<"None"<<endl;
		}
	}
	Instruction=res_str;

	//The end of the function;	
}
//check function
bool MipsInstruction::checkBranch(){
	return branchFlag;
}
bool MipsInstruction::checkJump(){
	return jumpFlag;
}
bool MipsInstruction::checkLoad(){
	return loadFlag;
}
bool MipsInstruction::checkStore(){
	return storeFlag;
}
//get funtion
string MipsInstruction::getInstruction(){
	return Instruction;
}
string MipsInstruction::getBinaryCode(){
	return BinaryCode;
}
string MipsInstruction::getOperation(){
	return operation;
}
int MipsInstruction::getindex_RS(){
	return index_RS;
}
int MipsInstruction::getindex_ROB(){
	return index_ROB;
}
int MipsInstruction::getindex_BTB(){
	return index_BTB;
}

int  MipsInstruction::getRegD(){
	return RegD;
}

int MipsInstruction::getRegS(){
	return RegS;
}

int MipsInstruction::getRegT(){
	return RegT;
}

bool  MipsInstruction::getRegDFlag(){
	return RegDFlag;
}

bool MipsInstruction::getRegSFlag(){
	return RegSFlag;
}

bool MipsInstruction::getRegTFlag(){
	return RegTFlag;
}

int MipsInstruction::getAdd(){
	return Address;
}
int MipsInstruction::getpredictedAddress(){
	return predictedAddress;
}
int MipsInstruction::gettarAddress(){
	return tarAddress;
}
//int  MipsInstruction::gettrueTarget(){
//	return trueTarget;
//}

int MipsInstruction::getImorOffset(){
	return ImorOffset;
}
int MipsInstruction::getData(){
	return data;
}
int MipsInstruction::getifClock(){
	return ifClock;
}//IF Time
int MipsInstruction::getisClock(){
	return isClock;
}//Issue Time
int MipsInstruction::getexeClock(){
	return exeClock;
}//Execute Time
int MipsInstruction::getwbClock(){
	return wbClock;
}//Write Back Time

//set function
void MipsInstruction::setindex_RS(int irs){
	index_RS = irs;
}
void MipsInstruction::setindex_ROB(int irob){
	index_ROB = irob;
}
void MipsInstruction::setindex_BTB(int ibtb){
	index_BTB = ibtb;
}

void MipsInstruction::setData(int d){
	data=d;
}

void MipsInstruction::setAdd(int temp_Add){
	Address=temp_Add;
}

void MipsInstruction::setpredictedAddress(int pda){
	predictedAddress=pda;
}

void MipsInstruction::settarAddress(int tar){
	tarAddress=tar;
}
//void  MipsInstruction::settrueTarget(int tt){
//	trueTarget=tt;
//}
void MipsInstruction::setImorOffset(int temp_Im){
	ImorOffset=temp_Im;
}
void MipsInstruction::setifClock(int ifc){
	ifClock=ifc;
}//IF Time
void MipsInstruction::setisClock(int isc){
	isClock=isc;
}//Issue Time
void MipsInstruction::setexeClock(int exec){
	exeClock=exec;
}//Execute Time
void MipsInstruction::setwbClock(int wbc){
	wbClock=wbc;
}//Write Back Time