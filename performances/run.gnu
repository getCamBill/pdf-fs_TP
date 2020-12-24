set title "Temps et vitesse d'execution"
set logscale x
set xlabel "taille buffer en octets"
set logscale y
set ylabel "temps en s ou vitesse en octets/s"
set style data linespoints
plot "final.dat" using 1:2 title "temps", \
     "final.dat" using 1:3 title "vitesse"
pause -1  "Hit return to continue"
