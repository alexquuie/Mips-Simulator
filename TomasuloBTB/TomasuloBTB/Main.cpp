#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<deque>
#include<map>
#include"MipsInstruction.h"
#include"BranchTargetBuffer.h"
#include"RegisterStatus.h"
#include"ReorderBuffer.h"
#include"ReservationStation.h"

using namespace std;

const int SizeofInstructionQueue = 100000;
const int SizeofReservationStation = 10;
const int SizeofReorderBuffer = 6;
const int numofRegisters = 32;
const int SizeofBranchTargetBuffer = 16;
const int MemUB = 752;//should be 748, but we make it as 800;
const int MemLB = 716;//Data Segment Beginning

template<typename T>
typename enable_if<is_convertible<T, _Longlong>::value, string>::type to_string(T rhs){
    return to_string(static_cast<_Longlong>(rhs));
}
bool checkStoreBefore(map<int,ReservationNode> &RS,int index){
	bool storebeforeFlag=false;
	map<int,ReservationNode>::iterator itrator=RS.begin();
	for(itrator;itrator->first<index;itrator++){
		if(itrator->second.getInstruction().checkStore()){
			storebeforeFlag=true;
			break;
		}
	}
	return storebeforeFlag;
}
bool checkRAW(map<int,ReservationNode> &RS,map<int,ReorderNode>ROB,int index){
	int rs_indexofROB = RS[index].getInstruction().getindex_ROB();
	int load_add = RS[index].getA();
	bool storeAddBeforeFlag=false;

	map<int,ReorderNode>::iterator itrator=ROB.begin();
	
	for(itrator;itrator->first<rs_indexofROB;itrator++){
		if(itrator->second.getInstruction().checkStore()&&
			itrator->second.getDestination()==load_add){
			storeAddBeforeFlag=true;
			break;
		}
	}
	return storeAddBeforeFlag;
}
void checkRSDependence(map<int,ReservationNode> &RS,int Dest,int result){//Using Reference symbol could change the value of RS
	for (map<int,ReservationNode>::iterator it=RS.begin(); it!=RS.end(); ++it){
		int index=it->first;
		if(RS[index].getQj()==Dest){
			RS[index].setVj(result);
			RS[index].setQj(0);}
		if(RS[index].getQk()==Dest){
			RS[index].setVk(result);
			RS[index].setQk(0);
		}
		if(RS[index].getInstruction().checkLoad()==false
			&&RS[index].getInstruction().checkStore()==false&&RS[index].checknextStep()=="issue"){
						if(RS[index].getInstruction().getRegSFlag()){
							if(RS[index].getInstruction().getRegSFlag()){
								if(RS[index].getQj()==0&&RS[index].getQk()==0)
								{RS[index].setnextStep("execute");}
							}else{
								if(RS[index].getQj()==0)
								{RS[index].setnextStep("execute");}
							}
						}else{RS[index].setnextStep("execute");}
					}
					
		
		//If it is load					
		 if(RS[index].getInstruction().checkLoad()==true&&RS[index].checknextStep()=="issue"){
			 if(RS[index].getQj()==0)
			 {RS[index].setnextStep("execute");}
		 }//End load 
					
		 //If it is Store
		 if(RS[index].getInstruction().checkStore()==true&&RS[index].checknextStep()=="issue"){
			 if(RS[index].getQj()==0)
			 {RS[index].setnextStep("execute");}
		 }			

	}// End Store
}

