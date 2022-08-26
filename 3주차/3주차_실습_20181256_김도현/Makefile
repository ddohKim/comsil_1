cc=g++ #g++ 컴파일러를 이용해서 컴파일 하겠다
target=array #실행파일 이름을 array 로 하겠다
objects=main.o array.o rangearray.o #컴파일을 위한 .o 파일 들의 모음

$(target) : $(objects) #target의 prerequisites 를 objects 로 둔다
	$(cc) -o $(target) $(objects)
#g++ -o 명령
$(objects) : Array.h RangeArray.h #header 파일이 Array.h,RagneArray.h 
.PHONY: clean #.PHONY 로 예상치 못한 오류 방지
clean : # make clean 으로 target, objects 파일 삭제
	rm $(target) $(objects)
