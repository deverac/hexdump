#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(uint)
    typedef unsigned int uint;
#endif


#define SCREEN_POS(LINE, COL) (((LINE) * 80 + (COL)) * 2)
#define IS_EQ(A, B) (strcmp((A), (B)) == 0)

#define MAX_ROWS   24
#define COLS        6


// Arbitrary constants
#define PAGE_0   300  // displays chars   0-127
#define PAGE_1   301  // displays chars 128-255


// The cp437 array does not contain all 256 characters. This OFFSET allows
// high index values (e.g. 252) to stay within the array bounds. The OFFSET
// is derived from (0x7f - 0x20).
#define ARY_OFFSET  0x5f

typedef struct options {
    int help;
    int page;
    int omit_final_nl;
    int omit_chars;
} options;

#if defined(LINUX)
// UTF-8 representations of Code Page 437 characters. Only non-alphanumeric
// characters are included. Most characters are three bytes. Many characters
// are two bytes; two-byte characters have a third null byte added for padding.
char cp437[] = {
    0x00, 0x00, 0x00, // x00 (not used; padding)
    0xe2, 0x98, 0xba, // x01 white smile
    0xe2, 0x98, 0xbb, // x02 black smile
    0xe2, 0x99, 0xa5, // x03 heart
    0xe2, 0x99, 0xa6, // x04 diamond
    0xe2, 0x99, 0xa3, // x05 club
    0xe2, 0x99, 0xa0, // x06 spade
    0xe2, 0x80, 0xa2, // x07 bullet
    0xe2, 0x97, 0x98, // x08 invert bullet
    0xe2, 0x97, 0x8b, // x09 white circle
    0xe2, 0x97, 0x99, // x0a black circle
    0xe2, 0x99, 0x82, // x0b male
    0xe2, 0x99, 0x80, // x0c female
    0xe2, 0x99, 0xaa, // x0d eigth
    0xe2, 0x99, 0xab, // x0e beamed
    0xe2, 0x98, 0xbc, // x0f sun
    0xe2, 0x96, 0xba, // x10 right triangle
    0xe2, 0x97, 0x84, // x11 left triangle
    0xe2, 0x86, 0x95, // x12 up down
    0xe2, 0x80, 0xbc, // x13 double exclamation
    0xC2, 0xB6, 0x00, // x14 paragraph
    0xC2, 0xA7, 0x00, // x15 section
    0xe2, 0x96, 0xac, // x16 rectangle
    0xE2, 0x86, 0xA8, // x17 up down with base
    0xE2, 0x86, 0x91, // x18 up arrow
    0xE2, 0x86, 0x93, // x19 down arrow
    0xE2, 0x86, 0x92, // x1a right arrow
    0xE2, 0x86, 0x90, // x1b left arrow
    0xE2, 0x88, 0x9F, // x1c angle right
    0xE2, 0x86, 0x94, // x1d left-right arrow
    0xE2, 0x96, 0xB2, // x1e up triangle
    0xE2, 0x96, 0xBC, // x1f down triangle
    0xE2, 0x8C, 0x82, // x7f house (127, DEL)

    0xC3, 0x87, 0x00, // x80
    0xC3, 0xBC, 0x00, // x81
    0xC3, 0xA9, 0x00, // x82
    0xC3, 0xA2, 0x00, // x83
    0xC3, 0xA4, 0x00, // x84
    0xC3, 0xA0, 0x00, // x85
    0xC3, 0xA5, 0x00, // x86
    0xC3, 0xA7, 0x00, // x87
    0xC3, 0xAA, 0x00, // x88
    0xC3, 0xAB, 0x00, // x89
    0xC3, 0xA8, 0x00, // x8a
    0xC3, 0xAF, 0x00, // x8b
    0xC3, 0xAE, 0x00, // x8c
    0xC3, 0xAC, 0x00, // x8d
    0xC3, 0x84, 0x00, // x8e
    0xC3, 0x85, 0x00, // x8f

    0xC3, 0x89, 0x00, // x90
    0xC3, 0xA6, 0x00, // x91
    0xC3, 0x86, 0x00, // x92
    0xC3, 0xB4, 0x00, // x93
    0xC3, 0xB6, 0x00, // x94
    0xC3, 0xB2, 0x00, // x95
    0xC3, 0xBB, 0x00, // x96
    0xC3, 0xB9, 0x00, // x97
    0xC3, 0xBF, 0x00, // x98
    0xC3, 0x96, 0x00, // x99
    0xC3, 0x9C, 0x00, // x9a
    0xC2, 0xA2, 0x00, // x9b
    0xC2, 0xA3, 0x00, // x9c
    0xC2, 0xA5, 0x00, // x9d
    0xE2, 0x82, 0xA7, // x9e
    0xC6, 0x92, 0x00, // x9f

    0xC3, 0xA1, 0x00, // xa0
    0xC3, 0xAD, 0x00, // xa1
    0xC3, 0xB3, 0x00, // xa2
    0xC3, 0xBA, 0x00, // xa3
    0xC3, 0xB1, 0x00, // xa4
    0xC3, 0x91, 0x00, // xa5
    0xC2, 0xAA, 0x00, // xa6
    0xC2, 0xBA, 0x00, // xa7
    0xC2, 0xBF, 0x00, // xa8
    0xE2, 0x8C, 0x90, // xa9
    0xC2, 0xAC, 0x00, // xaa
    0xC2, 0xBD, 0x00, // xab
    0xC2, 0xBC, 0x00, // xac
    0xC2, 0xA1, 0x00, // xad
    0xC2, 0xAB, 0x00, // xae
    0xC2, 0xBB, 0x00, // xaf

    0xE2, 0x96, 0x91, // xb0
    0xE2, 0x96, 0x92, // xb1
    0xE2, 0x96, 0x93, // xb2
    0xE2, 0x94, 0x82, // xb3
    0xE2, 0x94, 0xA4, // xb4
    0xE2, 0x95, 0xA1, // xb5
    0xE2, 0x95, 0xA2, // xb6
    0xE2, 0x95, 0x96, // xb7
    0xE2, 0x95, 0x95, // xb8
    0xE2, 0x95, 0xA3, // xb9
    0xE2, 0x95, 0x91, // xba
    0xE2, 0x95, 0x97, // xbb
    0xE2, 0x95, 0x9D, // xbc
    0xE2, 0x95, 0x9C, // xbd
    0xE2, 0x95, 0x9B, // xbe
    0xE2, 0x94, 0x90, // xbf

    0xE2, 0x94, 0x94, // xc0
    0xE2, 0x94, 0xB4, // xc1
    0xE2, 0x94, 0xAC, // xc2
    0xE2, 0x94, 0x9C, // xc3
    0xE2, 0x94, 0x80, // xc4
    0xE2, 0x94, 0xBC, // xc5
    0xE2, 0x95, 0x9E, // xc6
    0xE2, 0x95, 0x9F, // xc7
    0xE2, 0x95, 0x9A, // xc8
    0xE2, 0x95, 0x94, // xc9
    0xE2, 0x95, 0xA9, // xca
    0xE2, 0x95, 0xA6, // xcb
    0xE2, 0x95, 0xA0, // xcc
    0xE2, 0x95, 0x90, // xcd
    0xE2, 0x95, 0xAC, // xce
    0xE2, 0x95, 0xA7, // xcf

    0xE2, 0x95, 0xA8, // xd0
    0xE2, 0x95, 0xA4, // xd1
    0xE2, 0x95, 0xA5, // xd2
    0xE2, 0x95, 0x99, // xd3
    0xE2, 0x95, 0x98, // xd4
    0xE2, 0x95, 0x92, // xd5
    0xE2, 0x95, 0x93, // xd6
    0xE2, 0x95, 0xAB, // xd7
    0xE2, 0x95, 0xAA, // xd8
    0xE2, 0x94, 0x98, // xd9
    0xE2, 0x94, 0x8C, // xda
    0xE2, 0x96, 0x88, // xdb
    0xE2, 0x96, 0x84, // xdc
    0xE2, 0x96, 0x8C, // xdd
    0xE2, 0x96, 0x90, // xde
    0xE2, 0x96, 0x80, // xdf

    0xCE, 0xB1, 0x00, // xe0
    0xC3, 0x9F, 0x00, // xe1
    0xCE, 0x93, 0x00, // xe2
    0xCF, 0x80, 0x00, // xe3
    0xCE, 0xA3, 0x00, // xe4
    0xCF, 0x83, 0x00, // xe5
    0xC2, 0xB5, 0x00, // xe6
    0xCF, 0x84, 0x00, // xe7
    0xCE, 0xA6, 0x00, // xe8
    0xCE, 0x98, 0x00, // xe9
    0xCE, 0xA9, 0x00, // xea
    0xCE, 0xB4, 0x00, // xeb
    0xE2, 0x88, 0x9E, // xec
    0xCF, 0x86, 0x00, // xed
    0xCE, 0xB5, 0x00, // xee
    0xE2, 0x88, 0xA9, // xef

    0xE2, 0x89, 0xA1, // xf0
    0xC2, 0xB1, 0x00, // xf1
    0xE2, 0x89, 0xA5, // xf2
    0xE2, 0x89, 0xA4, // xf3
    0xE2, 0x8C, 0xA0, // xf4
    0xE2, 0x8C, 0xA1, // xf5
    0xC3, 0xB7, 0x00, // xf6
    0xE2, 0x89, 0x88, // xf7
    0xC2, 0xB0, 0x00, // xf8
    0xE2, 0x88, 0x99, // xf9
    0xC2, 0xB7, 0x00, // xfa
    0xE2, 0x88, 0x9A, // xfb
    0xE2, 0x81, 0xBF, // xfc
    0xC2, 0xB2, 0x00, // xfd
    0xE2, 0x96, 0xA0, // xfe
    0xC2, 0xA0, 0x00  // xff
};
#endif

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
            printf("%02x ", (unsigned char)ch); // avoid sign-extension on 64-bit
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



