# Those settings should be set from outside
# cmake-format: off
set(PARAM_DEBUG "" CACHE STRING "Debug options: ${VALID_DEBUG_OPTIONS}.")
option(PARAM_TESTS "If set then tests are compiled (only in non arm mode)." OFF)
option(PARAM_SIMULATION "If set then simulation is allowed." OFF)
set(PARAM_SYSTEM "" CACHE STRING "System type to use. Systems are defined in /systems directory.")
# cmake-format: off

# DEBUG OPTION
if(NOT ${PARAM_DEBUG} IN_LIST VALID_DEBUG_OPTIONS)
    message(FATAL_ERROR "${Red}For valid PARAM_DEBUG options are ${VALID_DEBUG_OPTIONS}.${ColorReset}")
endif()

# TESTS OPTION
if(NOT TESTS_ALLOWED)
    if(PARAM_TESTS)
        message("${BoldRed}Resetting PARAM_TESTS since they are not allowed${ColorReset}")
    endif()
    set(PARAM_TESTS OFF)
endif()

if(PARAM_TESTS)
    set(_COLOR_MSG_TESTS ${Green})
else()
    set(_COLOR_MSG_TESTS ${Red})
endif()

# PRINT INFO
message("${BoldBlue}Debug       : ${_COLOR_MSG_DEBUG}${PARAM_DEBUG}${ColorReset}")
message("${BoldBlue}Tests       : ${_COLOR_MSG_TESTS}${PARAM_TESTS}${ColorReset}")