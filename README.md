`hexdump.exe` - Display a file in hex+ASCII format.

`hexdump.zip` is a FreeDOS package containing `hexdump.exe` (and sources).

To install: `fdinst install hexdump.zip`. To install with sources: `fdnpkg install-wsrc hexdump.zip`

`hexdump.exe` was created to run on (16-bit) FreeDOS, but can also be built to run on (64-bit) Linux. When built on Linux, it is named `hexd` in order to avoid conflicting with the existing `hexdump` command.

`hexdump.exe` (and `hexd`) gives exactly the same output as the Linux command `hexdump -C`


On FreeDOS:

    >build.bat clean     Remove generated files
    >build.bat hexdump   Build hexdump.exe
    >build.pkg pkg       Build FreeDOS package hexdump.zip


On Linux:

    ./build.sh clean     Remove generated files
    ./build.sh hexdump   Build the hexd executable
    ./build.sh zip       Store files for FreeDOS in h.zip
