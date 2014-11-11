#!/bin/bash
n=$1
max=$2
inc=$3
if [[ ($inc == 0) || ("$inc" == "") ]]; then
	let inc=10
fi
while [ $n -le $max ]
do
	nombre="medicionesDe$n"
	./problema3 $nombre < "testsDe$n"
	let n+=inc
done
