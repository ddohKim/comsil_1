echo 'Working directory:'
read dirname
if [ -n "$dirname" ] #입력 유무
then
        if [ -d $dirname ] #디렉토리 존재 유무
        then
                if [ -x $dirname ] #접근가능한 파일인지 확인 
                then
                        cd $dirname
                else
                        echo "Error, No directory Permission" 
                        exit 1
                fi
        else
                echo "Error, No directory"
                exit 1
        fi
fi
for dir in *
do
        if [ -f $dir ] # 파일인지 체크
        then
                newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
                mv $dir $newname
        fi
done
