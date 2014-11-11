dividendo=3

n=$1
max=$2
inc=$3
if [[ ($inc == 0) || ("$inc" == "") ]]; then
	let inc=10
fi
while [ $n -le $max ]
do
	nombre="testsFacilesDe$n"
	./genConst $nombre $n $n 0 100
	let n+=inc
done
