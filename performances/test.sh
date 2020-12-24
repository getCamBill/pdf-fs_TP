#!/bin/bash
# Exemple de script shell qui mesure le temps d'éxécution de
# "./perf" avec des arguments différents

TEMP=temp
TEMP1=temp1
FINAL=final.dat
BIG_FILE=fichier_a_creer

dd if=/dev/zero of=$BIG_FILE bs=1k count=50000

rm -rf $FINAL
touch $FINAL

for ((i = 1; i <= 8388608; i *= 2)); # ~= à 8 000 000o
  do
    /usr/bin/time -f '%U\n%S' -o $TEMP ./mcat "$i" $BIG_FILE > /dev/null
    paste -sd+ $TEMP | bc > "$TEMP1"
    echo -e "$i $(cat "$TEMP1")" > "$TEMP1"
    cat "$TEMP1" >> "$FINAL"
  done
  # ni vu ni connu on supp les fichiers ...
    rm $TEMP
    rm $TEMP1
    rm $BIG_FILE
sed -i '1s/^/# buffSize user+sys\n/' $FINAL

gnuplot run.gnu

rm $FINAL
