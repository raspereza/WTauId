#!/bin/bash

for dir in $(find -maxdepth 1 -type d -name "MET_Run2016_files")
do
    filename=${dir:2:${#dir}-8}
    echo $filename
    for i in {0..9}
    do
	hadd -f ${filename}_${i}.root ${filename}_files/*${i}.root
    done
    hadd -f ${filename}.root ${filename}_*.root
    #rm ${filename}_*.root
done

