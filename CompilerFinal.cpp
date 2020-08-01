#include <bits/stdc++.h>
#include<stdlib.h>
using namespace std;
#define pts for(int fgh=0;fgh<space-2;fgh++) f<<" "; f<<x<<"\n"


class Entry {
	public:
		string name;
		string type;
		string sf;//kind=static/field/argument/local
		int index;
} ;

class SymbolTable {
public:
	int kind1_count;  //field or local
	int kind2_count;  //static or argument
	int total_count;
	vector<Entry*> a;
	string names;
	void init(string x){
		//f<<"Initialising da funny boi\n";
		kind1_count=0;
		kind2_count=0;
		total_count=0;
		a.clear();
		names=x;
	}
};

SymbolTable Class_Symbol_table;
SymbolTable Subroutine_Symbol_table;
vector<string> fil;
int d_count=0;
ofstream fin;
int Tlabelnum;

Entry* present(string s){
	for(int i=0;i<Class_Symbol_table.a.size();i++){
		if(Class_Symbol_table.a[i]->name==s) return Class_Symbol_table.a[i];
	}
	for(int i=0;i<Subroutine_Symbol_table.a.size();i++){
		if(Subroutine_Symbol_table.a[i]->name==s) return Subroutine_Symbol_table.a[i];
	}
	return NULL;
}

string rtok(string s){
	int x=s.size();
	char a[x+4];
	int i;
	for(i=0;s[i]!='.';i++){
		a[i]=s[i];
	}
	a[i]='.';
	a[i+1]='t';
	a[i+2]='o';
	a[i+3]='k';
	a[i+4]='\0';
	return a;
}

string rxml(string s){
	int x=s.size();
	char a[x+4];
	int i;
	for(i=0;s[i]!='.';i++){
		a[i]=s[i];
	}
	a[i]='.';
	a[i+1]='x';
	a[i+2]='m';
	a[i+3]='l';
	a[i+4]='\0';
	return a;
}
string rerr(string s){
	int x=s.size();
	char a[x+4];
	int i;
	for(i=0;s[i]!='.';i++){
		a[i]=s[i];
	}
	a[i]='.';
	a[i+1]='e';
	a[i+2]='r';
	a[i+3]='r';
	a[i+4]='\0';
	return a;
}
string rvm(string s){
	int x=s.size();
	char a[x+4];
	int i;
	for(i=0;s[i]!='.';i++){
		a[i]=s[i];
	}
	a[i]='.';
	a[i+1]='v';
	a[i+2]='m';
	a[i+3]='\0';
	return a;
}

void CompileSubroutine(ofstream& f,ofstream& g);
void compileTerm(ofstream& f,ofstream& g);
int compileExpressionList(ofstream& f,ofstream& g);
void compileExpression(ofstream& f,ofstream& g);
void compileLetStatement(ofstream& f,ofstream& g);
void compileDoStatement(ofstream& f,ofstream& g);
void compileWhileStatement(ofstream& f,ofstream& g);
void compileReturnStatement(ofstream& f,ofstream& g);
void compileIfStatement(ofstream& f,ofstream& g);
void compileVarDec(ofstream& f,ofstream& g);
void compileStatements(ofstream& f,ofstream& g);
void compileParameterList(ofstream& f,ofstream& g);
void Compileclassvardec(ofstream& f,ofstream& g);

int space=0;

string rettok(string s){
	if(s[3]=='k') return "keyword";
	if(s[3]=='s') return "symbol";
	if(s[3]=='S') return "StringConstant";
	if(s[4]=='n') return "integerConstant";
	if(s[4]=='d') return "identifier";
	else return "\0";
}


string sname(string s){
	int m=s.size();
	//f<<s;
	//f<<m<<"\n";
	int i,j;
	if(s[3]=='k') { i=12,j=m-11;}
	else if(s[3]=='s') { i=11;j=m-10;}
	else if(s[3]=='S') {i=19;j=m-18;}
	else if(s[4]=='n') {i=20;j=m-19;}
	else if(s[4]=='d') {i=15;j=m-14;}
	char a[j-i+4];
	int k=0;
	for(;i<j;i++){
		a[k++]=s[i];
	}
	a[k]='\0';
	return a;
}


