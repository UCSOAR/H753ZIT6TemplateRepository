/*
 * File_Handling_Print.h
 *
 *  Created on: Nov 22, 2025
 *      Author: SOAR
 *  Description: C-compatible print wrapper for File_Handling.c
 */

#ifndef FILE_HANDLING_PRINT_H_
#define FILE_HANDLING_PRINT_H_

#ifdef __cplusplus
extern "C"
{
#endif

    /* C-compatible print function that wraps cube_print */
    void File_Print(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* FILE_HANDLING_PRINT_H_ */
