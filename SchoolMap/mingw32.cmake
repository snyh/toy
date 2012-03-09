# use this file by 
# cmake -DCMAKE_TOOLCHAIN_FILE=./mingw32
SET(ROOT_DIR /home/snyh/opt/mingw-cross-env/usr/i686-pc-mingw32/)

SET(CMAKE_SYSTEM_NAME Windows)

SET(CMAKE_C_COMPILER i686-pc-mingw32-gcc)
SET(CMAKE_CXX_COMPILER i686-pc-mingw32-g++)
SET(CMAKE_RC_COMPILER i686-pc-mingw32-windres)

SET(CMAKE_FIND_ROOT_PATH ${ROOT_DIR})
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CMAKE_INCLUDE_PATH ${ROOT_DIR}/include)
SET(CMAKE_LIBRARY_PATH ${ROOT_DIR}/lib)

SET(CMAKE_PREFIX_PATH ${ROOT_DIR})
SET(CMAKE_PROGRAM_PATH ${ROOT_DIR}/bin)

SET(Boost_THREADAPI "win32")
SET(MSYS TRUE)
SET(MINGW TRUE)

SET(WIN_LIBRARYIES gdi32 comdlg32 oleaut32 imm32 winmm winspool kernel32 user32 shell32 uuid ole32 advapi32 ws2_32 mswsock)

add_definitions(-D_WIN32_WINNT=0x0501)

set(BUILD_SHARED_LIBS OFF)
set(MSYS 1)
set(PKG_CONFIG_EXECUTABLE /home/snyh/opt/mingw-cross-env/usr/bin/i686-pc-mingw32-pkg-config)
set(QT_QMAKE_EXECUTABLE /home/snyh/opt/mingw-cross-env/usr/bin/i686-pc-mingw32-qmake)
set(CMAKE_INSTALL_PREFIX /home/snyh/opt/mingw-cross-env/usr/i686-pc-mingw32 CACHE PATH "Installation Prefix")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Debug|Release|RelWithDebInfo|MinSizeRel")