bool issymbol(char a) {
	return (a=='('||a==')'||a=='{'||a=='}'||a=='['||a==']'||a=='.'||a==','||a==39||a=='+'||a=='_'||a=='-'||a=='/'||a=='&'||a=='|'||a=='<'||a=='>'||a=='='||a==';'||a=='*'||a=='~');
}

bool iskeyword(string s){
	return (s=="class"||s=="constructor"||s=="function"||s=="method"||s=="field"||s=="static"||s=="var"||s=="int"||s=="char"||s=="boolean"||s=="void"||s=="true"||s=="false"||s=="null"||s=="this"||s=="let"||s=="do"||s=="if"||s=="else"||s=="while"||s=="return" );
}

bool isintconstant(string s){
	for(int i=0;s[i];i++){
		if(!(s[i]>='0'&&s[i]<='9')) return false;
	}
	return true;
}

bool isStringconst(string s) {
	if(s[0]==34&&s[s.size()-1]==34) return true;
	return false;
}

bool isidentifier(string s){
	if(s[0]>='0'&&s[0]<='9')	return false;
	for(int i=0;i<s.size();i++){
		if(!((s[i]<='Z'&&s[i]>='A')||(s[i]>='a'&&s[i]<='z')||(s[i]>='0'&&s[i]<='9')||s[i]=='_')) return false;
	}
	return true;
}

bool iskeywordconst(string s){
	return (s=="this"||s=="true"||s=="false"||s=="this"||s=="null");
}

bool isop(string x){
	return (x=="+"||x=="-"||x=="*"||x=="/"||x=="&"||x=="|"||x=="<"||x==">"||x=="=");
}

void Compileclass(ofstream& f,ofstream& g) {
	f<<"<class>\n";
	space+=2;
	d_count=0;
	string x;
	x=fil[d_count++];
	//f<<d.tellg();
	x=fil[d_count++];
	//f<<" "<<d.tellg();
	if(!(x=="  <keyword> class </keyword>")) { g<<" ERROR: class expected but found : "<<x<<"\n";exit(0);}
	pts;
	x=fil[d_count++];
	//f<<" "<<d.tellg();
	if(!(rettok(x)=="identifier")) { g<<" ERROR: Class Name expected but found : "<<x<<"\n";exit(0);}
	pts;
	//f<<"Calling for initialization\n";
	Class_Symbol_table.init(sname(x));
	Tlabelnum=0;
	x=fil[d_count++];
	//f<<" "<<d.tellg();
	if(!(x=="  <symbol> { </symbol>")) { g<<" ERROR: { expected but found : "<<x<<" ";exit(0);}
	pts;
	Compileclassvardec(f,g);
	CompileSubroutine(f,g);
	x=fil[d_count++];
	if(!(sname(x)=="}")) { g<<" ERROR: } expected but found : "<<x<<"\n";exit(0);}
	pts;
	space-=2;
	f<<"</class>";
}

int isterm(ofstream& f,ofstream& g){
	string x;
	x=fil[d_count++];
	string s;
	s=fil[d_count++];
	d_count--;
	d_count--;
	if(rettok(x)=="integerConstant") return 1;
	if(rettok(x)=="StringConstant") return 2;
	if(iskeywordconst(sname(x))) return 3;
	if(rettok(x)=="identifier"&&sname(s)=="[") return 4;
	if(rettok(x)=="identifier"&&sname(s)=="(") return 5;
	if(rettok(x)=="identifier"&&sname(s)==".") return 6;
	if(rettok(x)=="identifier") return 7;
	if(sname(x)=="(") return 8;
	if(sname(x)=="~"||sname(x)=="-") return 9;
	return 0;
}

