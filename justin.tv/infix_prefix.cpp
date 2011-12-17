#define INFIX_PREFIX
#ifdef INFIX_PREFIX

#include <iostream>
#include <string>
#include <fstream>
#include <stack>
using namespace std;

enum SYM {LP,RP,ADD,MULT};
int getPrec(char c);
//O(n) n is length of infix expression
bool in2prefix(char in[],char pre[]){
	size_t i=0,j=0;
	int prec = 0;
	stack<char> s1,s2;
	int len = strlen(in);
	bool alpha = false;
	//calculate from back
	for(int i = len - 1; i >= 0; i--){
		if(in[i]==' ') continue;
		if(isalpha(in[i])) alpha = true;
        switch(in[i]){
            case ')':
                s1.push(in[i]);
                break;
            case '(':
				while(!s1.empty()&&s1.top() != ')'){
                     s2.push(s1.top());
                     s1.pop();
                 }
                 s1.pop();
                 break;
            case '-':  
			case '+': 
			case '*':
			case '/'://symbols
				while(!s1.empty()&&getPrec(s1.top()) > getPrec(in[i])){
                    s2.push(s1.top());
                    s1.pop();
                }
                s1.push(in[i]);
                break;
            default:
                s2.push(in[i]);
                break;
        }
    }
    while(!s1.empty())
    {
        s2.push(s1.top());
        s1.pop();
    }
	int k=0;
    while(!s2.empty())
    {
		pre[k++] = s2.top();
        s2.pop();
    }
	return alpha;
}

int getPrec(char c){
	switch(c){
	case '(':
		return LP;
	case ')':
		return RP;
	case '+':
		return ADD;
	case '-':
		return ADD;
	case '/':
		return MULT;
	case '*':
		return MULT;
	case '%':
		return MULT;
	}
	return 40;
}

//O(N) N is length of prefix length
int evaluate(char prefix[]){
	stack<int> num;
	for(int i=strlen(prefix)-1;i>=0;i--){
		if(getPrec(prefix[i])!=40){
			int a = num.top();
			num.pop();
			int b = num.top();
			num.pop();
			int c = 0;
			switch(prefix[i]){
			case '*':
				c = a * b;
				break;
			case '+':
				c = a + b;
				break;
			case '-':
				c = a - b;
				break;
			case '/':
				c = a/b;
				break;
			}
			num.push(c);
		}else num.push(prefix[i]-'0');
	}
	return num.top();
}

int main(int argc,char* argv[]){
	char *fileName = argv[1];
	//std::cout<<argv[1]<<std::endl;
	ifstream file;
	if(argv[1]!=NULL)
		file.open(argv[1]);
	else file.open("infix.txt");
	char output[100]={0};
	string line;
	while (getline(file,line)) {
		char prefix[100]={0};
		char output[100]={0};
		std::copy(line.begin(),line.end(),output);
		char result[100] ={0};
		bool status = in2prefix(output,prefix);
		//do not need reduce just output formula.
		if(argv[2]==NULL||status){
			std::cout<<prefix<<std::endl;
		}else{
			//we could evalute result
			std::cout<<evaluate(prefix)<<std::endl;
		}
	}
}
#endif