#! bin/bash
ps aux | grep $1 > buffer.txt
if [ -s buffer.txt ]
then
    rm buffer.txt
else
    exec -a $1
    rm buffer.txt
fi