void CompileSubroutine(ofstream& f,ofstream& g) {
	//f<<"In CompileSubroutine\n";

	string x;
	//f<<" "<<d.tellg();
	x=fil[d_count++];
	//f<<x;
	while(sname(x)=="constructor"||sname(x)=="function"||sname(x)=="method"){
		string tpp=sname(x);
		for(int i=0;i<space;i++) f<<" ";
		f<<"<SubroutineDec>\n";
		space+=2;
		pts;
		x=fil[d_count++];
		if(!(rettok(x)=="identifier"||rettok(x)=="keyword")) { g<<" ERROR: Return type ERROR in "<<Class_Symbol_table.names;exit(0);}
		pts;
		string rettype=sname(x);
		x=fil[d_count++];
		if(!(rettok(x)=="identifier")) { g<<" ERROR: proper identifier expected but found : "<<x<<" in "<<Class_Symbol_table.names;exit(0);}
		pts;
		Subroutine_Symbol_table.init(sname(x));
		if(tpp=="method"){
			Entry* ent = new Entry;
			ent->name="this";
			ent->index=0;
			ent->type=Class_Symbol_table.names;
			ent->sf="argument";
			Subroutine_Symbol_table.a.push_back(ent);
			Subroutine_Symbol_table.kind2_count++;
			Subroutine_Symbol_table.total_count++;
		}
		x=fil[d_count++];
		if(!(x=="  <symbol> ( </symbol>")) { g<<" ERROR : ( expected but found : "<<x<<"\n";exit(0); }
		pts;
		compileParameterList(f,g);
		x=fil[d_count++];
		if(!(x=="  <symbol> ) </symbol>")) { g<<" ERROR : ) expected but found : "<<x<<"\n";exit(0); }
		pts;
		for(int fgh=0;fgh<space;fgh++) f<<" ";
		f<<"<subroutineBody>\n";
		space+=2;
		x=fil[d_count++];
		if(!(x=="  <symbol> { </symbol>")) { g<<" ERROR : { expected but found : "<<x<<"\n";exit(0); }
		pts;
		compileVarDec(f,g);
		fin<<"function "<<Class_Symbol_table.names<<"."<<Subroutine_Symbol_table.names<<" "<<Subroutine_Symbol_table.kind1_count<<"\n";
		if(tpp=="constructor"){
			fin<<"push constant "<<Class_Symbol_table.kind1_count<<"\n";
			fin<<"call Memory.alloc 1\n"<<"pop pointer 0\n";
		}
		else if(tpp=="method"){
			fin<<"push argument 0\n";
			fin<<"pop pointer 0\n";
		}
		compileStatements(f,g);
		x=fil[d_count++];
		if(!(x=="  <symbol> } </symbol>")) { g<<" ERROR : } expected but found : "<<x<<"\n";exit(0); }
		pts;
		space-=2;
		for(int fgh=0;fgh<space;fgh++) f<<" ";
		f<<"</subroutineBody>\n";
		space-=2;
		for(int fgh=0;fgh<space;fgh++) f<<" ";
		f<<"</SubroutineDec>\n";
		x=fil[d_count++];
	}
	d_count--;
}

void Compileclassvardec(ofstream& f,ofstream& g) {
	string x;
	x=fil[d_count++];
	//f<<"In classvardec\n";
	//f<<x;
	while(sname(x)=="field"||sname(x)=="static"){
		string ky=sname(x);
		if(ky=="field") ky="this";
		for(int i=0;i<space;i++) f<<" ";
		f<<"<classvardec>\n";
		space+=2;
		pts;
		x=fil[d_count++];
		if(!(rettok(x)=="identifier"||rettok(x)=="keyword")) { g<<" ERROR: variable type expected but found : "<<x<<"\n";exit(0); }
		string sk=sname(x);

		do {
			pts;
			x=fil[d_count++];
			Entry* new_entry=new Entry;
			new_entry->sf=ky;
			new_entry->type=sk;
			if(ky=="this"){
				new_entry->index=Class_Symbol_table.kind1_count++;
				Class_Symbol_table.total_count++;
			}
			else {
				new_entry->index=Class_Symbol_table.kind2_count++;
				Class_Symbol_table.total_count++;
			}
			if(!(rettok(x)=="identifier")) { g<<" ERROR: proper identifier expected but found : "<<x<<"\n";exit(0); }
			new_entry->name=sname(x);
			pts;
			Class_Symbol_table.a.push_back(new_entry);
			x=fil[d_count++];
		}while(x=="  <symbol> , </symbol>");
		if(!(x=="  <symbol> ; </symbol>")) { g<<" ERROR: ; expected but found : "<<x<<"\n";exit(0); }
		pts;

		space-=2;
		for(int i=0;i<space;i++) f<<" ";
		f<<"</classvardec>\n";
		//g<<"Oho\n";

		x=fil[d_count++];
	}
	//f<<x.size();
	//f<<" "<<d.tellg();
	d_count--;
	//f<<" "<<d.tellg();
}

