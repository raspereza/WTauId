#!/bin/sh

# This script loops over all folders in directory and checks if there is a *.root file in these folders that is corrupted. If it is it is resubmitted.

for dir in $(find -maxdepth 1 -type d -name "*_files")
do
    echo $dir
    cd $dir
    for file in $(ls *.zsh)
    do
	list=$(echo $file | sed 's/.zsh//g')
	echo $list
	checkRoot ${list}.root
	exit=$?
	if [[ $exit -ne 0 ]]; then
	   echo "resubmit" $list
	   echo reason $exit

	   params=$(while read line; do if [[ -n $line ]]; then if [[ ${line::1} != "#" ]]; then echo ${line}; break; fi; fi; done < $file)
	   stringarray=($params)
	   echo $params
	   ./qsub.sh "${stringarray[0]}" "${stringarray[1]}" "${stringarray[2]}"
	fi
    done
    cd ../
done
   
