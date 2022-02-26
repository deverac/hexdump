#!/bin/sh

set -e

if [ "$1" = "clean" ]; then

    rm -f h.zip
    rm -f hexd

elif [ "$1" = "hexd" ]; then

    gcc hexdump.c -o hexd -DLINUX

elif [ "$1" = "zip" ]; then

    dirnam=hexdump
    mkdir -p $dirnam
    for fil in LICENSE.txt build.bat hexdump.c hexdump.txt; do
        cp $fil $dirnam
    done
    rm -f h.zip
    7z a h.zip $dirnam
    rm -rf $dirnam

else

    printf "  Targets:\n"
    printf "      clean    Remove generated files\n"
    printf "      hexd     Build the hexd executable\n"
    printf "      zip      Store files for FreeDOS in h.zip\n"
    printf "\n"

fi
