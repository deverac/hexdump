`hexdump.exe` - Display a file in hex+ASCII format; or display Standard ASCII chart or Extended ASCII chart.

`hexdump.zip` is a FreeDOS package containing `hexdump.exe` (and sources).

To install: `fdinst install hexdump.zip`. To install with sources: `fdnpkg install-wsrc hexdump.zip`

The Standard ASCII chart (characters 0-127) and the Extended ASCII chart (characters 128-255) will each fit on an 80x24 screen. A binary table of values 0-0xF is also printed with each ASCII chart.

`hexdump.exe` was created to run on (16-bit) FreeDOS, but can also be built to run on (64-bit) Linux. When built on Linux, it is named `hexd` in order to avoid conflicting with the existing `hexdump` command.

On Linux, the characters displayed on the Extended ASCII chart will depend on the character encoding of the terminal. Setting the encoding to [CodePage 437](https://en.wikipedia.org/wiki/Code_page_437) should produce what would be seen in FreeDOS. CodePage 850 produces similar, but not exact, results.

`hexdump.exe` (and `hexd`) gives exactly the same output as the Linux command `hexdump -v -C`

### Building

On Linux:

    ./build.sh clean     Remove generated files
    ./build.sh hexd      Build the hexd executable
    ./build.sh zip       (Optional) Store files for FreeDOS in h.zip

To transfer source files to FreeDOS, you can copy `h.zip` and unzip it, or copy the FreeDOS package `hexdump.zip` and run `fdnpkg install-wsrc hexdump.zip`. Either method will work.

On FreeDOS:

    >build.bat clean     Remove generated files
    >build.bat hexdump   Build hexdump.exe
    >build.bat pkg       Build FreeDOS package hexdump.zip

On FreeDOS, 'hexdump' is built using the Open Watcom C compiler, but `build.bat` can easily be modified to use a different C compiler.

If using an emulator, one method of transferring small files back and forth is via a floppy image and use of the [mtools](https://www.gnu.org/software/mtools/) utilities.

    mformat -C -f 1440 -v PROJECT -i floppy.img ::         Create 1.44Mb floppy image.
    mcopy -i floppy.img h.zip ::                           Copy file to image
    mcopy -i floppy.img ::h.zip h-copy.zip                 Copy file from image
