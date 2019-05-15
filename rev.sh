#!/bin/bash
read -p "Enter string:" string
len=${#string}
for (( i=$len-1; i>=0; i-- ))
do
# "${string:$i:1}"extract single single character from string.
reverse="$reverse${string:$i:1}"
done
echo "The reversed string is :: $reverse"
# chmod u+x scriptname
#./scriptname
