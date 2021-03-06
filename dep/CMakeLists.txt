# This file is part of the OregonCore Project. See AUTHORS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

if( MSVC )
  add_definitions(/W0)
else()
  add_definitions(-w)
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  if(SERVERS OR TOOLS)
    add_subdirectory(jemalloc)
  endif()
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  if(SERVERS OR TOOLS)
    add_subdirectory(acelite)
  endif()
  if(SERVERS)
    add_subdirectory(pdcurses)
  endif()
  if(TOOLS)
    add_subdirectory(bzip2)
  endif()
endif()

add_subdirectory(zlib)
add_subdirectory(recastnavigation)
add_subdirectory(g3dlite)

if(SERVERS)
  add_subdirectory(gsoap)
endif()

if(TOOLS)
  add_subdirectory(libmpq)
endif()

add_subdirectory(lualib)