void compileParameterList(ofstream& f,ofstream& g){
	for(int fgh=0;fgh<space;fgh++) f<<" ";
	f<<"<parameterlist>\n";
	space+=2;
	string x;
	x=fil[d_count++];
	if(x=="  <symbol> ) </symbol>") {
        space-=2;
        for(int fgh=0;fgh<space;fgh++) f<<" ";
        f<<"</parameterlist>\n";
		d_count--;
		return;
	}
	int check=0;
	do {
		if(check==1) x=fil[d_count++];
		check=1;
		if(!(rettok(x)=="identifier"||rettok(x)=="keyword")) g<<" ERROR: variable type expected but found : "<<x<<"\n";
		string sk=sname(x);
		pts;
		x=fil[d_count++];
		Entry* new_entry=new Entry;
		new_entry->sf="argument";
		new_entry->type=sk;
		if(!(rettok(x)=="identifier")) { g<<" ERROR: proper identifier expected but found : "<<x<<"\n";exit(0); }
		new_entry->name=sname(x);
		pts;
		new_entry->index=Subroutine_Symbol_table.kind2_count++;
		Subroutine_Symbol_table.total_count++;
		Subroutine_Symbol_table.a.push_back(new_entry);
		x=fil[d_count++];
	}while(x=="  <symbol> , </symbol>");

	space-=2;
	for(int fgh=0;fgh<space;fgh++) f<<" ";
	f<<"</parameterlist>\n";
	d_count--;

}

void compileStatements(ofstream& f,ofstream& g) {
	string x;
	x=fil[d_count++];
	if(!(sname(x)=="let"||sname(x)=="return"||sname(x)=="do"||sname(x)=="if"||sname(x)=="while")) {
		d_count--;
		return;
	}
	for(int fgh=0;fgh<space;fgh++) f<<" ";
		f<<"<Statements>\n";
		space+=2;
	while(sname(x)=="let"||sname(x)=="return"||sname(x)=="do"||sname(x)=="if"||sname(x)=="while") {

		d_count--;
		if(sname(x)=="do") {
			compileDoStatement(f,g);
		}
		else if(sname(x)=="let")  compileLetStatement(f,g);
		else if(sname(x)=="return")  compileReturnStatement(f,g);
		else if(sname(x)=="if") compileIfStatement(f,g);
		else if(sname(x)=="while") compileWhileStatement(f,g);

		x=fil[d_count++];
	}
	space-=2;
	for(int fgh=0;fgh<space;fgh++) f<<" ";
	f<<"</Statements>\n";
	d_count--;
}

void compileVarDec(ofstream& f,ofstream& g){
	string x;
	x=fil[d_count++];
	while(sname(x)=="var") {
        for(int fgh=0;fgh<space;fgh++) f<<" ";
		f<<"<varDec>\n";
		space+=2;
		pts;
		x=fil[d_count++];
		if(!(rettok(x)=="identifier"||rettok(x)=="keyword")) { g<<" ERROR: type expected but found : "<<x<<"\n";exit(0); }
		string sk=sname(x);

		do {
			pts;
			x=fil[d_count++];
			Entry *new_entry=new Entry;
			new_entry->sf="local";
			new_entry->type=sk;
			new_entry->index=Subroutine_Symbol_table.kind1_count++;
			Subroutine_Symbol_table.total_count++;
			if(!(rettok(x)=="identifier")) { g<<" ERROR: proper identifier expected but found : "<<x<<"\n";exit(0); }
			new_entry->name=sname(x);
			pts;
			Subroutine_Symbol_table.a.push_back(new_entry);
			x=fil[d_count++];
		}while(x=="  <symbol> , </symbol>");
		if(!(x=="  <symbol> ; </symbol>")) { g<<" ERROR: ; expected but found : "<<x<<"\n";exit(0); }
		pts;
		space-=2;
		for(int i=0;i<space;i++) f<<" ";
		f<<"</varDec>\n";
		x=fil[d_count++];
	}
	d_count--;
}