void
print_index( int page, int col, int val )
{
    if (page == PAGE_0 && col < 4) {
        printf("%2d ", val);
    } else {
        printf("%3d ", val);
    }
}


void
print_hex( int val )
{
    printf("x%02X ", val);
}


void
print_ch( int val )
{
    int val2;
#if defined(LINUX)
    int i;
    if ((val > 0x00 && val < 0x20) || val > 0x7e) { // Non-alphanumeric chars
        val2 = (val > 0x7e ? val - ARY_OFFSET : val);
        i = val2*3;
        // Output 2- or 3-byte UTF-8 representation of CP437 character.
        printf("%c", cp437[i]);
        printf("%c", cp437[i+1]);
        if (cp437[i+2] != 0x00) {
            printf("%c", cp437[i+2]);
        }
        printf(" ");
    } else { // Normal alpha-numeric character, and NULL.
        val2 = (val == 0 ? ' ' : val);
        printf("%c ", val2);
    }
#else
    // These characters disturb the formatting in various DOS environments
    // (e.g. FreeDOs, DOSBox-X)
    if (val==0x00 || val==0x07 || val==0x08 || val==0x09 || val==0x0a || val==0x0d || val==0x1a || val==0x1b) {
        val2 = ' ';
    } else {
        val2 = val;
    }
    printf("%c ", val2);
#endif
}


