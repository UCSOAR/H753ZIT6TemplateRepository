/*
 * File_Handling_Print.cpp
 *
 *  Created on: Nov 22, 2025
 *      Author: SOAR
 *  Description: C-compatible print wrapper for File_Handling.c
 */

#include "File_Handling_Print.h"
#include "SystemDefines.hpp"
#include <cstdarg>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief C-compatible wrapper for cube_print that can be called from C code
     * @param format Printf-style format string
     * @param ... Variable arguments
     */
    void File_Print(const char *format, ...)
    {
        char buffer[DEBUG_PRINT_MAX_SIZE];

        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        // Call the C++ cube_print function
        SOAR_PRINT("%s", buffer);
    }

#ifdef __cplusplus
}
#endif