void compileIfStatement(ofstream& f,ofstream& g){
	for(int i=0;i<space;i++) f<<" ";
	f<<"<IfStatement>\n";
	space+=2;
	string x;
	x=fil[d_count++];
	pts;
	x=fil[d_count++];
	if(!(sname(x)=="(")) { g<<" ERROR: ( expected but found : "<<x<<"\n";exit(0); }
	pts;
	compileExpression(f,g);
	int zx=Tlabelnum;
	Tlabelnum+=2;
	x=fil[d_count++];
	fin<<"not\n";
	fin<<"if-goto "<<Class_Symbol_table.names<<zx+1<<"\n";
	if(!(sname(x)==")")) { g<<" ERROR: ) expected but found : "<<x<<"\n";exit(0); }
	pts;
	x=fil[d_count++];
	if(!(sname(x)=="{")) { g<<" ERROR: { expected but found : "<<x<<"\n";exit(0); }
	pts;
	compileStatements(f,g);
	x=fil[d_count++];
	if(!(sname(x)=="}")) { g<<" ERROR: } expected but found : "<<x<<"\n";exit(0); }
	pts;
	x=fil[d_count++];
	if(!(sname(x)=="else")) {
		fin<<"label "<<Class_Symbol_table.names<<zx+1<<"\n";
		d_count--;
		space-=2;
		for(int i=0;i<space;i++) f<<" ";
		f<<"</IfStatement>\n";
		return;
	}
	fin<<"goto "<<Class_Symbol_table.names<<zx+2<<"\n";
	fin<<"label "<<Class_Symbol_table.names<<zx+1<<"\n";
	pts;
	x=fil[d_count++];
	if(!(sname(x)=="{")) { g<<" ERROR: { expected but found : "<<x<<"\n";exit(0); }
	pts;
	compileStatements(f,g);
	x=fil[d_count++];
	if(!(sname(x)=="}")) { g<<" ERROR: } expected but found : "<<x<<"\n";exit(0); }
	pts;
	space-=2;
	for(int i=0;i<space;i++) f<<" ";
	f<<"</IfStatement>\n";
	fin<<"label "<<Class_Symbol_table.names<<zx+2<<"\n";
}

void  compileReturnStatement(ofstream& f,ofstream& g){
	for(int i=0;i<space;i++) f<<" ";
	f<<"<ReturnStatement>\n";
	space+=2;
	string x;
	x=fil[d_count++];
	pts;
	x=fil[d_count++];
	if(sname(x)==";") {
		fin<<"push constant 0\n";
		pts;
	}
	else {
		d_count--;
		compileExpression(f,g);
		x=fil[d_count++];
		if(sname(x)!=";") { g<<"  ERROR : ; expected but found : "<<x<<"\n";exit(0); }
		pts;
	}
	fin<<"return\n";
	space-=2;
	for(int i=0;i<space;i++) f<<" ";
	f<<"</ReturnStatement>\n";
}

void compileWhileStatement(ofstream& f,ofstream& g){
	for(int i=0;i<space;i++) f<<" ";
	f<<"<WhileStatement>\n";
	space+=2;
	string x;
	x=fil[d_count++];
	pts;
	x=fil[d_count++];
	if(!(sname(x)=="(")) { g<<" ERROR: ( expected but found : "<<x<<"\n";exit(0); }
	pts;
	int zx=Tlabelnum;
	Tlabelnum+=2;
	fin<<"label "<<Class_Symbol_table.names<<zx+1<<"\n";
	compileExpression(f,g);
	x=fil[d_count++];
	fin<<"not\n";
	fin<<"if-goto "<<Class_Symbol_table.names<<zx+2<<"\n";
	if(!(sname(x)==")")) { g<<" ERROR: ) expected but found : "<<x<<"\n";exit(0); }
	pts;
	x=fil[d_count++];
	if(!(sname(x)=="{")) { g<<" ERROR: { expected but found : "<<x<<"\n";exit(0); }
	pts;
	compileStatements(f,g);
	x=fil[d_count++];
	if(!(sname(x)=="}")) { g<<" ERROR: } expected but found : "<<x<<"\n";exit(0); }
	pts;
	fin<<"goto "<<Class_Symbol_table.names<<zx+1<<"\n";
	fin<<"label "<<Class_Symbol_table.names<<zx+2<<"\n";
	space-=2;
	for(int i=0;i<space;i++) f<<" ";
	f<<"</WhileStatement>\n";
}

