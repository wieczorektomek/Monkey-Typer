# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/twiec/CLionProjects/Moneky_typer/cmake-build-debug/_deps/fmt-src"
  "C:/Users/twiec/CLionProjects/Moneky_typer/cmake-build-debug/_deps/fmt-build"
  "C:/Users/twiec/CLionProjects/Moneky_typer/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix"
  "C:/Users/twiec/CLionProjects/Moneky_typer/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/tmp"
  "C:/Users/twiec/CLionProjects/Moneky_typer/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
  "C:/Users/twiec/CLionProjects/Moneky_typer/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/src"
  "C:/Users/twiec/CLionProjects/Moneky_typer/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/twiec/CLionProjects/Moneky_typer/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/twiec/CLionProjects/Moneky_typer/cmake-build-debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
