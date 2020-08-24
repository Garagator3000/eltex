#Написать скрипт, который контролирует выполнение какого-либо
#процесса и в случае прерывания этого процесса возобновляет его работу.
#Скрипт должен запросить периодичность проверки и имя процесса.

#! /bin/bash

echo Как часто проверять?в минутах 0-59
read m
echo Какой процесс?полный путь
read process
crontab -l >> buff
echo "*/$m * * * *  /home/alexander/eltex/linux/homework/TASK2/task4-1.sh $process" >> buff
crontab buff
rm buff