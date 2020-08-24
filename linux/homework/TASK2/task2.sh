#Модернизировать скрипт выше, добавив в него возможность пользователю
#выбирать место расположения папок, их количество, шаблон имени и т.д.
#! bin/bash

echo Введи каталог
read catalog
echo Сколько папок?
read folder
echo Сколько подпапок?
read subFolder
echo Сколько файлов?
read files
#Можно до бесконечности спрашивать у пользователся данные для работы, мне кажется достаточно.
mkdir $catalog
cd $catalog
for((I=1;I<$folder+1;I++))
do
    mkdir $I
    cd $I
    for((K=1;K<$subFolder+1;K++))
    do
        mkdir $K
        cd $K
        for((J=1;J<$files+1;J++))
        do 
            touch $J
        done
        cd ..
    done
    cd ..
done