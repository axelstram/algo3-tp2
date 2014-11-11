dividendo=3

n=$1
max=$2
inc=$3
if [[ ($inc == 0) || ("$inc" == "") ]]; then
	let inc=10
fi
while [ $n -le $max ]
do
	nombre="testsDificilesDe$n"
	./genConst $nombre $n 1 $(($n/$dividendo)) 100
	let n+=inc
done
