/**
  ******************************************************************************
  * @file           : SystemDefines.hpp
  * @brief          : Macros and wrappers
  ******************************************************************************
  *
  * Contains system wide macros, defines, and wrappers
  *
  ******************************************************************************
  */
#ifndef CUBE_MAIN_SYSTEM_DEFINES_H
#define CUBE_MAIN_SYSTEM_DEFINES_H

/* Environment Defines ------------------------------------------------------------------*/
//#define COMPUTER_ENVIRONMENT        // Define this if we're in Windows, Linux or Mac (not when flashing on DMB)

#ifdef COMPUTER_ENVIRONMENT
#define __CC_ARM
#endif

/* System Wide Includes ------------------------------------------------------------------*/
#include "main_system.hpp" // C++ Main File Header
#include "UARTDriver.hpp"

/* Cube++ Required Configuration ------------------------------------------------------------------*/
#include "CubeDefines.hpp"
constexpr UARTDriver* const DEFAULT_DEBUG_UART_DRIVER = UART::Debug2;

#define SOAR_ASSERT(expr, ...) ((expr) ? (void)0U : cube_assert_debug(false, (const char *)__FILE__, __LINE__, ##__VA_ARGS__))

// SOAR_PRINT macro, acts as an interface to the print function which sends a packet to the UART Task to print data
#define SOAR_PRINT(str, ...) (print(str, ##__VA_ARGS__))
// UART Handle that ASSERT messages are sent over
enum GLOBAL_COMMANDS : uint8_t
{
    COMMAND_NONE = 0,        // No command, packet can probably be ignored
    TASK_SPECIFIC_COMMAND,    // Runs a task specific command when given this object
    DATA_COMMAND,             // Data command, used to send data to a task. Target is stored in taskCommand
};

/* Cube++ Optional Code Configuration ------------------------------------------------------------------*/


/* Task Parameter Definitions ------------------------------------------------------------------*/
/* - Lower priority number means lower priority task ---------------------------------*/

// UART TASK
constexpr uint8_t UART_TASK_RTOS_PRIORITY = 2;            // Priority of the uart task
constexpr uint8_t UART_TASK_QUEUE_DEPTH_OBJS = 10;        // Size of the uart task queue
constexpr uint16_t UART_TASK_STACK_DEPTH_WORDS = 512;    // Size of the uart task stack

// DEBUG TASK
constexpr uint8_t TASK_DEBUG_PRIORITY = 2;            // Priority of the debug task
constexpr uint8_t TASK_DEBUG_QUEUE_DEPTH_OBJS = 10;        // Size of the debug task queue
constexpr uint16_t TASK_DEBUG_STACK_DEPTH_WORDS = 512;        // Size of the debug task stack


#endif // CUBE_MAIN_SYSTEM_DEFINES_H
