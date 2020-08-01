#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;
int ispresent(string str,vector< pair <string,int> > s) {
	for(int i=0;i<s.size();i++) if(str.compare(s[i].first)==0) return i;
	return -1;
}
bool contains(string str,char a){
	for(int i=0;i<str.size();i++) if(str[i]==a) return true;
	return false;
}
int main() {
vector<pair<string,int>> s;
pair<string,int> x("SP",0);
s.push_back(x);
pair<string,int> y("LCL",1);
pair<string,int> z("ARG",2);
pair<string,int> d1("THIS",3);
pair<string,int> e1("THAT",4);
pair<string,int> a0("R0",0);
pair<string,int> a1("R1",1);
pair<string,int> a2("R2",2);
pair<string,int> a3("R3",3);
pair<string,int> a4("R4",4);
pair<string,int> a5("R5",5);
pair<string,int> a6("R6",6);
pair<string,int> a7("R7",7);
pair<string,int> a8("R8",8);
pair<string,int> a9("R9",9);
pair<string,int> a10("R10",10);
pair<string,int> a11("R11",11);
pair<string,int> a12("R12",12);
pair<string,int> a13("R13",13);
pair<string,int> a14("R14",14);
pair<string,int> a15("R15",15);
pair<string,int> kb("KBD",24576);
pair<string,int> sc("SCREEN",16384);
s.push_back(y);
s.push_back(z);
s.push_back(d1);
s.push_back(e1);
s.push_back(a0);
s.push_back(a1);
s.push_back(a2);
s.push_back(a3);
s.push_back(a4);
s.push_back(a5);
s.push_back(a6);
s.push_back(a7);
s.push_back(a8);
s.push_back(a9);
s.push_back(a10);
s.push_back(a11);
s.push_back(a12);
s.push_back(a13);
s.push_back(a14);
s.push_back(a15);
s.push_back(kb);
s.push_back(sc);
ifstream a;
a.open("inp.txt");
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
			if(a.get(ch)) if(ch=='/') { getline(a,str); if(pre2!='\n'&&pre2!=0) b<<'\n';}
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
ifstream d;
d.open("out.txt");
int jk=16;
for(int k=0;;k++){
    string cmd;
	if(!getline(d,cmd))
		break;
	int i=cmd.size();
	if(cmd[0]=='(') {
		char str[i];
		int j;
		for(j=1;;j++){
			if(cmd[j]==')')  break;
			str[j-1]=cmd[j];
		}
		str[j-1]='\0';
		if(ispresent(str,s)==-1) {
	    	pair<string,int> fg(str,k);
	    	s.push_back(fg);
	    	k--;
    	}
    	else {
    		int h=ispresent(str,s);
    		s[h].second=k;
    		k--;
    	}
    }
}
d.close();
ifstream ab;
ab.open("out.txt");
for(int k=0;;k++){
    string cmd;
	if(!getline(ab,cmd))
		break;
	int i=cmd.size();
	if(cmd[0]=='@'&&(cmd[1]>'9'||cmd[1]<'0')) {
        int j;
		char str[i];
		for(j=1;j<i;j++) {
			str[j-1]=cmd[j];
		}
		str[j-1]='\0';
    	if(ispresent(str,s)==-1) {
    		pair<string,int> fg(str,jk);
    		jk++;
    		s.push_back(fg);
    	}
    }
}
ab.close();
ifstream e;
e.open("out.txt");
ofstream c;
c.open("final.hack");
char final[17]={'0'};
for(int ky=0;;ky++){
    string cmd;
	if(!getline(e,cmd))
		break;
	int i=cmd.size();
	if(cmd[0]=='@'){
		final[0]='0';
		if(cmd[1]<='9'&&cmd[1]>='0'){
			int de=0;
			int w=1;
			for(int hgl=0;hgl<i-2;hgl++){
               w=w*10;
			}
			int r=1;
			while(w>0) {
				if(cmd[r]>'9'||cmd[r]<'0'){
					cout<<"Expected a proper integer value in ( only decimal no hexadecimal or binary) : "<<cmd;
					exit(0);
				}
				de+=(cmd[r++]-'0')*w;
				w=w/10;
			}
			r=15;
			while(r!=0) {if(de==0) final[r]='0';
				if(de%2==1) final[r]='1';
				else final[r]='0';
				de=de/2;
				r--;
			}
		}
		else {
            int j;
			char str[i-1];
			for(j=1;j<=i;j++) {
				str[j-1]=cmd[j];
		    }
		    int h=ispresent(str,s);
		    int de=s[h].second;
		    int r=15;
		    while(r!=0) {
				if(de%2==1) final[r]='1';
				else final[r]='0';
				de=de/2;
				r--;
			}
		}
	}
	else if(cmd[0]=='(') {ky--; continue;}
	else if(cmd[0]=='D'||cmd[0]=='M'||cmd[0]=='A'||cmd[0]=='0'){
        final[15]='1';final[14]='1';
        final[13]='1';
		char str1[i],str2[i];
		int j=0,k=0;
		if(contains(cmd,'=')) {
			while(cmd[j]!='='){ str1[j]=cmd[j]; j++; }
			str1[j]='\0';
			int bc=j;
			j++;
			while(cmd[j]!='\0'){ str2[k]=cmd[j]; j++;k++; }
			str2[k]='\0';
			int bcc=0;
        	if(contains(str1,'M')) { final[3]='1';bcc++;} else final[3]='0';
        	if(contains(str1,'D')) { final[4]='1';bcc++;} else final[4]='0';
        	if(contains(str1,'A')) { final[5]='1';bcc++;} else final[5]='0';
        	if(bc!=bcc) { cout<<"Error : Unidentified expression ( Expression can contain only A,M,D) : "<<str1<<" in command "<<cmd;exit(0);}
        	if(strcmp(str2,"0")==0) { final[11]='1' ;final[10]='0' ;final[9]='1' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='0' ;}
        	else if(strcmp(str2,"1")==0) { final[11]='1' ;final[10]='1' ;final[9]='1' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='0' ;}
        	else if(strcmp(str2,"-1")==0) { final[11]='1' ;final[10]='1' ;final[9]='1' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"D")==0) { final[11]='0' ;final[10]='0' ;final[9]='1' ;final[8]='1' ;final[7]='0' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"A")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='0' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"M")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='0' ;final[6]='0' ;final[12]='1' ; }
        	else if(strcmp(str2,"!D")==0) { final[11]='0' ;final[10]='0' ;final[9]='1' ;final[8]='1' ;final[7]='0' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"!A")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='0' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"!M")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='0' ;final[6]='1' ;final[12]='1' ; }
        	else if(strcmp(str2,"-D")==0) { final[11]='0' ;final[10]='0' ;final[9]='1' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"-A")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"-M")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='1' ;final[12]='1' ; }
        	else if(strcmp(str2,"D+1")==0|| strcmp(str2,"1+D")==0) { final[11]='0' ;final[10]='1' ;final[9]='1' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"M+1")==0|| strcmp(str2,"1+M")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='1' ; }
        	else if(strcmp(str2,"A+1")==0|| strcmp(str2,"1+A")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"D-1")==0) { final[11]='0' ;final[10]='0' ;final[9]='1' ;final[8]='1' ;final[7]='1' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"A-1")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"M-1")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='1' ; }
        	else if(strcmp(str2,"D+M")==0|| strcmp(str2,"M+D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='1' ; }
        	else if(strcmp(str2,"D+A")==0|| strcmp(str2,"A+D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"D-A")==0) { final[11]='0' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"D-M")==0) { final[11]='0' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='1' ;final[12]='1' ; }
        	else if(strcmp(str2,"M-D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='1' ; }
        	else if(strcmp(str2,"A-D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"D&A")==0|| strcmp(str2,"A&D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='0' ;final[7]='0' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"D&M")==0|| strcmp(str2,"M&D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='0' ;final[7]='0' ;final[6]='0' ;final[12]='1' ; }
        	else if(strcmp(str2,"D|A")==0|| strcmp(str2,"A|D")==0) { final[11]='0' ;final[10]='1' ;final[9]='0' ;final[8]='1' ;final[7]='0' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"D|M")==0|| strcmp(str2,"M|D")==0) { final[11]='0' ;final[10]='1' ;final[9]='0' ;final[8]='1' ;final[7]='0' ;final[6]='1' ;final[12]='1' ; }
        	else { cout<<"Error : Unidentified expression : "<<str2<<" in command : "<<cmd;exit(0);}
        	final[2]='0';final[1]='0';final[0]='0';
        }
        else if(contains(cmd,';')) {
            final[3]='0';final[4]='0';final[5]='0';
			while(cmd[j]!=';'){ str2[j]=cmd[j]; j++; }
			str2[j]='\0';
			j++;
			while(cmd[j]!='\0'){ str1[k]=cmd[j]; j++;k++; }
			str1[k]='\0';
			if(strcmp(str1,"JMP")==0) { final[2]='1';final[1]='1';final[0]='1';}
			else if(strcmp(str1,"JLT")==0) { final[2]='1';final[1]='0';final[0]='0';}
			else if(strcmp(str1,"JEQ")==0) { final[2]='0';final[1]='1';final[0]='0';}
			else if(strcmp(str1,"JGT")==0) { final[2]='0';final[1]='0';final[0]='1';}
			else if(strcmp(str1,"JNE")==0) { final[2]='1';final[1]='0';final[0]='1';}
			else if(strcmp(str1,"JLE")==0) { final[2]='1';final[1]='1';final[0]='0';}
			else if(strcmp(str1,"JGE")==0) { final[2]='0';final[1]='1';final[0]='1';}
			else { cout<<"Expected valid jump instruction in the command : "<<cmd;exit(0);  }
			if(strcmp(str2,"0")==0) { final[11]='1' ;final[10]='0' ;final[9]='1' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='0' ;}
        	else if(strcmp(str2,"1")==0) { final[11]='1' ;final[10]='1' ;final[9]='1' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='0' ;}
        	else if(strcmp(str2,"-1")==0) { final[11]='1' ;final[10]='1' ;final[9]='1' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"D")==0) { final[11]='0' ;final[10]='0' ;final[9]='1' ;final[8]='1' ;final[7]='0' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"A")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='1' ;final[7]='0' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"M")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='1' ;final[7]='0' ;final[6]='0' ;final[12]='1' ; }
        	else if(strcmp(str2,"!D")==0) { final[11]='0' ;final[10]='0' ;final[9]='1' ;final[8]='1' ;final[7]='0' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"!A")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='0' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"!M")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='0' ;final[6]='1' ;final[12]='1' ; }
        	else if(strcmp(str2,"-D")==0) { final[11]='0' ;final[10]='0' ;final[9]='1' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"-A")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"-M")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='1' ;final[12]='1' ; }
        	else if(strcmp(str2,"D+1")==0|| strcmp(str2,"1+D")==0) { final[11]='0' ;final[10]='1' ;final[9]='1' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"M+1")==0|| strcmp(str2,"1+M")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='1' ; }
        	else if(strcmp(str2,"A+1")==0|| strcmp(str2,"1+A")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"D-1")==0) { final[11]='0' ;final[10]='0' ;final[9]='1' ;final[8]='1' ;final[7]='1' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"A-1")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"M-1")==0) { final[11]='1' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='1' ; }
        	else if(strcmp(str2,"D+M")==0|| strcmp(str2,"M+D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='1' ; }
        	else if(strcmp(str2,"D+A")==0|| strcmp(str2,"A+D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"D-A")==0) { final[11]='0' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"D-M")==0) { final[11]='0' ;final[10]='1' ;final[9]='0' ;final[8]='0' ;final[7]='1' ;final[6]='1' ;final[12]='1' ; }
        	else if(strcmp(str2,"M-D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='1' ; }
        	else if(strcmp(str2,"A-D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='1' ;final[7]='1' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"D&A")==0|| strcmp(str2,"A&D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='0' ;final[7]='0' ;final[6]='0' ;final[12]='0' ; }
        	else if(strcmp(str2,"D&M")==0|| strcmp(str2,"M&D")==0) { final[11]='0' ;final[10]='0' ;final[9]='0' ;final[8]='0' ;final[7]='0' ;final[6]='0' ;final[12]='1' ; }
        	else if(strcmp(str2,"D|A")==0|| strcmp(str2,"A|D")==0) { final[11]='0' ;final[10]='1' ;final[9]='0' ;final[8]='1' ;final[7]='0' ;final[6]='1' ;final[12]='0' ; }
        	else if(strcmp(str2,"D|M")==0|| strcmp(str2,"M|D")==0) { final[11]='0' ;final[10]='1' ;final[9]='0' ;final[8]='1' ;final[7]='0' ;final[6]='1' ;final[12]='1' ; }
        	else { cout<<"Error : Unidentified expression "<<str2<<" in command : "<<cmd;exit(0);}
	}
	else { cout<<"Unidentified command : "<<cmd; exit(0); }
    final[16]='\0';
    for(int ggh=0;ggh<8;ggh++){
        char t=final[ggh];
        final[ggh]=final[15-ggh];
        final[15-ggh]=t;
    }
}
final[16]='\0';
c<<final<<"\n";
}
e.close();
c.close();
getch();
return 0;
}
