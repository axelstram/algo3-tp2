n=$1
max=$2
nombrebase=$3
inc=$4
if [[ ($inc == 0) || ("$inc" == "") ]]; then
	let inc=10
fi
while [ $n -le $max ]
do
	nombre="$nombrebase$n"
	cat $nombre >> "todasLas$nombrebase"
	let n+=inc
done
