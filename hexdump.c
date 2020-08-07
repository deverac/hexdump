#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(uint)
    typedef unsigned int uint;
#endif


#define MAX_X   80
#define MAX_Y   24
#define ITEMS  128

#define TEXT_LEN 5

#define STD_CHART 0
#define EXT_CHART 1

int
dumpfile( char * fname )
{
    char ch;
    uint i;
    uint k;
    FILE * fp;
    char asc[17]; // 16 + 1 for null.

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


// Modifies buf to hold a string representation of val.
// Assumes buf can hold, at least, 4 chars.
void
val_to_str( int val, char * buf )
{
    char names[][4] = {
        "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
        "BS",  "TAB", "LF",  "VT",  "FF",  "CR",  "SO",  "SI",
        "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
        "CAN", "EM",  "SUB", "ESC", "FS",  "GS",  "RS",  "US",
        "spc"
    };
    if (val <= ' ') {
        sprintf(buf, "%s", names[val]);
    } else if (val == 127) {
        sprintf(buf, "DEL");
    } else {
        sprintf(buf, "%c", val);
    }
}


int
get_text_width( int chart, int col )
{
    int width;
    int pad = 4;

    if (chart == EXT_CHART) {
        return 1 + pad;
    }

    if (col <= 1) {
        width = 3 + pad;
    } else if (col == 5) {
        width = 3;
    } else {
        width = 1 + pad;
    }
    return width;
}


int
get_val_width( int chart, int col )
{
    if (chart == EXT_CHART) {
        return 3;
    }
    return (col >= 4 ? 3 : 2);
}

void
print_binary_str(int val)
{
    int i;
    printf("    %X  ", val);
    for (i = 8; i >= 1; i >>= 1) {
        printf("%c", (val & i ? '1' : '0'));
    }
}


int
print_ascii_grid( int chart )
{
    int cols = ITEMS / MAX_Y;
    int col;
    int row;
    int val;
    int val_width;
    char text[TEXT_LEN];
    int text_width;
    int limit = (chart == STD_CHART ? 128 : 256);

    if (ITEMS % MAX_Y > 0) {
        cols += 1;
    }
    for (row = 0; row < MAX_Y; row++) {
        for (col=0; col<cols; col++) {
            val = row + (col * MAX_Y) + (limit - 128);
            val_width = get_val_width(chart, col);
            text_width = get_text_width(chart, col);
            if (val < limit) {
                val_to_str(val, text);
                printf("%*d x%02X %-*s", val_width, val, val, text_width, text);
            } else {
                print_binary_str(val-limit);
            }
        }
        printf("\n");
    }
    return 0;
}


void
help( char * progname )
{
    printf("Display file in hex+ASCII format. Or display an ASCII chart.\n");
    printf("Usage: %s [/E] [/H] [/?]\n", progname);
    printf("       %s FILENAME\n", progname);
    printf("\n");
    printf("            If no option is supplied, display Standard ASCII chart (0-127)\n");
    printf("  /E        Display Extended ASCII chart (128-255)\n");
    printf("  /H, /?    Display this help\n");
    printf("  FILENAME  File to display in hex+ASCII format\n");
    printf("\n");
    printf("A binary table of values 0-0xF is also printed with each ASCII chart.\n");
    printf("The characters displayed in the Extended ASCII chart will depend on the\n");
    printf("codepage that is currently loaded. The DOS command 'CHCP' will display the\n");
    printf("current codepage.\n");
}


int
main ( int argc, char** argv )
{
    if (argc == 1) {
        return print_ascii_grid(0);
    }

    if (strcmp(argv[1], "/h") == 0 || strcmp(argv[1], "/H") == 0 || strcmp(argv[1], "/?") == 0) {
        help(basename(argv[0]));
        return 0;
    } else if (strcmp(argv[1], "/a") == 0 || strcmp(argv[1], "/A") == 0) {
        return print_ascii_grid(STD_CHART);
    } else if (strcmp(argv[1], "/e") == 0 || strcmp(argv[1], "/E") == 0) {
        return print_ascii_grid(EXT_CHART);
    } else {
        return dumpfile(argv[1]);
    }
}
