########################################################################################################################
# Generic utilities and functionality for CMake.
########################################################################################################################

# @brief Converts a boolean to integer.
# @param[in] bool_var The name of the variable with the boolean value.
# @param[out] int_var The name of the variable where the resulting integer will be stored.
# @example bool2int(BOOL_VARIABLE INT_VARIABLE)
function(bool2int bool_var int_var)
    if(${bool_var})
        set(${int_var} 1 PARENT_SCOPE)
    else()
        set(${int_var} 0 PARENT_SCOPE)
    endif()
endfunction()
