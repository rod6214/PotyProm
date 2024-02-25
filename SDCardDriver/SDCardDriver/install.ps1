$CMAKE_BUILD_DIRECTORY = (Get-Location).Path + "\build"
$CMAKE_SOURCE_DIR = (Get-Location).Path
$TOOLCHAIN_DIR = (Get-Location).Path + "\avr-toolchain.cmake"
$CMAKE_BUILD_DIRECTORY
$CMAKE_SOURCE_DIR
$TOOLCHAIN_DIR

powershell -noexit "& ""cmake -G 'Unix Makefiles' -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_DIR -B $CMAKE_BUILD_DIRECTORY -S $CMAKE_SOURCE_DIR""" 
