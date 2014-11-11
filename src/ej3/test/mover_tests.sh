n=$1
max=$2
nombrebaseori=$3
nombrebasedest=$4
inc=$5
if [[ ($inc == 0) || ("$inc" == "") ]]; then
	let inc=10
fi
while [ $n -le $max ]
do
	nombreori="$nombrebaseori$n"
	nombredest="$nombrebasedest$n"
	mv $nombreori $nombredest
	let n+=inc
done
