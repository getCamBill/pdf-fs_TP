#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


#define TAILLE_BUFFER 1

int main (int argc, char **argv) {
    
        assert(argc > 1);
        
        // ouverture fichier lecture
        int fLec = open(argv[1], O_RDONLY);
        assert(fLec != -1);
        
        // ouverture fichier en ecriture
        int fEcri = open(argv[2], O_WRONLY);
        assert(fEcri != -1);

        int taille = TAILLE_BUFFER*sizeof(char);
        char *buffer; // TAILLE de 1 pour exo 1
        buffer = (char *) malloc (taille); // nb d'octet lu
        
        int posi = lseek(fLec,(off_t) 0, SEEK_END);
        printf("Taille du fichier : %d\n", posi);
        assert(posi != -1); //si -1 error et si 0 on est pas à la fin
                
        ssize_t readOctet;

        for (int i = posi-1; i >= 0;i--) {
                lseek(fLec, (off_t) i, SEEK_SET);
                readOctet = read(fLec,buffer,taille);
                assert(readOctet != -1); // -1 si error
                readOctet = write(STDOUT_FILENO, buffer,taille);
                assert(readOctet > 0); // si 0 rien écrite et -1 error
        }

        
        printf("\nFini\n");
        
        close(fLec);
        close(fEcri);
        free(buffer);


        return 0;
}
