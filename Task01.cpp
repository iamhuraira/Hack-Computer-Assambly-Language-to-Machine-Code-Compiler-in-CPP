#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Hack_Assembler{
    public:
    string instruction[42]={"0","1","-1","D","A","!D","!A","-D","-A","D+1","A+1","D-1","A-1","D+A","D-A","A-D","D&A","D|A","M","!M","-M","M+1","M-1","D+M","D-M","M-D","D&M","D|M","M","D","MD","A","AM","AD","AMD","JGT","JEQ","JGE","JLT","JNE","JLE","JMP"};                    
string value[42]={"101010","111111","111010","001100","110000","001101","110001","001111","110011","011111","110111","001110","110010","000010","010011","000111","000000","010101","110000","110001","110011","110111","110010","000010","010011","000111","000000","010101","001","010","011","100","101","100","111","001","010","011","100","101","110","111"};
     ofstream out;
	 ifstream in;
    Hack_Assembler(string filename){
       
     
	string line;
	string ext=".hack";
	string file(filename.begin(),filename.begin()+filename.find('.'));
	string name=file+ext;
	out.open("binarycode.hack",ios::app);
	in.open(filename.c_str(),ios::in);			
	if(in.is_open()){
		while(getline(in,line)){ 
		if(line.find("//" || "/*" || "*/") != string::npos)
			  line.erase(line.find("//"));
		line=spaceRemover(line);
		A_Instruction(line);
		C_Instruction(line);
	}
	in.close();
	out.close();
	rename("binarycode.hack",name.c_str());
}
    }

    // A-INSTRUCTION FUNCTION
    void A_Instruction(string code){		
			
	int i,j=0,k=0,number;				
	int binary[15];
    char no[10];
	for(i=0;code[i]!=0;i++){
		if (code[i]=='@')break;			
	}
	if (code[i]!='@')return;			
	i++;
	out << 0;							 
	for(;code[i]!= 0;i++){
		if(code[i]==' ')continue;		
		no[j++]=code[i];				 
	}
	number=atoi(no);					
	for(k=0;number>0;k++){
		binary[k]=number%2;				
	}
	int m=15-k;
	for(int n=0; n <m ;n++){			
		out<< 0;
 }
	for (int n=k-1 ; n>=0 ; n--){			
		out << binary[n];				
	}
	out << "\n";
							
}

// C-INSTRUCTION FUNCTION

void C_Instruction(string code){
	if(code[0]=='@')return;
	for(int i=0;code[i]!=0;i++){
		if(code[i]=='='){
		string DEST(code.begin(),code.begin()+code.find('=')),COMP(code.begin()+code.find('=')+1,code.end());
		Computation(COMP);
		Destination(DEST);
		
	}
		if(code[i]==';'){
			string COMP(code.begin(),code.begin()+code.find(';')),JUMP(code.begin()+code.find(';')+1,code.end());
		Computation(COMP);
		Jump(JUMP);
		}
	}
	return;
} 

// COMPUTATION FUNCTION
	void Computation(string COMP){
		int a=1;
	for(int i=0;i<28;i++){
		if(instruction[i]==COMP){
		if(i<=18)a=0;	
		out<< "111";
		out << a;
		out << value[i]; 
		}
	}
    }
    // DESTINATION FUNCTION
	void Destination(string DEST){
        for(int i=28;i<35;i++){
		if(instruction[i]==DEST){
		out << value[i];
		 out << "000"; 
		out << endl;
		}
	}
    }

     // JUMP FUNCTION
	void Jump(string JUMP){
	for(int i=35;i<42;i++){
		if(instruction[i]==JUMP){
		out <<"000";
		out << value[i];
		out <<'\n';
		}
	}
}
    // Space Remover FUNCTION
string spaceRemover(string s){
	string st="";
	for(int i=0;i<s.length();i++){
		if(s[i]!=' ' && s[i]!='\t')st.push_back(s[i]);
	}
	return st;
}

};

int main ()
{
    string filename;
    cout<<"Enter the  filename:";
    cin>>filename;
    Hack_Assembler  assembler(filename);

cout << "\n\nThe Program  Assembled..\n";
cout << "\n\nThank You so Much..\n";
return 0;
}