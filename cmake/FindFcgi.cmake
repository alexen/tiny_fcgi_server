###################################################################################################
##
##   Copyright (C) 2021, Enakaev Aleksey <enakaev.aleksey@yandex.ru>
##
##   Absolutely freeware.
##
###################################################################################################
#
# FindFcgi cmake module
# (from here https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/dev/Module-Maintainers)
#
# Variables:
#
# - Fcgi_FOUND
# - Fcgi_INCLUDE_DIR
# - Fcgi_C_LIBRARY
# - Fcgi_CPP_LIBRARY
# - Fcgi_LIBRARIES
#

find_package(PkgConfig)
pkg_check_modules(PC_Fcgi QUIET Fcgi)

find_path(Fcgi_INCLUDE_DIR
     NAMES fcgiapp.h
     PATH ${PC_Fcgi_INCLUDE_DIRS}
     PATH_SUFFIXES fcgi
     )
find_library(Fcgi_C_LIBRARY
     NAMES fcgi
     PATHS ${PC_Fcgi_LIBRARY_DIRS}
     )
find_library(Fcgi_CPP_LIBRARY
     NAMES fcgi++
     PATHS ${PC_Fcgi_LIBRARY_DIRS}
     )

set(Fcgi_LIBRARIES
     ${Fcgi_C_LIBRARY}
     ${Fcgi_CPP_LIBRARY}
     )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Fcgi
     REQUIRED_VARS
          Fcgi_LIBRARIES
          Fcgi_C_LIBRARY
          Fcgi_CPP_LIBRARY
          Fcgi_INCLUDE_DIR
     )

mark_as_advanced(
     ${Fcgi_INCLUDE_DIR}
     ${Fcgi_C_LIBRARY}
     ${Fcgi_CPP_LIBRARY}
     ${Fcgi_LIBRARIES}
     )