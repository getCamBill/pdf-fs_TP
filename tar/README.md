# BC² aka BILLOUARD Camille BEVILACQUA Cedric

#   Décodage du format `tar`

## Protocole

Le principe est de lire la structure pour chaque fichier au sein d'une boucle jusqu'à arriver à la fin de celui-ci.

Pour chaque structure lue, on affiche le contenu des éléments de la structure ainsi que le mode du fichier, qui est en octal, avec l'utilisation d'une fonction pour convertir le mode en écriture rwx (utilisateur).

Pour l'avancée dans le fichier, on utilise à chaque fois un lseek si le fichier est passé en argument et on effectue un read vide pour faire avancer le curseur dans le cas d'un pipe.

Pour savoir, on vérifie le nombre d'arguments, dans le cas d'un pipe et  d'un argument, on prend donc l'argument en priorité et le pipe uniquement si il n'y a pas d'argument.

L'ouverture du fichier n'est pas non plus la même au début du script si le fichier vient d'un pipe ou d'un paramètre. Pour le pipe, le numéro est directement pris dans la sortie standard, pour un paramètre, le fichier est d'abord ouvert avec open pour obtenir son numéro d'adresse.

A la fin de la boucle, on vérifie la validité du fichier pour vérifier si il n'est pas corrompue.

Nous avons testé avec des fichiers vides dans l'archive, un ou plusieurs fichiers différents dans l'archive, une archive corrompue... les tests sont réalisés dans les commandes ci-dessous.

### Initialisation

Tout d'abord cloner le repo : 
```bash
cd ~
git clone https://gitlab-etu.fil.univ-lille1.fr/billouard/pds-fs.git
cd pds-fs/tar/
```

#### Etapes 

Pour lancer en une seule fois la compilation, l'execution et les différends tests : 
```bash
make all
```

OU 

Pour compiler lstar : 
```bash
make lstar
```
Pour générer les tests de lstar avec et sans pipe. (Comprends la création de fichiers, d'archive valide et corrompue)
```bash
make geneTestFiles 
```
Puis pour lancer les tests :
```bash
make tests
```