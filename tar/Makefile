CC=gcc
CFLAGS=-Wextra -Wall #-ansi -pedantic

all: lstar geneTestFiles tests

geneTestFiles:
	#
	# ** Création des fichiers pour tester ./lstar
	rm -rf vide;touch vide;rm -rf test;touch test;
	# ** On insère des caractères dans le fichier test
	echo "azerty" > test;
	#
	#  Création de l'archive (valide)
	rm -rf archive_valide.tar;
	tar -H ustar -c vide test > archive_valide.tar;
	#
	#  ** Création de l'archive (corrompue)
	#  en supprimant les 4 premiers caractères (octets)
	rm -rf archive_corrompue.tar;
	tail -c +5 archive_valide.tar > archive_corrompue.tar
	#

lstar: lstar.c
	$(CC) $(CFLAGS) lstar.c -o lstar

tests:
	# ** Version POSIX pour lister le contenu des archives
	# sans ./lstar :
	tar -tv < archive_valide.tar;
	#
	# -------------------------------
	#  Test avec ./lstar :
	# -------------------------------
	#  Sans pipe :
	#
	#  l'archive valide :
	#
	./lstar archive_valide.tar;
	#
	#  l'archive corrompue :
	#
	./lstar archive_corrompue.tar;
	#
	# -------------------------------
	#  Avec pipe :
	#
	tar -H ustar -c vide test README.md Makefile | ./lstar
	#
	tar -H ustar -c README.md Makefile vide test | ./lstar
	#
	tar -H ustar -c README.md vide test Makefile | ./lstar
	#

clean:
	rm -rf lstar

karcher:
	rm -rf lstar;rm -rf archive_valide.tar;
	rm -rf archive_corrompue.tar;
	rm -rf vide;rm -rf test;

.PHONY: all
