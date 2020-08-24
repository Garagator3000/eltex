#Написать скрипт: будильник (в нужный момент проиграть музыку, скрипт
#запрашивает время срабатывания и файл который надо проиграть).

#! /bin/bash
d=''
echo -n "В какой день вас разбудить? (гггг-мм-дд)"
read d
h=''
echo -n "В какой час вас разбудить? (чч)"
read h
declare -i m=''
echo -n "Во сколько минут избранного часа вас разбудить? (мм)"
read m
declare -i z=0
if m -eq 59
then
    z=$m+2
else
    z=$m+1
fi
echo "$d $h:$m"
echo "$z"
u=$(date +%s -d "$d $h:$m")
echo "$u"
echo "DISPLAY=:0 $m $h * * *  /home/alexander/eltex/linux/homework/TASK2/task3.sh" |crontab -
sudo rtcwake -m mem -t $u
mpg123 ~/Музыка/alarm.mp3