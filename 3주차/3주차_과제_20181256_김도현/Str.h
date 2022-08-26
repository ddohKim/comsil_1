class Str
{
private :
        char *str; //string의 내용을 저장하는 배열이다
        int len; // string의 길이를 저장하는 변수이다
public :
        Str(int leng); //leng은 string 길이를 의미한다
        Str(const char *neyong); //neyong 에 초기화하는 내용이 들어간다
        ~Str(); //소멸자로 str 배열을 삭제시킨다
        int length(void);//string의 길이를 return 한다
        char *contents(void); //string의 내용에 대해 return 한다
        int compare(class Str& a); //문자열읠 비교한다(strcmp)
        int compare(const char *a); //문자열을 비교한다(strcmp)
        void operator=(const char *a); //string의 값을 넣는다
        void operator=(class Str& a); //Str의 내용을 넣는다
};