void
print_text(int page, int col, int val) {
    char buf[] = "        ";
    char names[][4] = {
        "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
        "BS",  "TAB", "LF",  "VT",  "FF",  "CR",  "SO",  "SI",
        "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
        "CAN", "EM",  "SUB", "ESC", "FS",  "GS",  "RS",  "US",
        "SPC", "DEL"
    };
    if (page == PAGE_0) {
        if (val <= ' ') {
            memcpy(buf, names[val], strlen(names[val]));
        } else if (val == 127) {
            char * del = names[33];
            memcpy(buf, del, strlen(del));
        }
        // Control size of padding after each column.
        if (col <= 1) {
            buf[6] = '\0';
        } else if (col == 5) {
            buf[3] = '\0';
        } else {
            buf[2] = '\0';
        }
    } else { // PAGE_1
        buf[3] = '\0';
    }
    printf("%s", buf);
}


//  Print 'AAA BBB C DDD' where:
//    AAA  the decimal value
//    BBB  the Hex value
//    C    the character
//    DDD  the text name
void
print_hascii_str(int page, int col, int val)
{
    print_index(page, col, val);
    print_hex(val);
    print_ch(val);
    print_text(page, col, val);
}


//  Print 'H BBBB' where:
//   H     hex value (0-F)
//   BBBB  binary value (0000-1111)
void
print_binary_str(int val)
{
    int i;
    printf("    %X  ", val);
    for (i = 8; i >= 1; i >>= 1) {
        printf("%c", (val & i ? '1' : '0'));
    }
}


