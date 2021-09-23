#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <conio.h>

using namespace std;
//Initializing streams for reading and writing files
//   Taking Help from Google, Youtube and etc 
ifstream in;
ofstream file;

//Function Declarations
void Assembler(string);
void Rename(string);
string removespaces(string);
void AInstruction();
void CInstruction();
bool numberextractor(string);
void Comp(string);
void Dest(string);
void Jump(string);
void ReadLabels(string);

//Variables Initialization
string Instruction[42]={"0","1","-1","D","A","!D","!A","-D","-A","D+1","A+1","D-1","A-1","D+A","D-A","A-D","D&A","D|A","M","!M","-M","M+1","M-1","D+M","D-M","M-D","D&M","D|M","M","D","MD","A","AM","AD","AMD","JGT","JEQ","JGE","JLT","JNE","JLE","JMP"};                    
string Value[42]={"101010","111111","111010","001100","110000","001101","110001","001111","110011","011111","110111","001110","110010","000010","010011","000111","000000","010101","110000","110001","110011","110111","110010","000010","010011","000111","000000","010101","001","010","011","100","101","100","111","001","010","011","100","101","110","111"};
string Symbol[1000]={"R0","R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15","SP","LCL","ARG","THIS","THAT","SCREEN","KBD"};
int Address[1000]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,16384,24576};
int LineNumber;
bool Error=false;
string na;
int symbolindex=23,n=16;

                    // READ LABELS FUNCTION
                    //To read all the labels of the program 

void ReadLabels(string filename){                
	ifstream file1; 
	string line;
	int lineno=0;
	file1.open(filename.c_str(),ios::in);		
	if(file1.is_open()){
		while(getline(file1,line)){				
		if(line.find("//") != string::npos)		
			line.erase(line.find("//"));		
		line=removespaces(line);				//Function to remove spacess 
		if(!line.empty()){						
		lineno++;								
		if(line[0]!='(')continue;				
		string label(line.begin()+1,line.begin()+line.find(')'));		//This line seperates out the label and stores it in a variable named label
		Symbol[symbolindex]=label;				
		Address[symbolindex++]=lineno;
		}
	}
}
file1.close();
}
          // NUMBER EXTRACTOR FUNCTION  TURE Or FALSE
bool numberextractor(string num){
	if(atoi(num.c_str())==0)return false;			
	return true;									
}
    // A-INSTRUCTION  FUNCTION
void AInstruction(string code){
	int k=15;
	if (code[0]!='@')return;						
	int binary[16]={0},number;						
	string num(code.begin()+1,code.end());			
	if(num!="0"){
	if(numberextractor(num)==false){				//Calling the numberextracor function 
		for(int i=0;i<symbolindex;i++){				
		if(Symbol[i]==num){							
			number=Address[i];					
			goto no;								//Goto statement
		}
		}
		{
			Symbol[symbolindex]=num;				
			Address[symbolindex++]=number=n++;		
			goto no;								//Goto statement 
		}
	}
}
	number=atoi(num.c_str());						
	no:												
	for(int i=0;number>0;i++){
		int temp;									
		temp=number%2;								
		number=number/2;							//Converting the number to its equivilant 15 bit binary code and saving it in binary array
		binary[k--]=temp;
	}
	for (int i=0;i<16;i++){
		file << binary[i];							//Writing the binary array in file
	}
	file << "\n";									
}
  // C-INSTRUCTION FUNCTION
void CInstruction(string code){
	bool flag=false;								
	if(code[0]=='@')return;							
	for(int i=0;code[i]!=0;i++){					
		if(code[i]=='='){							
		flag=true;									
		string DEST(code.begin(),code.begin()+code.find('=')),COMP(code.begin()+code.find('=')+1,code.end()); 
		Comp(COMP);									//Calling Comp Function
		Dest(DEST);									//Calling Dest Function
		}
		else if(code[i]==';'){						
		flag=true;									
		string COMP(code.begin(),code.begin()+code.find(';')),JUMP(code.begin()+code.find(';')+1,code.end());	//Extracing DEST and COMP from the code for furher processing
		Comp(COMP);									//Calling Comp Function
		Jump(JUMP);									//Calling Jump Function
		}
		if(code[0]=='(')flag=true;					
	}
	if(flag==false){								
		Error=true;									
	}
}

     // COMPUTATION FUNCTION
void Comp(string COMP){
	int a=1;
	int fl=0;
	for(int i=0;i<28;i++){
		if(Instruction[i]==COMP){					
		if(i<18)a=0;								
		file << "111";								
		file << a;									
		file << Value[i]; 
		fl=1;
		}
	}
	if(fl=0) Error=true;							
}
       //  DESTINATION FUNCTION
void Dest(string DEST){
	int fl=0;
	for(int i=28;i<35;i++){
		if(Instruction[i]==DEST){
		file << Value[i];							
		file << "000"; 								
		file << '\n';								
		fl=1;										
		}
	}
	if(fl=0) Error=true;							
}
    //  JUMP  FUNCTION
void Jump(string JUMP){
	int fl=0;
	for(int i=35;i<42;i++){
		if(Instruction[i]==JUMP){
		file <<"000";							
		file << Value[i]; 						
		file <<'\n';							
		fl=1;									
		}
	}
	if(fl=0) Error=true;							
}
           //  OPEN FILE FUNCTION 
void Openfile(string filename){
	string ext=".hack";													
	string name(filename.begin(),filename.begin()+filename.find('.'));	
	na=name+ext;									
	file.open(na.c_str(),ios::out);					
}
     //   SPACE Remover  FUNCTION
	 //If the code contains any spaces or tab characters they will be removed
string removespaces(string s){
	string st="";
	for(int i=0;i<s.length();i++){
		if(s[i]!=' ' && s[i]!='\t')st.push_back(s[i]);		
	}
	return st;
}
    //  ASSEMBLER  FUNCTION
void Assembler(string filename){
		in.open(filename.c_str(),ios::in);					
		string line;										
		Openfile(filename);									
		if(!in.is_open()){
			cout << "\nError Reading File\n";				//If error opening file gives out error and exits the program
			exit(1);
		}
		if(in.is_open()){
		while(getline(in,line)){							//Reading the file line by line
		if(line.find("//") != string::npos)
			line.erase(line.find("//"));					
		line=removespaces(line);							//Calling the removespaces  function to remove spaces
		if(!line.empty()){									
		LineNumber++;										
		AInstruction(line);									//Calling the A Instruction
		CInstruction(line);									//Calling the C Instruction
		if(Error==true){
		cout << "Syntax Error at line no: " << LineNumber << "\n";	
		remove(na.c_str());
		exit(1);
	}
		}
	}
	
}
in.close();													
file.close();												
}

//  SHOW   SYMBOL  TABLE FUNCTION
//Function for shwoing the symbol table
void Showsymboltable(){											
		for(int i=0;i<symbolindex;i++)
		cout << Symbol[i] << "\t\t" << Address[i] << "\n";
}

int main(){
	string name;
	cout << "\n\n\n\t\t\t THE HACK COMPUTER  ASSEMBLER \n\n\n";
	cout << "Enter the filename : ";
	cin >> name;					//Taking filename from the user
	ReadLabels(name);
	Assembler(name);				//Giving it to Assembler Function for further processing
	cout << "~ Press A to Assemble the Code\n~ Press S to view the Symbol Table\n";
	char d=getch();
	if(d=='A' || d=='a')
		cout << "\n\nThe Program Entered  has been Assembled..\n";
	else if(d=='S' || d=='s')
		Showsymboltable();
	else cout << "\n\nThe Program has been Assembled..\n";
}