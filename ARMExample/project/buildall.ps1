$CMAKE_CURRENT_SOURCE_DIR=Get-Location
$TOOLCHAIN_PATH="C:/Develop/bin/arm-toolchain"
# cmake --build ${CMAKE_CURRENT_SOURCE_DIR}/build --target clean
cmake -G 'Unix Makefiles' -DTOOLCHAIN_PREFIX="${TOOLCHAIN_PATH}" -DCMAKE_TOOLCHAIN_FILE="${CMAKE_CURRENT_SOURCE_DIR}/toolchain-arm-none-eabi.cmake" -B "${CMAKE_CURRENT_SOURCE_DIR}/build" -S "${CMAKE_CURRENT_SOURCE_DIR}"