void compileDoStatement(ofstream& f,ofstream& g){
	for(int i=0;i<space;i++) f<<" ";
	f<<"<DoStatement>\n";
	space+=2;
	string x;
	x=fil[d_count++];
	pts;
	x=fil[d_count++];
	string cnn=sname(x);
	if(rettok(x)!="identifier") {g<<"ERROR : identifier expected but found : "<<x<<"\n";exit(0); }
	pts;
	x=fil[d_count++];
	int check=0;
	int check1=0;
	string snam;
	Entry* new_entry=new Entry;
	if(sname(x)==".") {
		check1=1;
		pts;
		x=fil[d_count++];
		new_entry=present(cnn);
		snam=sname(x);
		if(new_entry==NULL) {
			check=1;
		}
		else {
			fin<<"push "<<new_entry->sf<<" "<<new_entry->index<<"\n";
		}
		if(rettok(x)!="identifier") {g<<"ERROR : identifier expected but found : "<<x<<"\n";exit(0); }
		pts;
		x=fil[d_count++];
	}
	else {
		fin<<"push pointer 0\n";
	}
	if(sname(x)!="(") { g<<" ERROR : ( expected but found : "<<x<<"\n";exit(0); }
	pts;
	int np=compileExpressionList(f,g);
	x=fil[d_count++];
	if(!(sname(x)==")")) { g<<" ERROR : ) expected but found : "<<x<<"\n";exit(0); }
	pts;
	x=fil[d_count++];
	if(check1==1&&check==0) fin<<"call "<<new_entry->type<<"."<<snam<<" ";
	else if(check1==1) fin<<"call "<<cnn<<"."<<snam<<" ";
	else fin<<"call "<<Class_Symbol_table.names<<"."<<cnn<<" ";
	if(check) fin<<np;
    else fin<<np+1;
    fin<<"\n";
	fin<<"pop temp 0\n";
	if(sname(x)!=";") { g<<" ERROR : ; expected but found : "<<x<<"\n";exit(0); }
	pts;
	space-=2;
	for(int i=0;i<space;i++) f<<" ";
	f<<"</DoStatement>\n";
}

void compileLetStatement(ofstream& f,ofstream& g){
	for(int i=0;i<space;i++) f<<" ";
	f<<"<LetStatement>\n";
	space+=2;
	string x;
	x=fil[d_count++];
	pts;
	x=fil[d_count++];
	if(!(rettok(x)=="identifier")) {g<<"Identifier name expected but found : "<<x<<"\n";exit(0); }
	pts;
	Entry* new_entry=new Entry;
	new_entry=present(sname(x));
	if(new_entry==NULL) {g<<"Declaration ERROR : "<<sname(x)<<" undeclared ";exit(0);}
	x=fil[d_count++];
	int check=0;
	if(sname(x)=="[") {
		check=1;

		pts;
		compileExpression(f,g);
		fin<<"push "<<new_entry->sf<<" "<<new_entry->index<<"\n";
		x=fil[d_count++];
		if(!(sname(x)=="]")) { g<<" ERROR : ] expected but found : "<<x<<"\n";exit(0); }
		fin<<"add\n";
		pts;
		x=fil[d_count++];
	}
	if(!(sname(x)=="=")) { g<<"ERROR : = expected but found : "<<x<<"\n";exit(0); }
	pts;
	compileExpression(f,g);
	x=fil[d_count++];
	if(sname(x)!=";") { g<<" ERROR : ; expected but found : "<<x<<"\n";exit(0); }
	pts;
	if(check==0) {
		fin<<"pop "<<new_entry->sf<<" "<<new_entry->index<<"\n";
	}
	else {
		fin<<"pop temp 0\n";
		fin<<"pop pointer 1\n";
		fin<<"push temp 0\n";
		fin<<"pop that 0\n";
	}
	space-=2;
	for(int i=0;i<space;i++) f<<" ";
	f<<"</LetStatement>\n";
}

