# BILLOUARD Camille GR2B

# Marche à suivre

## Pour l'éxécution :        
        make stat
## Pour supp l'exec :
        make karcher

# Ex 5 
        Resultat de la cmd stat test.txt 

  Taille : 32        	Blocs : 1          Blocs d'E/S : 1048576 fichier
Périphérique : 2fh/47d	Inœud : 330         Liens : 1
Accès : (0777/-rwxrwxrwx)  UID : (    0/    root)   GID : (    0/    root)
Accès : 2020-09-13 12:53:04.268702900 +0200
Modif. : 2020-09-13 12:53:05.570575400 +0200
Changt : 2020-09-13 12:53:04.268702900 +0200
  Créé : -

# Ex 6
        cmd whatis stat

 stat (2)             - Obtenir l'état d'un fichier (file status)
stat (1)             - display file or file system status

# Ex 7 
       - l'appel syst stat() permet d'obtenir les meta données des inode
       - représenté par un struct stat 
       - Le  champ Blocs indique le nombre de blocs de 512 octets alloués au fi‐
       chier.Et le Blocs E/S donne  la  taille  de bloc « préférée » pour des en‐
       trées-sorties efficaces.
      
# Ex 8
        
        // Partie valable la semaine dernière ...
        Pour l'ajour du texte, étant donné qu'un bloc s'incrémente si size > 512o, 
        on execute le script suivant : 
        Comme une lettre (ici 'l') est codé sur 1o on en insère 512

               $ for l in {1..512};do echo -e 'l\c' >> test.txt ; done && stat test.txt 
        
                Bloc = 1

             et on ajoute une 513ème lettre (donc 513o) 
                echo -e 'l\c' >> test.txt
             Bloc = 2, ici le bloc augmente de 1 car les blocs sont alloués
             par 512o et ici nous dépassons de 1 donc le bloc augmente de 1
        
        // MAJ suite à réxécution de ./stat  
        apres réexcution de ./stat on voit que cela augmente de 8 en 8 et cela est dû 
        au   fait que les Bloc d'E/S sont de 4096 ce qui correespond à 512 * 8
# Ex 9 
             fait 
             issues : pb rencontré car linux sur Vbox avec le partage de fichier avec 
             l'hôte ne permet pas les liens symbolique car droits 
             solutions : (provisioire) travailler dans un autre dir et cp les files
             en fin. (car push git à partir de l'hôte (windows)).

# Ex 10
        Le nb de liens de test.txt et son lien physque ont le même nb de liens
        Le liens symbolique ne contient qu'un seul lien car un seul physique 
        
        Aprés une supp du file d'origine : 
         - hard link : texte present
         - soft link : aucun fichier ...
         - cp : texte present
      
## Implémentation 


#Ex 11

         Lors de la comilation : 
