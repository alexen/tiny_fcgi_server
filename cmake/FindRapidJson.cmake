###################################################################################################
##
##   Copyright (C) 2021, Enakaev Aleksey <enakaev.aleksey@yandex.ru>
##
##   Absolutely freeware.
##
###################################################################################################
#
# FindRapidJson cmake module
# (from here https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/dev/Module-Maintainers)
#
# Variables:
#
# - RapidJson_FOUND
# - RapidJson_INCLUDE_DIR
#

find_package(PkgConfig)
pkg_check_modules(PC_RapidJson QUIET RapidJson)

find_path(RapidJson_INCLUDE_DIR
     NAMES document.h
     PATH ${PC_RapidJson_INCLUDE_DIRS}
     PATH_SUFFIXES rapidjson
     )

set(RapidJson_LIBRARIES
     ${RapidJson_C_LIBRARY}
     ${RapidJson_CPP_LIBRARY}
     )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RapidJson
     REQUIRED_VARS
          RapidJson_INCLUDE_DIR
     )

mark_as_advanced(${RapidJson_INCLUDE_DIR})