void compileExpression(ofstream& f,ofstream& g){
	string x;
	x=fil[d_count++];
	for(int i=0;i<space;i++) f<<" ";
	f<<"<Expression>\n";
	space+=2;
	d_count--;
	compileTerm(f,g);
	x=fil[d_count++];
	while(isop(sname(x))) {
		string snam=sname(x);
		pts;
		compileTerm(f,g);
		x=fil[d_count++];
		if(snam=="+") fin<<"add\n";
		else if(snam=="-") fin<<"sub\n";
		else if(snam=="&") fin<<"and\n";
		else if(snam=="|") fin<<"or\n";
		else if(snam=="<") fin<<"lt\n";
		else if(snam==">") fin<<"gt\n";
		else if(snam=="=") fin<<"eq\n";
		else if(snam=="*") fin<<"call Math.multiply 2\n";
		else fin<<"call Math.divide 2\n";
	}
	d_count--;
	space-=2;
	for(int i=0;i<space;i++) f<<" ";
	f<<"</Expression>\n";
}

int compileExpressionList(ofstream& f,ofstream& g){

	int coo=0;
	for(int i=0;i<space;i++) f<<" ";
	f<<"<ExpressionList>\n";
	string x;
	if(isterm(f,g)==0) {
		for(int i=0;i<space;i++) f<<" ";
		f<<"</ExpressionList>\n";
		return 0;
	}
	space+=2;
	do {
		coo++;
		compileExpression(f,g);
		x=fil[d_count++];
		if(sname(x)==",") {pts;}

	}while(sname(x)==",");
	space-=2;
	for(int i=0;i<space;i++) f<<" ";
	f<<"</ExpressionList>\n";
	d_count--;
	return coo;

}

void compileTerm(ofstream& f,ofstream& g){
	string x;
	int z=isterm(f,g);
	if(z==0) {

		return;
	}
	for(int i=0;i<space;i++) f<<" ";
	f<<"<term>\n";
	space+=2;
	x=fil[d_count++];
	if(z==1) {
		pts;
		fin<<"push constant "<<sname(x)<<"\n";
	}
	else if(z==2){
		pts;
		int l=sname(x).size();
		fin<<"push constant "<<l<<"\n";
		fin<<"call String.new 1\n";
		for(int i=0;i<l;i++){
			fin<<"push constant "<<(int)sname(x)[i]<<"\n";
			fin<<"call String.appendChar 2\n";
		}
	}
	else if(z==3){
		string zz=sname(x);
		if(zz=="true"){
			fin<<"push constant 0\nnot\n";
		}
		else if(zz=="false") fin<<"push constant 0\n";
		else if(zz=="null") fin<<"push constant 0\n";
		else fin<<"push pointer 0\n";
		pts;
	}
	else if(z==4){
		Entry* new_entry=new Entry;
		new_entry=present(sname(x));
		if(new_entry==NULL) {g<<"Declaration error : "<<sname(x)<<" undeclared";exit(0);}
		pts;
		x=fil[d_count++];
		pts;
		compileExpression(f,g);
		fin<<"push "<<new_entry->sf<<" "<<new_entry->index<<"\n";
		x=fil[d_count++];
		fin<<"add\n";
		fin<<"pop pointer 1\n";
		fin<<"push that 0\n";
		if(!(sname(x)=="]")) { g<<" ERROR : ] expected but found : "<<x<<"\n";exit(0); }
		pts;
	}
	else if(z==5){
		pts;
		fin<<"push pointer 0\n";
		string snam=sname(x);
		x=fil[d_count++];
		pts;
		int np=compileExpressionList(f,g);
		x=fil[d_count++];
		fin<<"call "<<Class_Symbol_table.names<<"."<<snam<<" ";
		fin<<np+1<<"\n";
		if(!(sname(x)==")")) { g<<" ERROR : ) expected but found : "<<x<<"\n";exit(0); }
		pts;
	}
	else if(z==6){
		int check=0;
		string cnn=sname(x);
		Entry* new_entry=new Entry;
		new_entry=present(cnn);
		pts;
		x=fil[d_count++];
		pts;
		x=fil[d_count++];
		string snam=sname(x);
		if(new_entry!=NULL){
			check=1;
			fin<<"push "<<new_entry->sf<<" "<<new_entry->index<<"\n";
		}

		if(!(rettok(x)=="identifier")) { g<<"Proper identifier expected but found : "<<x<<"\n";exit(0); }
		pts;
		x=fil[d_count++];
		if(!(sname(x)=="(")) { g<<" ERROR : ( expected but found : "<<x;exit(0); }
		pts;
		int np=compileExpressionList(f,g);
		x=fil[d_count++];
		if(!(sname(x)==")")) { g<<" ERROR : ) expected but found : "<<x;exit(0); }
		pts;
		if(!check) fin<<"call "<<cnn<<"."<<snam<<" "<<np<<"\n";
    	else fin<<"call "<<new_entry->type<<"."<<snam<<" "<<np+1<<"\n";
	}
	else if(z==7){
		string cnn=sname(x);
		Entry* new_entry=new Entry;
		new_entry=present(cnn);
		if(new_entry==NULL) {g<<"Declaration error : "<<sname(x)<<" undeclared";exit(0);}
		fin<<"push "<<new_entry->sf<<" "<<new_entry->index<<"\n";
		pts;
	}
	else if(z==8){
		pts;
		compileExpression(f,g);
		x=fil[d_count++];
		if(!(sname(x)==")")) { g<<" ERROR : ) expected but found : "<<x;exit(0); }
		pts;
	}
	else if(z==9){
		compileTerm(f,g);
		if(sname(x)=="-"){
			pts;
			fin<<"neg\n";
		}
		else if(sname(x)=="~"){
			pts;
			fin<<"not\n";
		}

	}
	space-=2;
	for(int i=0;i<space;i++) f<<" ";
	f<<"</term>\n";
}