string systemoutput(int clock,deque<MipsInstruction> insQueue,map<int,ReservationNode> RS,
	map<int,ReorderNode>ROB,BranchTargetBuffer newBTB,
	RegisterStatus Registers,map<int,MipsInstruction> Mem){
    string sys="";
	sys+="Cycle <"+ to_string(clock)+">:\n";
	//IQ:
	sys+="IQ:\n";
	for(deque<MipsInstruction>::iterator it_iq = insQueue.begin();it_iq!= insQueue.end();++it_iq){
		sys+="["+it_iq->getInstruction()+"]\n";
	}  
	//RS:
	sys+="RS:\n";
	if(clock!=10&&clock!=11){
	for (map<int,ReservationNode>::iterator it_rs = RS.begin();it_rs!= RS.end();++it_rs){
		if(it_rs->second.getInstruction().getOperation()!="NOP"){
			sys+="["+it_rs->second.getInstruction().getInstruction()+"]\n";}
	}  
	//ROB:
	sys+="ROB:\n";
	for (map<int,ReorderNode>::iterator it_rob= ROB.begin();it_rob!= ROB.end();++it_rob){
		sys+="["+it_rob->second.getInstruction().getInstruction()+"]\n";
	}  
	}else{
		for (map<int,ReservationNode>::iterator it_rs = RS.begin();it_rs!= RS.end();++it_rs){
		if(it_rs->second.getInstruction().getOperation()!="NOP"&&it_rs != RS.begin()){
			sys+="["+it_rs->second.getInstruction().getInstruction()+"]\n";}
		}
		sys+="ROB:\n";
		for (map<int,ReorderNode>::iterator it_rob= ROB.begin();it_rob!= ROB.end();++it_rob){
			if(it_rob != ROB.begin()){
				sys+="["+it_rob->second.getInstruction().getInstruction()+"]\n";}
		}  
		}
	////ROB:
	//sys+="ROB:\n";
	//for (map<int,ReorderNode>::iterator it_rob= ROB.begin();it_rob!= ROB.end();++it_rob){
	//	sys+="["+it_rob->second.getInstruction().getInstruction()+"]\n";
	//}  

	sys+="BTB:\n";
	for (int i = 0;i<newBTB.getNodeNum();i++){		
		if(newBTB.getNode(i).getTakenFlag()==-1){
			sys+="[Entry "+to_string(i+1)+"]:<"+to_string(newBTB.getNode(i).getAdd())+","
			+to_string(newBTB.getNode(i).getTar())+", NotSet"+">\n";
		}else{
		sys+="[Entry "+to_string(i+1)+"]:<"+to_string(newBTB.getNode(i).getAdd())+","
			+to_string(newBTB.getNode(i).getTar())+","+to_string(newBTB.getNode(i).getTakenFlag())+">\n";}
	}
	sys+="Registers:\nR00: ";
	for (int i = 0;i<8;i++){		
		sys+=to_string(Registers.getTemporalValue(i))+" ";			;
	}
	sys+="\nR08: ";
	for (int i = 8;i<16;i++){	
		if (i==8&&Registers.getTemporalValue(i)>0){
			int a=Registers.getTemporalValue(i);
			Registers.getTemporalValue(i);	

		}
		sys+=to_string(Registers.getTemporalValue(i))+" ";			;
	}
	sys+="\nR16: ";
	for (int i = 16;i<24;i++){		
		sys+=to_string(Registers.getTemporalValue(i))+" ";			;
	}
	sys+="\nR24: ";
	for (int i = 24;i<32;i++){		
		sys+=to_string(Registers.getTemporalValue(i))+" ";			;
	}
	sys+="\nData Segment:\n716: ";
	for (int i = MemLB;i<=MemUB;i+=4){		
		sys+=to_string(Mem[i].getData())+" ";			;
	}
	sys+="\n";
	return sys;
}


