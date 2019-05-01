%{
  /*_____Definition section_____literal c++ code between single "%"_____*/

  /*Necesary imports*/
    #include <stdio.h>
    #include <iostream>
    #include <string.h>
    #include <bitset>
    #include <vector>
    #include <map>
    #include <stdlib.h>
    #include <algorithm>
    #include <cstdlib>
    #include <fstream>
    #include <sstream>

    

    //C++ definitions
    std::fstream fs; //stream instruction file
    std::fstream fs2; // stream data file
    std::string final_message="Compiler success";
    std::string line;
    int counter=0;
    int times=0;

    int yylex();  //call to invoke lexer, returns token
    extern int yylineno; //line number counter

    /*Define different instructions structures*/
    void vInstruction(std::string op,std::string vr,std::string v1,std::string v2); // op vr,v1,v2
    void vsInstruction(std::string op,std::string vr,std::string v1,std::string s1); //op vr,v2,s1
    void viInstruction(std::string op,std::string vr,std::string v1, std::string imm); // op ,vr,v1, imm
    void viInstruction1(std::string op,std::string v1, std::string imm); // op , v1, imm
    void ssInstruction(std::string op,std::string s1, std::string imm); // op , s1, imm
    void repeat(int times);
    void endrepeat();
    std::string vectorReg(std::string vecReg);
    std::string scalarReg(std::string scaReg);
    std::string getImm(std::string imm);
    std::string getImm1(std::string imm);

    void yyerror(std::string S); // define error function
    void printt(std::string s); //Define print function
%}

%union{
  char* id;
  int num;
} // structure to make the id and number relationship

/*lex tokens*/
%token <id> vaddition vsubtra vmultiple vload vstore vxor vrot vadditions vadditioni vsubtras vsubtrai  vxors vxori  vmultiples  vmultiplei  vrotr smove//instructions
%token <id> vreg // vector register
%token <id> sreg // scalar register
%token <id> immediate //immediate
%token <id> commentary //commentary
%token <num> number //number
%token <id> vrepeat //repeat
%token <id> vendrepeat //endrepeat

/*yacc tokens*/
%type <id> operation 

%%
line   : line instruccion '\n'
       | line commentary '\n'
       | /* NULL */
      ;


operation : vaddition     {;}
          | vsubtra       {;}
          | vmultiple     {;}
          | vload        {;}
          | vstore         {;}
          | vxor       {;}
          | vrot       {;}
          | vadditions       {;}
          | vadditioni       {;}
          | vsubtras       {;}
          | vsubtrai       {;}
          | vxors           {;}
          | vxori       {;}
          | vmultiples         {;}
          | vmultiplei     {;}
          | vrotr {;}
          | smove {;}
          ;

instruccion : operation vreg ',' vreg ',' vreg {vInstruction($1,$2,$4,$6);}
            | operation vreg ',' vreg ',' sreg {vsInstruction($1,$2,$4,$6);}
            | operation vreg ',' vreg ',' immediate {viInstruction($1,$2,$4,$6);}
            | operation immediate ',' vreg {viInstruction1($1,$4,$2);}
            | operation vreg ',' immediate {viInstruction1($1,$2,$4);}
            | operation sreg ',' immediate {ssInstruction($1,$2,$4);}
            | vrepeat number {repeat($2);}
            | vendrepeat {endrepeat();}
            | instruccion commentary {;}
            | error {yyerror("instruccion not supported");}
            ;   
 
%%

extern int yyparse();
extern FILE *yyin; //file used as input
std::string ruta=""; //where the file to read is located

//Instruccion op rd,rs,rm
void vInstruction(std::string op,std::string vr,std::string v1,std::string v2){
    std::string binary;
    if(op.compare("VAdd")==0 || op.compare("vAdd")==0 || op.compare("vadd")==0 || op.compare("VADD")==0){
        binary+="00000";
    }else if(op.compare("VSUB")==0 || op.compare("Vsub")==0 || op.compare("vsub")==0 || op.compare("VSub")==0){
        binary+="00011";
    }else if(op.compare("VXOR")==0 || op.compare("Vxor")==0 || op.compare("vxor")==0 || op.compare("VXor")==0){
        binary+="00110";
    }else if(op.compare("VMUL")==0 || op.compare("Vmul")==0 || op.compare("vmul")==0 || op.compare("VMul")==0){
        binary+="01001";
    }
    binary+=vectorReg(vr);
    binary+=vectorReg(v1);
    binary+=vectorReg(v2);
    binary+="0000"; // bits used only with immediates
    fs<<binary<<'\n';
}

