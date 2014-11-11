dividendo=3

n=$1
max=$2
inc=$3
if [[ ($inc == 0) || ("$inc" == "") ]]; then
	let inc=10
fi
while [ $n -le $max ]
do
	nombre="testsDe$n"
	./genRan $nombre $n $(($n/$dividendo)) $(($n/$dividendo)) 100
	let n+=inc
done
