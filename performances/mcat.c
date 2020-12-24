#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE_BUFF atoi(argv[1]) // on défini la taille du tampon

int main (int argc, char **argv) {

        assert(argc > 2);
        // fichier de lecture
        int fd = open(argv[2], O_RDONLY);
        assert(fd != -1);
        // on se met bien au début du fichier
        long offset = 0;
        int posi = lseek(fd, (off_t) 0, SEEK_SET);
        assert(posi != -1);
        // et c'est parti !!
        int octLus, octEcrit;
        // char buffer[SIZE_BUFF];
        char *buffer;
        buffer = (char *) malloc(sizeof(SIZE_BUFF));

      while ((octLus = read(fd, buffer, SIZE_BUFF)) > 0) {
          assert(octLus > 0);
        		for (offset = 0; octLus; octLus -= octEcrit){
        			octEcrit = write(STDOUT_FILENO, buffer + offset, (size_t)octLus);
              assert(octEcrit > 0);
              offset += octEcrit;
            }
        }
        close(fd);
        free(buffer);
  return 0;
}