void vsInstruction(std::string op,std::string vr,std::string v1,std::string s1){
    std::string binary;
    if(op.compare("VAdds")==0 || op.compare("vAdds")==0 || op.compare("vadds")==0 || op.compare("VADDS")==0){
        binary+="00010";
    }else if(op.compare("VSUBS")==0 || op.compare("Vsubs")==0 || op.compare("vsubs")==0 || op.compare("VSubs")==0){
        binary+="00101";
    }else if(op.compare("VXORS")==0 || op.compare("Vxors")==0 || op.compare("vxors")==0 || op.compare("VXors")==0){
        binary+="01000";
    }else if(op.compare("VMULS")==0 || op.compare("Vmuls")==0 || op.compare("vmuls")==0 || op.compare("VMuls")==0){
        binary+="01011";
    }
    binary+=vectorReg(vr);
    binary+=vectorReg(v1);
    binary+=scalarReg(s1);
    binary+="0000"; // bits used only with immediates
    fs<<binary<<'\n';
}

void viInstruction(std::string op,std::string vr,std::string v1,std::string imm){
    std::string binary;
    if(op.compare("VADDI")==0 || op.compare("Vaddi")==0 || op.compare("vaddi")==0 || op.compare("VAddi")==0){
        binary+="00001";
    }else if(op.compare("VSUBI")==0 || op.compare("Vsubi")==0 || op.compare("vsubi")==0 || op.compare("VSubi")==0){
        binary+="00100";
    }else if(op.compare("VXORI")==0 || op.compare("Vxori")==0 || op.compare("vxori")==0 || op.compare("VXori")==0){
        binary+="00111";
    }else if(op.compare("VMULI")==0 || op.compare("Vmuli")==0 || op.compare("vmuli")==0 || op.compare("VMuli")==0){
        binary+="01101";
    }else if(op.compare("VROTR")==0 || op.compare("Vrotr")==0 || op.compare("vrotr")==0 || op.compare("VRotr")==0){
        binary+="01101";
    }
    binary+=vectorReg(vr);
    binary+=vectorReg(v1);
    binary+=getImm(imm);
    fs<<binary<<'\n';
}

void viInstruction1(std::string op,std::string vr,std::string imm){
    std::string binary;
    if(op.compare("VST")==0 || op.compare("Vst")==0 || op.compare("vst")==0 || op.compare("VSt")==0){
        binary+="01110";
    }else if(op.compare("VLD")==0 || op.compare("Vld")==0 || op.compare("vld")==0 || op.compare("VLd")==0){
        binary+="01111";
    }else if(op.compare("VROT")==0 || op.compare("Vrot")==0 || op.compare("vrot")==0 || op.compare("VRot")==0){
        binary+="01010";
    }
    binary+=vectorReg(vr);
    binary+=getImm1(imm);
    fs<<binary<<'\n';
}

void ssInstruction(std::string op,std::string s1,std::string imm){
     std::string binary;
    if(op.compare("SMOV")==0 || op.compare("Smov")==0 || op.compare("smov")==0 || op.compare("SMov")==0){
        binary+="10000";
    }
    binary+=scalarReg(s1);
    binary+=getImm(imm);
    fs<<binary<<'\n';
}

void repeat(int num){
    times=num;
}

void endrepeat(){
    times=0;
}

std::string vectorReg(std::string vecReg){
    std::string reg="0";
    vecReg.erase(0, 1);                                                 //erase 'r'
    std::string bin = std::bitset<4>(atoi(vecReg.c_str())).to_string(); //set 4 bits for number of 'r'
    reg+=bin;
    return reg;
}

std::string scalarReg(std::string scaReg){
    std::string reg="1";
    scaReg.erase(0, 1);                                                 //erase 'r'
    std::string bin = std::bitset<4>(atoi(scaReg.c_str())).to_string(); //set 4 bits for number of 'r'
    reg+=bin;
    return reg;
}

std::string getImm(std::string imm){
    std::string data;
    std::istringstream buffer(data);
	int value;
	buffer >> value;
    std::bitset<9> b;
	b = (std::bitset<9> ) value;
    return b.to_string();
}

std::string getImm1(std::string imm){
    std::string data;
    std::istringstream buffer(data);
	int value;
	buffer >> value;
    std::bitset<14> b;
	b = (std::bitset<14> ) value;
    return b.to_string();
}

void printt(std::string s){
  std::cout << s << std::endl;
}

void yyerror(std::string S){
  final_message="Compiler failed";
  std::cout << S <<" at line: "<<yylineno<<'\n';
  yyclearin;
  exit(0);
}

int main(void) {
  std::cout<<"Ruta del archivo a compilar"<<'\n';
  fs.open ("text.txt", std::ios::out | std::ios::trunc); //Intrucciones
  fs2.open ("data.txt", std::ios::out | std::ios::trunc); //Datos
  std::cin>>ruta;
  FILE *myfile = fopen(ruta.c_str(), "r");
	//se verifica si es valido
	if (!myfile) {
		std::cout << "No es posible abrir el archivo" << std::endl;
		return -1;
	}
  //fs<<"11100001101000000000000000000000"<<'\n'; // initial write of text file
	yyin = myfile;
	do {
		yyparse(); // start yacc
	} while (!feof(yyin)); //condition of finish
  

  fs.close();
  fs2.close();
  std::cout<<final_message<<'\n';
  for(int i=0;i<100;++i);
}
