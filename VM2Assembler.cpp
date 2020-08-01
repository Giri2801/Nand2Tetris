#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int stst=0;
int ses=0;

int isSubstring(string s1, string s2)
{
    int M = s1.length();
    int N = s2.length();


    for (int i = 0; i <= N - M; i++) {
        int j;


        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == M)
            return i;
    }

    return -1;
}

int isSubstring1(string s1, string s2)
{
    int M = s1.length();
    int N = s2.length();
    if(M!=N) return -1;

    for (int i = 0; i <= N - M; i++) {
        int j;


        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == M)
            return i;
    }

    return -1;
}

int isdigit(char a){
	if(a=='1'||a=='2'||a=='3'||a=='4'||a=='5'||a=='6'||a=='7'||a=='8'||a=='9'||a=='0') return 1;
	else return 0;
}

int main(int argc,char**argv) {
	ifstream ab;
	ofstream ba;
	ab.open(argv[1]);
	ba.open("out2.txt");
	string ms;
	while(getline(ab,ms)){
		if(isSubstring("call",ms)==0||isSubstring("function",ms)==0){
			int hb=0;
			while(ms[hb]){
				if(ms[hb]==' ') ms[hb]='*';
				hb++;
			}
		}
		ba<<ms<<endl;
	}
	ab.close();
	ba.close();
	ifstream a;
	a.open("out2.txt");
	ofstream b;
	b.open("out.txt");
	if(!a ||!b) cout<<"Error in opening file";
	else {
	    char ch,pre2=0;
	    string str;
	    while(a.get(ch)) {
	    	int h=0;
			if(ch==9  || ch==32) ;
			else if(ch=='/') {
				char pre='*';
				if(a.get(ch)) 
					if(ch=='/') { 
						getline(a,str);
						if(pre2!='\n'&&pre2!=0) 
							b<<'\n';
					}
				else if(ch=='*') {
					while(a.get(ch)) {
           			    if(ch=='\n') h=1;
						if(ch=='/'&&pre=='*') break;
						pre=ch;
					}
					if(h==1) b<<'\n';
				}
				else b<<'/'<<ch;
			}
			else if(ch=='\n'&&(pre2=='\n'||pre2==0)) continue;
			else { b<<ch; pre2=ch; }
		}
	}



	a.close();
	b.close();
	ifstream c;
	c.open("out.txt");
	ofstream d;
	d.open(argv[2]);
	int g=0,h=0,l=0;
	for(int k=0;;k++) {
    	string cmd;
		if(!getline(c,cmd))
			break;
		string as=cmd;
		if(isSubstring1("add",cmd)==0||isSubstring1("sub",cmd)==0||isSubstring1("and",cmd)==0||isSubstring1("or",cmd)==0){
			d<<"@SP\nAM=M-1\nD=M\nA=A-1\n";
			if(isSubstring1("add",cmd)==0) d<<"M=M+D\n";
			else if(isSubstring1("and",cmd)==0) d<<"M=M&D\n";
			else if(isSubstring1("sub",cmd)==0) d<<"M=M-D\n";
			else if(isSubstring1("or",cmd)==0) d<<"M=M|D\n";
		}
		else if(isSubstring1(cmd,"not")==0){
			d<<"@SP\nA=M-1\nM=!M\n";
		}
		else if(isSubstring1(cmd,"neg")==0){
			d<<"@SP\nA=M-1\nM=-M\n";
		}
		else if(isSubstring1(cmd,"eq")==0){
			d<<"@SP\nAM=M-1\nD=M+1\nA=A-1\nD=M-D\nM=D\n@IFEQ"<<g<<"\nD+1;JEQ\n@SP\nA=M-1\nM=0\n(IFEQ"<<g<<")\n";
			g++;
		}
		else if(isSubstring1(cmd,"gt")==0){
			d<<"@SP\nAM=M-1\nD=M+1\nA=A-1\nD=M-D\nM=-1\n@IFGT"<<h<<"\nD+1;JGT\n@SP\nA=M-1\nM=0\n(IFGT"<<h<<")\n";
			h++;
		}
		else if(isSubstring1(cmd,"lt")==0){
			d<<"@SP\nAM=M-1\nD=M+1\nA=A-1\nD=M-D\nM=-1\n@IFLT"<<l<<"\nD+1;JLT\n@SP\nA=M-1\nM=0\n(IFLT"<<l<<")\n";
			l++;
		}
		else if(isSubstring("push",cmd)!=-1){
			if(isSubstring("push",cmd)!=0)
				d<<"Error wrong command : "<<cmd<<"\n";
			char seg[11];
			int i;
			for( i=4;!isdigit(cmd[i])&&i<15;i++){
				seg[i-4]=cmd[i];
			}

			if(i==15) d<<"Error in command : "<<cmd<<"\n";
			seg[i-4]='\0';
			int cmdsize=cmd.size();
			cmdsize-=i+1;
			char index[cmdsize+2];
			for(int y=0;y<=cmdsize;y++){
				index[y]=cmd[i+y];
			}
			index[cmdsize+1]='\0';
			if(isSubstring1(seg,"local")==0){
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
                    if(index[0]=='0')
                        d<<"@LCL\nA=M\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
                    else
                        d<<"@LCL\nA=M+"<<index<<"\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
				else {
					d<<"@"<<index<<"\nD=A\n@LCL\nA=M+D\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}

			}
			else if(isSubstring1(seg,"argument")==0){
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
                    if(index[0]=='0')
                        d<<"@ARG\nA=M\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
                    else
                        d<<"@ARG\nA=M+"<<index<<"\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
				else {
					d<<"@"<<index<<"\nD=A\n@ARG\nA=M+D\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
			}
			else if(isSubstring1(seg,"this")==0){
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
                    if(index[0]=='0')
                        d<<"@THIS\nA=M\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
                    else
                        d<<"@THIS\nA=M+"<<index<<"\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
				else {
					d<<"@"<<index<<"\nD=A\n@THIS\nA=M+D\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
			}
			else if(isSubstring1(seg,"that")==0){
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
                    if(index[0]=='0')
                        d<<"@THAT\nA=M\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
                    else
                        d<<"@THAT\nA=M+"<<index<<"\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
				else {
					d<<"@"<<index<<"\nD=A\n@THAT\nA=M+D\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
			}

			else if(isSubstring1(seg,"pointer")==0){
				if(index[0]=='0'){
					d<<"@THIS\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
				else if(index[0]=='1'){
					d<<"@THAT\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
				else d<<"Error improper command involving pointer : "<<cmd<<"\n";
			}
			else if(isSubstring1(seg,"constant")==0){
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
					d<<"@SP\nAM=M+1\nA=A-1\nM="<<index<<"\n";
				}
				else {
					d<<"@"<<index<<"\nD=A\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
			}
			else if(isSubstring1(seg,"static")==0){
				d<<"@";
				int yp=0;
				while(argv[2][yp]!='.') d<<argv[2][yp++];
				d<<"_"<<index<<"\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
			}
			else if(isSubstring1(seg,"temp")==0) {
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
                    if(index[0]=='0')
                        d<<"@5\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
                    else
                        d<<"@6\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
				else {
					d<<"@"<<index<<"\nD=A\n@5\nA=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
				}
			}
			else d<<"Error improper push command : "<<cmd<<"\n";
		}
		else if(isSubstring("pop",cmd)!=-1){
			if(isSubstring("pop",cmd)!=0)
				d<<"Error wrong command : "<<cmd<<"\n";
			char seg[11];
			int i;
			for( i=3;!isdigit(cmd[i])&&i<15;i++){
				seg[i-3]=cmd[i];
			}
			if(i==15) d<<"Error in command : "<<cmd<<"\n";
			seg[i-3]='\0';

			int cmdsize=cmd.length();
			cmdsize-=i+1;
			char index[cmdsize+2];
			for(int y=0;y<=cmdsize;y++){
				index[y]=cmd[i+y];
			}
			index[cmdsize+1]='\0';
			if(isSubstring1(seg,"local")==0){
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
                    if(index[0]=='0')
                        d<<"@LCL\nD=M\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
                    else
                        d<<"@LCL\nD=M+"<<index<<"\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
				}
				else {
					d<<"@"<<index<<"\nD=A\n@LCL\nD=M+D\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
				}

			}
			else if(isSubstring1(seg,"argument")==0){
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
                    if(index[0]=='0')
                        d<<"@ARG\nD=M\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
                    else
                        d<<"@ARG\nD=M+"<<index<<"\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
				}
				else {
					d<<"@"<<index<<"\nD=A\n@ARG\nD=M+D\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
				}

			}
			else if(isSubstring1(seg,"this")==0){
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
                    if(index[0]=='0')
                        d<<"@THIS\nD=M\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
                    else
                        d<<"@THIS\nD=M+"<<index<<"\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
				}
				else {
					d<<"@"<<index<<"\nD=A\n@THIS\nD=M+D\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
				}

			}
			else if(isSubstring1(seg,"that")==0){
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
                    if(index[0]=='0')
                        d<<"@THAT\nD=M\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
                    else
                        d<<"@THAT\nD=M+"<<index<<"\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
				}
				else {
					d<<"@"<<index<<"\nD=A\n@THAT\nD=M+D\n@SP\nAM=M-1\nA=A+1\nM=D\nA=A-1\nD=M\nA=A+1\nA=M\nM=D\n";
				}

			}
			else if(isSubstring1(seg,"pointer")==0){
				if(index[0]=='0'){
					d<<"@SP\nAM=M-1\nD=M\n@THIS\nM=D\n";
				}
				else if(index[0]=='1'){
					d<<"@SP\nAM=M-1\nD=M\n@THAT\nM=D\n";
				}
				else d<<"Error improper command involving pointer : "<<cmd<<"\n";
			}
			else if(isSubstring1(seg,"static")==0){
				d<<"@SP\nAM=M-1\nD=M\n@";
				int yp=0;
				while(argv[2][yp]!='.') d<<argv[2][yp++];
				d<<"_"<<index<<"\nM=D\n";

			}
			else if(isSubstring1(seg,"temp")==0){
				if((index[0]=='0'||index[0]=='1')&&cmdsize==0){
                    if(index[0]=='0')
                        d<<"@SP\nAM=M-1\nD=M\n@5\nM=D\n";
                    else if(index[0]=='1')
                        d<<"@SP\nAM=M-1\nD=M\n@6\nM=D\n";
                    else if(index[0]=='2')
                        d<<"@SP\nAM=M-1\nD=M\n@7\nM=D\n";
                    else if(index[0]=='3')
                        d<<"@SP\nAM=M-1\nD=M\n@8\nM=D\n";
                    else if(index[0]=='4')
                        d<<"@SP\nAM=M-1\nD=M\n@9\nM=D\n";
                    else if(index[0]=='5')
                        d<<"@SP\nAM=M-1\nD=M\n@10\nM=D\n";
                    else if(index[0]=='6')
                        d<<"@SP\nAM=M-1\nD=M\n@11\nM=D\n";
                    else if(index[0]=='7')
                        d<<"@SP\nAM=M-1\nD=M\n@12\nM=D\n";
                    else d<<"Error in command : "<<cmd<<" the value of index is not accessible\n";
				}
				else {
					d<<"Error in command : "<<cmd<<" the value of index is not accessible\n";
				}
			}
			else d<<"Error improper pop command : "<<cmd<<"\n";

		}
		else if(isSubstring("function",cmd)!=-1){
			d<<"(";
			int yp=0;
			yp=9;
			while(cmd[yp]!='*')	d<<cmd[yp++];
			d<<")\n@";
			yp++;
			while(cmd[yp]) d<<cmd[yp++];
			d<<"\nD=A\n(";
			yp=0;
			while(argv[2][yp]!='.') d<<argv[2][yp++];
			d<<"_LOOP"<<stst<<")\n@";
			yp=0;
			while(argv[2][yp]!='.')
			d<<argv[2][yp++];

			d<<"_LOOP_END"<<stst<<"\nD;JEQ\n@SP\nAM=M+1\nA=A-1\nM=0\nD=D-1\n@";
			yp=0;
			while(argv[2][yp]!='.')
			d<<argv[2][yp++];

			d<<"_LOOP"<<stst<<"\n0;JMP\n(";
			yp=0;
			while(argv[2][yp]!='.')
			d<<argv[2][yp++];

			d<<"_LOOP_END"<<stst++<<")\n";
		}
		else if(isSubstring("call",cmd)!=-1) {

			d<<"@";
			int yp=0;
			while(argv[2][yp]!='.')
			d<<argv[2][yp++];
			d<<"_";
			yp=0;
			yp=5;
			while(cmd[yp]!='*')
			d<<cmd[yp++];
			yp++;
			d<<"_RETURN_ADDRESS"<<ses<<"\nD=A\n@SP\nA=M\nM=D\n@LCL\nD=M\n@SP\nAM=M+1\nM=D\n@ARG\nD=M\n@SP\nAM=M+1\nM=D\n@THIS\nD=M\n@SP\nAM=M+1\nM=D\n@THAT\nD=M\n@SP\nAM=M+1\nM=D\n@SP\nM=M+1\nD=M\n@LCL\nM=D\n@5\nD=D-A\n@";
			while(cmd[yp]) d<<cmd[yp++];
			d<<"\nD=D-A\n@ARG\nM=D\n@";
			yp=5;
			while(cmd[yp]!='*')
			d<<cmd[yp++];

			d<<"\n0;JMP\n(";
			yp=0;
			while(argv[2][yp]!='.')
			d<<argv[2][yp++];
			d<<"_";
			yp=5;
			while(cmd[yp]!='*')

			d<<cmd[yp++];

			d<<"_RETURN_ADDRESS"<<ses++<<")\n";
		}
		else if(isSubstring("return",cmd)!=-1) {
			d<<"@5\nD=A\n@LCL\nAD=M-D\nD=M\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@ARG\nA=M\nM=D\nD=A\n@SP\nM=D+1\n@LCL\nAM=M-1\nD=M\n@THAT\nM=D\n@LCL\nAM=M-1\nD=M\n@THIS\nM=D\n@LCL\nAM=M-1\nD=M\n@ARG\nM=D\n@LCL\nAM=M-1\nD=M\n@LCL\nM=D\n@R13\nA=M\n0;JMP\n";
		}
		else if(isSubstring("goto",cmd)==0){
			d<<"@";
			int yp=0;
			while(argv[2][yp]!='.')
			d<<argv[2][yp++];
			d<<"_";
			yp=4;
			while(cmd[yp])	d<<cmd[yp++];
			d<<"\n0;JMP\n";

		}
		else if(isSubstring("label",cmd)!=-1){
			d<<"(";
			int yp=0;
			while(argv[2][yp]!='.') d<<argv[2][yp++];
			d<<"_";
			yp=5;
			while(cmd[yp])	d<<cmd[yp++];
			d<<")\n";
		}
		else if(isSubstring("if-goto",cmd)==0){
			d<<"@SP\nAM=M-1\nD=M\n@";
			int yp=0;
			while(argv[2][yp]!='.') d<<argv[2][yp++];
			d<<"_";
			yp=7;
			while(cmd[yp])	d<<cmd[yp++];
			d<<"\nD;JNE\n";

		}
		else d<<"Wrong command : "<<cmd;


	}
    int fgh;
	c.close();
	d.close();
	cin>>fgh;
	return 0;
}
