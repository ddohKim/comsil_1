#include "Str.h"
#include <cstring>
#include <iostream>
using namespace std;
Str::Str(const char *string) //str 을 초기화하는 과정이다
{
len=strlen(string); //len 에 str의 문자열 길이를 저장한다
str=new char[len+1];
 //str을 len에 맞는 배열로 만든다.마지막 \0을 넣기위해.+1해줌
strcpy(str, string); //str 배열에 string 문자열을 대입한다
}

Str::Str(int char_length) //문자열 길이를 받아 len과 str에 저장
{
if(char_length>=0)
{len=char_length; //문자열 길이를 len에 저장
str=new char[char_length+1];//문자열 길이만큼 str의 문자열 배열만듬
}
else cout<<"Error: length is not negative"<<endl; //문자열 길이가 0보다 작으면 에러 발생
}
Str::~Str(){
delete []str; //소멸자에서 delete [] 를 사용해 str 배열을 삭제한다
}

int Str::length(){
return len; //length함수 호출시 len(문자열길이)을 리턴한다
}

char* Str::contents(void){
return str; //contents 함수 호출 시 string 내용을 리턴한다
}
int Str::compare(class Str& a)
{
return strcmp(str,a.contents()); 
//class Str& a이기 때문에 conents 함수를 호출해 strcmp를 이용하여 비교한다
}
int Str::compare(const char *a)
{
return strcmp(str,a);
//여기서는 *a 이기 때문에 문자열 바로 contents함수 호출 없이 비교 가능하다
}
void Str::operator=(const char *a) //연산자 다중정의 = 
{
delete [] str; //str 배열 삭제 후 다시 넣기 위해
len=strlen(a); //*a 가 들어와서 len에 *a 길이를 넣어줌
str=new char[len+1]; //새로운 배열을 만듬
strcpy(str,a); //strcpy를 이용해 str에 a 를 복사한다
}
void Str::operator=(class Str& a)
{
delete [] str; //str 배열  삭제 후 다시 넣기 위해
len=a.length(); //a의 길이를 length 함수를 호출해 받아와 len에 저장
str=new char[len+1];//새로운 str배열을 만듬
strcpy(str,a.contents());
//str에 contents 함수를 호출해 strcpy를 이용해 복사한다
}
