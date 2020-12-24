#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define MAX_DATE_SIZE 64
#define SIZE_BUFFER 512
#define TMAGIC   "ustar"

typedef struct {
    /* Byte offset    Field type                 */
  char name[100];            /*   0    NUL-terminated if NUL fits */
  char mode[8];              /* 100                               */
  char uid[8];               /* 108                               */
  char gid[8];               /* 116                               */
  char size[12];             /* 124                               */
  char mtime[12];            /* 136                               */
  char chksum[8];            /* 148                               */
  char typeflag;             /* 156    see below                  */
  char linkname[100];        /* 157    NUL-terminated if NUL fits */
  char magic[6];             /* 257    must be TMAGIC (NUL term.) */
  char version[2];           /* 263    must be TVERSION           */
  char uname[32];            /* 265    NUL-terminated             */
  char gname[32];            /* 297    NUL-terminated             */
  char devmajor[8];          /* 329                               */
  char devminor[8];          /* 337                               */
  char prefix[155];          /* 345    NUL-terminated if NUL fits */
                             /* 500                               */
/* If the first character of prefix is '\0', the file name is name;
   otherwise, it is prefix/name.  Files whose pathnames don't fit in
   that length can not be stored in a tar archive.  */
}POSIX_HEADER;

long arrondi512 (long n) {
    int reste = n%512;
    int partEnt = n/512;

    return (reste != 0) ? partEnt*512+512 : n;
};

char* permission(int value) {
    char* answer = NULL;
    switch(value) {
      case 0:  answer = "---"; break;
      case 1:  answer = "--x"; break;
      case 2:  answer = "-w-"; break;
      case 3:  answer = "-wx"; break;
      case 4:  answer = "r--"; break;
      case 5:  answer = "r-x"; break;
      case 6:  answer = "rw-"; break;
      case 7:  answer = "rwx"; break;
      default: printf("ERROR");
    }

    return answer;
}

int verifChksum(POSIX_HEADER * header) {
  char *posixStructure = (char *) header;
  int res = 0;

  for (int i = 0; i < 512; i++) {
    res += (148 <= i && i < 156) ? ' ' : posixStructure[i];
  }
  return res;
}

int main(int argc, char *argv[]) {

    int fd, sizeBuff, posi;
    int i =0;
    long offset = 0;
    if (argc > 1) {
      fd = open(argv[1], O_RDONLY);
      assert(fd != -1);
      posi = lseek(fd, (off_t) offset, SEEK_SET);
      assert(posi != -1);

    } else { // si pipe
      fd = STDIN_FILENO;
    }
      int verif = 1;
      POSIX_HEADER s;
      sizeBuff = arrondi512(sizeof(s));
      while (read(fd, &s, sizeBuff) > 0) {

          //Lecture
          if ((!strcmp(s.magic,TMAGIC)) && strtol(s.chksum,NULL,8)==verifChksum(&s)) {
          // seul moyen pour message fichier corrompu
          verif = 0;
          //Mode
          int mode = atoi(s.mode);
          int value1 = mode / 100;
          int value2 = (mode - value1 * 100) / 10;
          int value3 = (mode - value1 * 100 - value2 * 10);
          printf("-%s%s%s",permission(value1), permission(value2), permission(value3));
          //GID Group name
          printf("  %s/%s  ", s.gid, s.gname);
          //Size
          long sizeFile = strtol(s.size, NULL, 8);
          printf("       %ld", sizeFile);
          //Date
          char date[MAX_DATE_SIZE];
          unsigned long timesF = difftime(strtol(s.mtime,NULL,8), 0);
          struct tm *ptrTime = localtime( (const time_t *) &timesF);
          strftime(date, MAX_DATE_SIZE, "%Y-%m-%d %H:%M", ptrTime);
          printf(" %s ", date);
          //Name
          printf(" %s\n", s.name);
        }
         if (argc > 1) {
           i+=sizeBuff;
           posi = lseek(fd, (off_t) offset+i, SEEK_SET);
           assert(posi != -1);
         }
      }
      if (argc > 1 ) {close(fd);}
      if (verif) {
        printf("Fichier corrompu verif=%d  chksum=%ld\n", verifChksum(&s),strtol(s.chksum,NULL,8));
        printf("tar: Ceci ne ressemble pas à une archive de type « tar »\n");
        printf("tar: On saute à l'en-tête suivant\n");
        printf("tar: Arrêt avec code d'échec à cause des erreurs précédentes\n");
      }

    return EXIT_SUCCESS;
}