int main(int argc,char* argv[]) {
	int ii=0;
	for(ii=2;ii<argc;ii++) {
	ifstream a;
	a.open(argv[ii]);
	ofstream b;
	b.open("out.txt");
	if(!a ||!b) ;
	else {
	    char ch,pre2=0;
	    string str;
	    while(a.get(ch)) {
	    	int h=0;
			if(ch==9 ) ;
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
	ofstream d;
	c.open("out.txt");
	d.open(rtok(argv[ii]));
	ofstream g;
	g.open(rerr(argv[ii]));
	//g<<"Hi\n";
	d<<"<tokens>\n";
	string s;
	while(getline(c,s)) {
		if(s=="\n") continue;
		int i=0,j=0;
		int ssize=s.size();
		char stt[ssize+1];
		while(j<ssize){
			if(s[j]=='\t'||(s[j]==' '&&i==0)) ;
			else if(s[j]==' '&&i!=0) {
				stt[i++]='\0';
				if(iskeyword(stt)) d<<"  <keyword> "<<stt<<" </keyword>\n";
				else if(isidentifier(stt)) d<<"  <identifier> "<<stt<<" </identifier>\n";
				else if(isintconstant(stt)) d<<"  <integerConstant> "<<stt<<" </integerConstant>\n";
				else g<<"Unidentified command : "<<stt<<" in the line : "<<s<<"\n";
				i=0;
			}
			else if(issymbol(s[j])&&i!=0) {
				stt[i++]='\0';

				if(iskeyword(stt)) d<<"  <keyword> "<<stt<<" </keyword>\n";
				else if(isidentifier(stt)) d<<"  <identifier> "<<stt<<" </identifier>\n";
				else if(isintconstant(stt)) d<<"  <integerConstant> "<<stt<<" </integerConstant>\n";
				i=0;
				d<<"  <symbol> "<<s[j]<<" </symbol>\n";
			}
			else if(issymbol(s[j])&&i==0) {
				d<<"  <symbol> "<<s[j]<<" </symbol>\n";
			}
			else if(s[j]==34) {
				if(i!=0) g<<"ERROR in command : "<<s<<"Wrong occurence of \" \n";
				else {

					j++;
					while(s[j]!=34) stt[i++]=s[j++];
					stt[i++]='\0';
					d<<"  <StringConstant> "<<stt<<" </StringConstant>\n";
					i=0;
				}
			}
			else stt[i++]=s[j];
			j++;
		}
	}
	d<<"</tokens>";
	d.close();
	c.close();
	ifstream e;
	e.open(rtok(argv[ii]));
	string x;
	fil.clear();
    while(getline(e,x)){
        fil.push_back(x);
    }
	ofstream f;
	f.open(rxml(argv[ii]));
	fin.open(rvm(argv[ii]));
	Compileclass(f,g);
	g.close();
	fin.close();
	fin.clear();
	}
	//g<<"euhoihoifhh\n";
	return 0;
}
