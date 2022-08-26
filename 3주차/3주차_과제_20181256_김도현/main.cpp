#include "Str.h"
#include <iostream>
using namespace std;

int main()
{ 
Str a("I'm a girl"); //I'm a girl a 배열로 초기화
cout << a.contents(); //내용 출력
a="I'm a boy\n"; //I'm a boy로 a 배열 바꿈
cout << a.contents(); //내용 출력
cout << a.compare("I'm a a") << endl; //I'm a a 와 a 배열 비교(다름)
cout <<"\na.length: "<< a.length()<<endl; //a 배열 길이 출력
Str b("Hi"); //b 배열 hi 로 초기화
cout <<"b.contents: "<<b.contents()<<endl; //b 배열 내용 확인
cout <<"b.length: "<<b.length()<<endl; //b 배열 길이 확인
a=b; //a 배열에 b 배열 넣기
cout <<"a=b, a.contents: "<< a.contents()<<endl; //a 배열 내용 확인
cout << "a==b??: "<<a.compare(b)<<endl; //a 배열과 b배열 비교(같음)
Str c(""); //아무것도 없는 c 배열 초기화
cout<< "\nc.length: "<<c.length()<<" c.contents: "<<c.contents()<<endl;
//c 배열 길이, 내용 확인
cout <<"\nd(-1)"<<endl; //길이가 음수일때 확인
Str d(-1); //길이가 음수일때 에러 메세지 나오는지 확인
return 0;
}

