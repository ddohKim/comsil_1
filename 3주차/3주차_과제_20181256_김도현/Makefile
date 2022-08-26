cc=g++ #g++ 를 이용하여 컴파일하겠다
target=a.out #실행파일을 a.out 으로 하겠다
objects=main.o Str.o #컴파일을 위한 .o 파일들의 모음

$(target) : $(objects) #target의 prerequisites 를 objects로 둠
	$(cc) -o $(target) $(objects)
#g++ -o 명령어
$(objects) : Str.h #header 파일은 Str.h 이다
.PHONY : clean #.PHONY 를 사용해 오류를 방지한다
clean : #make clean 을 사용해 target 파일과 object파일들을 삭제시킨다
	rm $(target) $(objects)

