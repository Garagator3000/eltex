#! bin/bash
#Скриптом на BASH, создать 50 папок в указанной, в каждой из 50ти папок
#создать еще 100 подпапок, и в каждой из этих подпапок создать 200 пустых
#файлов.

mkdir testcycle
for((I=1;I<51;I++))
do
    mkdir $I
    cd $I
    for((K=1;K<101;K++))
    do
        mkdir $K
        cd $K
        for((J=1;J<201;J++))
        do 
            touch $J
        done
        cd ..
    done
    cd ..
done