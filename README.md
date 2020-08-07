`hexdump.exe` - Display a file in hex+ASCII format; or display Standard ASCII chart or Extended ASCII chart.

`hexdump.zip` is a FreeDOS package containing `hexdump.exe` (and sources).

To install: `fdinst install hexdump.zip`. To install with sources: `fdnpkg install-wsrc hexdump.zip`

The Standard ASCII chart (characters 0-127) and the Extended ASCII chart (characters 128-255) will each fit on an 80x24 screen. A binary table of values 0-0xF is also printed with each ASCII chart.

`hexdump.exe` was created to run on (16-bit) FreeDOS, but can also be built to run on (64-bit) Linux. When built on Linux, it is named `hexd` in order to avoid conflicting with the existing `hexdump` command.

On Linux, the characters displayed on the Extended ASCII chart will depend on the character encoding of the terminal. Setting the encoding to [CodePage 437](https://en.wikipedia.org/wiki/Code_page_437) should produce what would be seen in FreeDOS. CodePage 850 produces similar, but not exact, results.

`hexdump.exe` (and `hexd`) gives exactly the same output as the Linux command `hexdump -C`


On FreeDOS:

    >build.bat clean     Remove generated files
    >build.bat hexdump   Build hexdump.exe
    >build.pkg pkg       Build FreeDOS package hexdump.zip


On Linux:

    ./build.sh clean     Remove generated files
    ./build.sh hexd      Build the hexd executable
    ./build.sh zip       Store files for FreeDOS in h.zip
