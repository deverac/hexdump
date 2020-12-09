@echo off

if "%1" == "clean"    goto %1
if "%1" == "hexdump"  goto %1
if "%1" == "pkg"      goto %1

echo.
echo   Targets:
echo      clean    Clean generated files
echo      hexdump  Build hexdump.exe
echo      pkg      Build FreeDOS package
echo.
goto end


:clean
    rem Clean
    if exist hexdump.exe del hexdump.exe
    if exist hexdump.obj del hexdump.obj
    if exist hexdump.err del hexdump.err
    if exist hexdump.zip del hexdump.zip
    if exist pkg\NUL deltree /y pkg > NUL
    goto end


:hexdump
    rem Build executable
    wcl hexdump.c
    goto end


:pkg
    rem Build FreeDOS package

    set PKG=pkg
    set GRP=devel
    set NAM=hexdump
    if exist %PKG%\NUL deltree /y %PKG% > NUL
    if exist hexdump.zip del hexdump.zip  > NUL

    mkdir %PKG%
    mkdir %PKG%\appinfo
    set LSM=%PKG%\appinfo\hexdump.lsm
    echo Begin3> %LSM%
    echo Title:          %NAM%>> %LSM%
    echo Version:        0.2>> %LSM%
    echo Entered-date:   2020-12-09>> %LSM%
    echo Description:    Display a file in hex+ASCII format.>> %LSM%
    echo Keywords:       freedos %NAM%>> %LSM%
    echo Author:         >> %LSM%
    echo Maintained-by:  >> %LSM%
    echo Primary-site:   >> %LSM%
    echo Alternate-site: >> %LSM%
    echo Original-site:  >> %LSM%
    echo Platforms:      DOS>> %LSM%
    echo Copying-policy: GPL>> %LSM%
    echo End>> %LSM%

    mkdir %PKG%\%GRP%
    mkdir %PKG%\source
    mkdir %PKG%\source\%NAM%
    if not exist %PKG%\source\%NAM%\NUL goto err1pkg

    copy build.bat   %PKG%\source\%NAM%
    copy hexdump.c   %PKG%\source\%NAM%
    copy hexdump.txt %PKG%\source\%NAM%
    copy LICENSE.txt %PKG%\source\%NAM%
    if not exist %PKG%\source\%NAM%\LICENSE.txt goto err2pkg

    mkdir %PKG%\%GRP%\%NAM%
    copy .\hexdump.exe %PKG%\%GRP%\%NAM%
    if not exist %PKG%\%GRP%\%NAM%\hexdump.exe goto err3pkg
    copy .\hexdump.txt %PKG%\%GRP%\%NAM%
    if not exist %PKG%\%GRP%\%NAM%\hexdump.txt goto err3pkg

    mkdir %PKG%\links
    echo %GRP%\%NAM%\hexdump.exe > %PKG%\links\hexdump.bat
    if not exist %PKG%\links\hexdump.bat goto err4pkg

    cd .\%PKG%
    rem  -9  Max compression
    rem  -r  Recurse into directories
    zip -9 -r ..\hexdump.zip *
    if not exist ..\hexdump.zip goto err5pkg
    cd ..

    echo.
    echo The hexdump.zip package has been created.
    echo.
    echo To install: fdnpkg install hexdump.zip
    echo         or: fdnpkg install-wsrc hexdump.zip
    echo  To remove: fdnpkg remove hexdump

    goto end


:err1pkg
    echo Error creating directory structure. Building package failed.
    goto end

:err2pkg
    echo Error copying source files. Building package failed. 
    goto end

:err3pkg
    echo Error copying executable files. Building package failed.
    goto end

:err4pkg
    echo Error building links. Building package failed. 
    goto end

:err5pkg
    echo Error creating zip file. Building package failed.
    goto end

:end
