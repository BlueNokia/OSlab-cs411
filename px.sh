#!/bin/bash

#2
sudo fdisk -l
fdisk=$(sudo fdisk -l)
echo

#count number of : in PATH variable
var=`echo $fdisk | grep -o "^/" | wc -l`
n=`expr $var + 1`

#fetching each coloumn
for (( i=1; i <= $n; i++ ))
do
	info1=($(sudo fdisk -l | grep '^/dev' | cut -d ' ' -f1))
	info2=($(sudo fdisk -l | grep '^/dev' | cut -d ' ' -f2))
	info3=($(sudo fdisk -l | grep '^/dev' | cut -d ' ' -f3))
	info4=($(sudo fdisk -l | grep '^/dev' | cut -d ' ' -f4))
	info5=($(sudo fdisk -l | grep '^/dev' | cut -d ' ' -f5))
	info6=($(sudo fdisk -l | grep '^/dev' | cut -d ' ' -f6))	
done

for((i=0 ; i<8 ; i++));do
	echo "Partition:: ${info1[$i]}  Start Sector:: ${info2[$i]}  End Sector:: ${info3[$i]}  No of Sector:: ${info4[$i]}  Partition Size:: ${info5[$i]}  Partition Type:: ${info6[$i]}"
done


#3
echo "Access | Items|Author|Editor|Size(B)|Last updated|File name " 
ls -l Documents --color=auto

#4
grep -R "vendor_id" "/proc/cpuinfo"| sed -n 1p

grep -R "model name" "/proc/cpuinfo"| sed -n 1p

grep -R "cpu" "/proc/cpuinfo"| sed -n 1p

grep -R "cache size" "/proc/cpuinfo"| sed -n 1p


#5
a=`uname -s`
b=`uname -r`
c=`uname -o`
d=`uname -v`
echo "Kernel Name: $a"
echo "Kernel Release: $b"
echo "OS: $c"
echo "OS Version: $d"


#6
du --time -c -a -h /home/student/Downloads/java_assign
