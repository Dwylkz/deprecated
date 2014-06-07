#!/bin/bash
for i in *; do
	#sed -i 's/Go(\(\(\w\|_\)*\), \(\(\w\|_\|->\)*\)/Go(\3, \1/g' "$i";
	#sed -i 's/CastGo(\(\(\w\|_\)*\), \(\(\w\|_\)*\), \(\(\w\|_\|->\)*\)/CastGo(\3, \5, \1/g' "$i";
	sed -i 's/key/data/g' "$i";
done;