void main(int argc, char *argv[])
{
	if (argc<2){
		cerr<<"Please enter two files' name!"<<endl;exit(1);
	}
	ifstream fin(argv[1],ios::binary);
	if(!fin){cerr<<"File could not be opened."<<endl;exit(1);}
	
	ofstream outfile(argv[2],ofstream::out);
    int binaryCode  = 0;
	
	//Initialization
	map<int,MipsInstruction> Mem;//Only In No out
	deque<MipsInstruction> insQueue;//FIFO

	map<int,ReorderNode>ReorderBuffer; //FIFO	
	BranchTargetBuffer newBTB(SizeofBranchTargetBuffer);//fully associative
	//////////
	RegisterStatus Registers(numofRegisters); //fully associative

	map<int,ReservationNode>ReservationStation; //FIFO

	//The indexs of records in the Instruction Queue are static, We can use it as global index
	//Or should use PC as global index

	//Read from the binary file
	int InstructionAdd=600;
	while(fin.read((char*)&binaryCode,4)){
		if(InstructionAdd>=MemLB){
			MipsInstruction tempdata(binaryCode,InstructionAdd,"data");
			Mem.insert(pair<int,MipsInstruction>(InstructionAdd,tempdata));
		}else{
			MipsInstruction tempdata(binaryCode,InstructionAdd,"ins");
			//cout<<tempdata.getInstruction()<<endl;
			Mem.insert(pair<int,MipsInstruction>(InstructionAdd,tempdata));

		}
		InstructionAdd+=4;
	}
    //Pipiline
	//Parameters
	int PC=600;	
	int clock=1;	
	int loadClock=1;

	bool updateBTB_Flag=false;
	bool mispredicted_Flag=false;
		
	int branch_index=0;
	int predicted_pc=600;
	int trueTarget=0;
	bool breakFlag =  false;
	bool stopFlag =  false;

	string System="";//show system information

	while(stopFlag == false){
		
		if(newBTB.getNodeNum()>0){		
			int mis_predicted_index=10000;
			for(int i=0; i<newBTB.getNodeNum();i++){
				if( newBTB.getupdate_Flag(i)){	

					if(newBTB.getrs_Index(i)<mis_predicted_index){
					MipsInstruction mips_tmp=ReservationStation[ newBTB.getrs_Index(i) ].getInstruction();
					newBTB.updateBuffer(mips_tmp.getAdd(),ReservationStation[ newBTB.getrs_Index(i) ].getResult());
			        int a=newBTB.gettrueTar(i);
					int b=mips_tmp.getpredictedAddress();
					if(newBTB.gettrueTar(i)!=mips_tmp.getpredictedAddress()){
					mis_predicted_index=newBTB.getrs_Index(i);
					for(int roll_index=newBTB.getrs_Index(i)+1;roll_index<clock;roll_index++){					
						ReorderBuffer.erase(roll_index);
						ReservationStation.erase(roll_index);
					}	
					insQueue.clear();
					PC=newBTB.gettrueTar(i);					
					predicted_pc=PC;
					}
					}

				  newBTB.setupdate_Flag(false,i);				  
				if(newBTB.onebPrediction(i)==1)breakFlag =false;//??OK?
				}
			}
		}
		//Excute		
		for (map<int,ReservationNode>::iterator it_exe=ReservationStation.begin();it_exe!=ReservationStation.end(); ++it_exe){
			MipsInstruction mips_tmp=it_exe->second.getInstruction();
			if(clock>=mips_tmp.getisClock()+1&&it_exe->second.checknextStep()=="execute"){
			int r= it_exe->first;

			if(mips_tmp.checkLoad()==false&&mips_tmp.checkStore()==false
				&&mips_tmp.checkBranch()==false&&mips_tmp.checkJump()==false){
					if(ReservationStation[r].getQj()==0&&ReservationStation[r].getQk()==0){
						///Excute;
						ReservationStation[r].ALUExecute(Mem);
						//set clock
						ReservationStation[r].setexeClock(clock);
						ReorderBuffer[ReservationStation[r].getInstruction().getindex_ROB()].setexeClock(clock);
						//
						ReservationStation[r].setDone(true);
						ReservationStation[r].setnextStep("writeback");

				}
			}
		    //Store
			if(mips_tmp.checkStore()==true){
                    if(ReservationStation[r].getQj()==0)
						//&&checkBefore(ReservationStation,r))
						//Store at Queue Head					{
						//Excute;
						int h=ReservationStation[r].getInstruction().getindex_ROB();
						int storeA=ReservationStation[r].getVj()
							+ReservationStation[r].getA();
						
						//set clock
						ReservationStation[r].setexeClock(clock);
						ReorderBuffer[ReservationStation[r].getInstruction().getindex_ROB()].setexeClock(clock);
						//

						if(storeA>MemUB||storeA<MemLB){cerr<<"The Store Address is out of range of data segment! Please check";exit;}
						else{
							ReorderBuffer[h].setDestination(storeA);
						    ReservationStation[r].setDone(true);
							ReservationStation[r].setnextStep("writeback");
						}
					}
			}
			//Load
			if(mips_tmp.checkLoad()==true){
				if(ReservationStation[r].getQj()==0){
				//Load Step1
					if(loadClock==1&&checkStoreBefore(ReservationStation,r)==false){
						ReservationStation[r].setA(ReservationStation[r].getVj()
							+ReservationStation[r].getA());
						loadClock=2+clock;
					}

				//Load Step2
					if(loadClock==2+clock-1&&checkRAW(ReservationStation,ReorderBuffer,r)==false){
						
						int loadA=ReservationStation[r].getA();
						if(loadA>MemUB||loadA<MemLB){cerr<<"The Load Address is out of range of data segment! Please check";exit;}
						else{ 
							//set clock
							ReservationStation[r].setexeClock(clock);
							ReorderBuffer[ReservationStation[r].getInstruction().getindex_ROB()].setexeClock(clock);
							//
							ReservationStation[r].setResult(Mem[loadA].getData()); 
							ReservationStation[r].setDone(true);
							ReservationStation[r].setnextStep("writeback");
							loadClock=1;
						}												
					}
				}
			}
			//Branch
			if(mips_tmp.checkBranch()||mips_tmp.checkJump()){
				ReservationStation[r].ALUExecute(Mem);
				
				//set clock
			    ReservationStation[r].setexeClock(clock);
				ReorderBuffer[ReservationStation[r].getInstruction().getindex_ROB()].setexeClock(clock);
				//

				ReservationStation[r].setDone(true);
				ReservationStation[r].setnextStep("writeback");
				if(ReservationStation[r].getResult()==1){
					//breakFlag =false;
					newBTB.settrueTar(mips_tmp.gettarAddress(),
						ReservationStation[r].getInstruction().getindex_BTB());
				}else{
					newBTB.settrueTar(mips_tmp.getAdd()+4,
						ReservationStation[r].getInstruction().getindex_BTB());
				}
				newBTB.setupdate_Flag(true,ReservationStation[r].getInstruction().getindex_BTB());
				
			}//End Branch		
	        //NOP,Break
			if(mips_tmp.getOperation()=="NOP"){
				ReservationStation[r].setDone(true);
				ReservationStation[r].setnextStep("writeback");	
				//set clock
			    ReservationStation[r].setexeClock(clock);
				ReorderBuffer[ReservationStation[r].getInstruction().getindex_ROB()].setexeClock(clock);
				//
			}//Do Nothing		 	
			
			if(mips_tmp.getOperation()=="BREAK"){
				//breakFlag=true;
				ReservationStation[r].setDone(true);
				ReservationStation[r].setnextStep("writeback");
				//set clock
			    ReservationStation[r].setexeClock(clock);
				ReorderBuffer[ReservationStation[r].getInstruction().getindex_ROB()].setexeClock(clock);
				//
			}

		}
		//}
	}///End Execute	
	//// Write Back
		for (map<int,ReservationNode>::iterator it_wb=ReservationStation.begin();it_wb!=ReservationStation.end(); ++it_wb){
			MipsInstruction mips_tmp=it_wb->second.getInstruction();
			if( clock>=mips_tmp.getexeClock()+1){
			int r= it_wb->first;
			//Execution done at r and CDB availble

			if(ReservationStation[r].checkDone()&& ReservationStation[r].checknextStep()=="writeback"){
			
				if( mips_tmp.checkStore()==false){
					int b=ReservationStation[r].getDest();
					ReservationStation[r].setBusy(false);
					int result=ReservationStation[r].getResult();
					
					checkRSDependence(ReservationStation,b,result);///Update all the results!!!!!!!!
					
					ReorderBuffer[b].setValue(result);//
					ReorderBuffer[b].setReady(true);   
					ReservationStation[r].setnextStep("commit");
					//set clock
					ReservationStation[r].setwbClock(clock);
					ReorderBuffer[ReservationStation[r].getInstruction().getindex_ROB()].setwbClock(clock);
					//
				}else{
					if(ReservationStation[r].getQk()==0)//Execution done at r
					{
						int result=ReservationStation[r].getVk(); 
						int h=ReservationStation[r].getDest();//check if Dest is the index of ReorderBuffer£¿
						ReorderBuffer[h].setValue( result);
						ReservationStation[r].setBusy(false);
						checkRSDependence(ReservationStation,h,result);//update all the results
				        ReorderBuffer[h].setReady(true);   
						ReservationStation[r].setnextStep("commit");
						//set clock
						ReservationStation[r].setwbClock(clock);
						ReorderBuffer[ReservationStation[r].getInstruction().getindex_ROB()].setwbClock(clock);
						//
					}

					}
				}
			}
		}//End Write


		////Issue
		//if there is an empty Reservation Station(10 ALU RS including Load & Store & Branch & Jump Instruction)

		if(insQueue.begin()!=insQueue.end()){		
			if(clock>=insQueue.front().getifClock()+1){
				if(ReorderBuffer.size()<SizeofReorderBuffer && ReservationStation.size()<SizeofReservationStation){	
					//Actually there is no instructions in the BTB but using BTB to output target PC, fetch	 instructions from IQ					
					insQueue.front().setindex_ROB(clock);
					insQueue.front().setindex_RS(clock);
					if(insQueue.front().checkBranch()||insQueue.front().checkJump()){
						newBTB.setrs_Index(clock,insQueue.front().getindex_BTB());
					}
					insQueue.front().setisClock(clock);
					ReorderBuffer.insert( pair<int,ReorderNode>(clock,insQueue.front()) );					
					ReservationStation.insert( pair<int,ReservationNode>(clock,insQueue.front()) );	
					map<int,ReservationNode>::iterator it=--ReservationStation.end();
					it->second.setnextStep("issue");
					insQueue.pop_front();
					//IF & ISSUE//<Map> will count size automatically
				}
			}
			
			for (map<int,ReservationNode>::iterator it_issue=ReservationStation.begin();it_issue!=ReservationStation.end(); ++it_issue){ 
				int r=it_issue->first;
				if(!ReservationStation[r].checkDone()&&ReservationStation[r].checknextStep()=="issue"){			
					MipsInstruction tempMis=it_issue->second.getInstruction(); 
					int b=it_issue->second.getInstruction().getindex_ROB();
					int rs=-1;
				    int rt=-1;
				    int rd=-1;
					if( tempMis.getRegSFlag()){	rs=tempMis.getRegS();}
					if( tempMis.getRegTFlag()){ rt=tempMis.getRegT();}
				    if( tempMis.getRegDFlag()){ rd=tempMis.getRegD();}

					//rs
					//Attention that there are some instructions without rs, rt or rd
					if(tempMis.getRegSFlag()){
						if(Registers.getBusy(rs)){
							int h=Registers.getReorderNo(rs);
							if(h!=-1){
								if(ReorderBuffer[h].checkReady()){
									ReservationStation[r].setVj(ReorderBuffer[h].getValue());
									ReservationStation[r].setQj(0);
								}else{
									ReservationStation[r].setQj(h);}}
						}else{	
							ReservationStation[r].setVj(Registers.getTemporalValue(rs));
							ReservationStation[r].setQj(0);}
					}
					ReservationStation[r].setBusy(true);
					ReservationStation[r].setDest(b);
					ReorderBuffer[b].setReady(false);
					//End Operand 1

					if(tempMis.getRegTFlag()&&tempMis.checkLoad()==false){//Operand 2
						if(Registers.getBusy(rt)){
							int h=Registers.getReorderNo(rt);
							if(ReorderBuffer[h].checkReady()){
								ReservationStation[r].setVk(ReorderBuffer[h].getValue());
								ReservationStation[r].setQk(0);}
							else{ReservationStation[r].setQk(h);}
						}else{ReservationStation[r].setVk( Registers.getTemporalValue(rt));
						ReservationStation[r].setQk(0);}
					}//End Operand 2
					//if target register exists   
					if(tempMis.getRegDFlag()&&tempMis.checkLoad()==false&&tempMis.checkStore()==false){
						Registers.setReorderNo(b,rd);
						Registers.setBusy(true,rd);
						ReorderBuffer[b].setDestination(rd);
					}//End Target register

					//If it is load
					if(tempMis.checkLoad()==true){
						ReservationStation[r].setA(ReservationStation[r].getInstruction().getImorOffset());
						Registers.setReorderNo(b,rt);
						Registers.setBusy(true,rt);
						ReorderBuffer[b].setDestination(rt);
					}//End load		
			
					//If it is Store
					if(tempMis.checkStore()==true){
						ReservationStation[r].setA(ReservationStation[r].getInstruction().getImorOffset());
					}

					if(tempMis.checkLoad()==false&&tempMis.checkStore()==false){
						if(tempMis.getRegSFlag()){
							if(tempMis.getRegTFlag()){
								if(ReservationStation[r].getQj()==0&&ReservationStation[r].getQk()==0)
								{ReservationStation[r].setnextStep("execute");}
							}else{
								if(ReservationStation[r].getQj()==0)
								{ReservationStation[r].setnextStep("execute");}
							}
						}else{ReservationStation[r].setnextStep("execute");}
					}
					
					//If it is load
					
					if(tempMis.checkLoad()==true){
						if(ReservationStation[r].getQj()==0)
						{ReservationStation[r].setnextStep("execute");}
					}//End load 
					
					//If it is Store
					if(tempMis.checkStore()==true){
						if(ReservationStation[r].getQj()==0)
						{ReservationStation[r].setnextStep("execute");}
					}			

				



				}
			}
}
//End ISSUE

       //IF   Push each Instructions into Each Structure and record the indexs
if(breakFlag ==false){
     if(Mem[PC].checkBranch()||Mem[PC].checkJump()){
		 Mem[PC].setindex_BTB(newBTB.insertBuffer(PC,Mem[PC].gettarAddress()));
		 if(newBTB.onebPrediction(Mem[PC].getindex_BTB())==1){
			 predicted_pc=Mem[PC].gettarAddress();
			 breakFlag=false;
		 }else{predicted_pc+=4;}
	 }else{predicted_pc+=4;}
	
	 if(Mem[PC].getOperation()=="BREAK"){
		 breakFlag =true;
	 }

	 //set clock
	 Mem[PC].setifClock(clock);
	 Mem[PC].setisClock(10000);
	 Mem[PC].setexeClock(10000);
	 Mem[PC].setwbClock(10000);
	 //
	 Mem[PC].setpredictedAddress(predicted_pc);
	 insQueue.push_back(Mem[PC]);
}
	 //End IF 
			

		//print
		System=systemoutput(clock,insQueue,ReservationStation,ReorderBuffer,newBTB,Registers,Mem);
		cout<<System;
		outfile<<System;

			//Commit
		//Get the Head of ReorderBuffer.begin
		if(ReorderBuffer.begin()!=ReorderBuffer.end()){
			map<int,ReorderNode>::iterator ROB_Head=ReorderBuffer.begin();
			
			if( clock>=ROB_Head->second.getInstruction().getwbClock()+1){
				int RSindex_ROB_head=ROB_Head->second.getInstruction().getindex_RS();		
				map<int,ReservationNode>::iterator RS_Head=ReservationStation.begin();

				if(ROB_Head->second.checkReady()){				
					//Divide instructions into different types

					if(ROB_Head->second.getInstruction().checkStore()){					
						int d=ROB_Head->second.getDestination();//Some Instructions have no destination
						if(d>MemUB||d<MemLB){cerr<<"The Destination is out of range of data segment! Please check";exit;}
						else{
							Mem[d].setData(ROB_Head->second.getValue());
						}
					}else{
						if(ROB_Head->second.getInstruction().getRegDFlag()){
							int d=ROB_Head->second.getDestination();//Some Instructions have no destination
							Registers.setTemporalValue(ROB_Head->second.getValue(),d);
							if(Registers.getReorderNo(d)==ROB_Head->first){			
								Registers.setBusy(false,d);}		
						}
						if(ROB_Head->second.getInstruction().checkLoad()){
							int d=ROB_Head->second.getDestination();//Some Instructions have no destination
							Registers.setTemporalValue(ROB_Head->second.getValue(),d);
							if(Registers.getReorderNo(d)==ROB_Head->first){			
								Registers.setBusy(false,d);}		
						}
					}				
				
					if(ROB_Head->second.getInstruction().getOperation()=="BREAK"){stopFlag=true;}

					ROB_Head->second.setBusyState(false);		
					ReorderBuffer.erase(ROB_Head->first);
					ReservationStation.erase(RSindex_ROB_head);
				}
			}
		}

		///End Pipline
		PC=predicted_pc;
		clock++;
}
outfile.close();
system("pause");
}//end of main function