void
update_dos_screen(int omit_nl) {
#if !defined(LINUX)
    int n = (omit_nl ? 1 : 0);
    // DOS cannot print a visible representation of certain characters (e.g.
    // line feed). As a work-around, we write characters directly to video
    // RAM. Since this writes to absolute values on the screen, we must
    // make an adjustment if the final newline is not emitted.
    char far * base = (char far *) 0xb8000000; // Base address of DOS video
    *(base + SCREEN_POS( 7+n,  7)) = 0x07;
    *(base + SCREEN_POS( 8+n,  7)) = 0x08;
    *(base + SCREEN_POS( 9+n,  7)) = 0x09;
    *(base + SCREEN_POS(10+n,  7)) = 0x0a;
    *(base + SCREEN_POS(13+n,  7)) = 0x0d;
    *(base + SCREEN_POS( 2+n, 22)) = 0x1a;
    *(base + SCREEN_POS( 3+n, 22)) = 0x1b;
#endif
}


void
print_page(options * opts )
{
    int col;
    int row;
    int val;
    int max_index = (opts->page == PAGE_0 ? 128 : 256);

    for (row = 0; row < MAX_ROWS; row++) {
        for (col=0; col<COLS; col++) {
            val = row + (col * MAX_ROWS) + (max_index - 128);
            if (val < max_index) {
                print_hascii_str(opts->page, col, val);
            } else {
                print_binary_str(val-max_index);
            }
        }
        if (! ((row == MAX_ROWS - 1) && opts->omit_final_nl)) {
            printf("\n");
        }
    }

    if ((opts->page == PAGE_0) && !opts->omit_chars) {
        update_dos_screen(opts->omit_final_nl);
    }
}


void
help( char * progname )
{
    printf("Display file in hex+ASCII format. Or display an ASCII chart.\n");
    printf("Usage: %s [/A] [/B] [/E] [/H] [/N] [/?]\n", progname);
    printf("       %s FILENAME\n", progname);
    printf("\n");
    printf("            If no option is supplied, display Standard ASCII chart (0-127)\n");
    printf("  /A        Same as no option\n");
    printf("  /B        Skip certain chars that may cause printing issues (DOS only)\n");
    printf("  /E        Display Extended ASCII chart (128-255)\n");
    printf("  /H, /?    Display this help\n");
    printf("  /N        Omit final newline when printing ASCII chart (helps in emulators)\n");
    printf("  FILENAME  File to display in hex+ASCII format\n");
    printf("\n");
    printf("A binary table of values 0-0xF is also printed with each ASCII chart.\n");
#if defined(LINUX)
    printf("Characters for DOS Code Page 437 are displayed in the ASCII charts.\n");
#else
    printf("The characters displayed in the ASCII charts will depend on the\n");
    printf("Code Page that is currently loaded. The DOS command 'CHCP' will display\n");
    printf("the current Code Page.\n");
#endif
}


int
main ( int argc, char** argv )
{
    int i;
    char * filename = NULL;

    // Set default options
    options opts;
    opts.help = 0;
    opts.page = PAGE_0;
    opts.omit_final_nl = 0;
    opts.omit_chars = 0;

    // Parse arguments. Skip arg[0].
    for(i=1; i<argc; i++) {
        if      (IS_EQ(argv[i], "/h")) { opts.help = 1; }
        else if (IS_EQ(argv[i], "/?")) { opts.help = 1; }
        else if (IS_EQ(argv[i], "/a")) { opts.page = PAGE_0; }
        else if (IS_EQ(argv[i], "/b")) { opts.omit_chars = 1; }
        else if (IS_EQ(argv[i], "/e")) { opts.page = PAGE_1; }
        else if (IS_EQ(argv[i], "/n")) { opts.omit_final_nl = 1; }
        else {
            if (filename) {
                printf("Error: '%s'. Filename already defined.\n", argv[i]);
                return 1;
            } else {
                filename = argv[i];
            }
        }
    }

    if (opts.help) {
        help(argv[0]);
    } else if (filename) {
        return dumpfile(filename);
    } else {
        print_page(&opts);
    }
    return 0;
}
