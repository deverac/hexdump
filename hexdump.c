#include <stdio.h>
#include <stdlib.h>

#if !defined(uint)
    typedef unsigned int uint;
#endif

int
main ( int argc, char** argv )
{
    char ch;
    uint i;
    uint k;
    FILE * fp;
    char * fname;
    char asc[17]; // 16 + 1 for null.

    if (argc < 2) {
        printf("Display file in hex+ASCII format. A file must be provided.\n");
        exit(1);
    }
    
    fname = argv[1];
    asc[16] = '\0';
    if (( fp = fopen(fname, "rb") )) {
        i = 0;
        while (1) {
            ch = fgetc(fp);
            if (feof(fp)) {
                break;
            }
            if (i % 16 == 0) {
                if (i > 0) {
                    printf(" |%s|\n", asc);
                }
                printf("%08x  ", i);
            }
            if (i % 16 == 8) {
                printf(" ");
            }
            asc[i%16] = (ch < 32 || ch > 126 ? '.' : ch);
            printf("%02x ", ch);
            i++;
        }
        if (i % 16 > 0) {
            asc[(i % 16) + 0] = '\0';
        }
        k = i;
        while (k % 16 != 0) {
            printf("   ");
            k++;
        }
        if (i % 16 <= 8 && i % 16 > 0) {
            printf(" ");
        }
        printf(" |%s|\n", asc);

        printf("%08x  ", i);
        printf("\n");
        fclose(fp);
    } else {
        printf("Error opening %s\n", fname);
        return 1;
    }
    return 0;
}
