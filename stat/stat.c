#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char **argv) {
        
        assert(argc > 1);
        /*Si le nb d'argument est ok */
        struct stat stf; 
        struct passwd *pwd;
        struct group *grp;

        int st_return; 
        char *file = argv[1];
        st_return = stat(file, &stf);
        assert(st_return != -1);
        /*Si return value == 0 */
        
        pwd = getpwuid(stf.st_uid);
        assert(pwd != NULL);
        grp = getgrgid(stf.st_gid);
        assert(grp != NULL);

        /*Ex 11*/
        printf("Fichier : %s\n", file);
        printf("Taille  : %ld     ", stf.st_size);
        printf("Blocs : %lld    ", stf.st_blocks);
        printf("Blocs d'E/S : %ld    ", stf.st_blksize);
        printf("Périphérique : %ld\n", stf.st_dev);
        //printf("Mode %d    ", stf.st_mode);
        printf("Mode (en octale) %o  ", stf.st_mode);// %o suffisant ??
        printf("Numéro inode : %ld    ", stf.st_ino);
        printf("\nNombre de liens physiques : %ld\n", stf.st_nlink);
        printf("Type de périphérique  : %ld\n", stf.st_rdev);
        printf("\nAccès : %s \n",ctime((const time_t * )&stf.st_atim));
        printf("Modification : %s  \n",ctime((const time_t * )&stf.st_mtim));
        printf("Changement : %s  \n",ctime((const time_t * )&stf.st_ctim));
        /*Ex 12*/
            
       
        printf("Type de fichier :  ");
        switch (stf.st_mode & S_IFMT) {
        case S_IFDIR: printf("repertoire\n");  break;
        case S_IFIFO:  printf("tube\n");  break;
        case S_IFLNK:  printf("sof-link\n");  break;
        case S_IFREG:  printf("fichier ordinaire\n");  break;
        default:       printf("type non trouvé\n");  break;
        }

        /* Ex 13*/


         printf("Login : %s      ",pwd->pw_name);
         printf("Groupe  : %s\n", grp->gr_name);


        return 0;
}
