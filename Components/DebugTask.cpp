/**
 ******************************************************************************
 * File Name          : DebugTask.cpp
 * Description        : Task for controlling debug input
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <SoarDebug/Inc/DebugTask.hpp>
#include "Command.hpp"
#include "CubeUtils.hpp"
#include <cstring>

#include "stm32h7xx_hal.h"

// External Tasks (to send debug commands to)

/* Macros --------------------------------------------------------------------*/

/* Structs -------------------------------------------------------------------*/

/* Constants -----------------------------------------------------------------*/
constexpr uint8_t DEBUG_TASK_PERIOD = 100;
extern I2C_HandleTypeDef hi2c2;

/* Variables -----------------------------------------------------------------*/

/* Prototypes ----------------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/**
 * @brief Constructor, sets all member variables
 */
DebugTask::DebugTask()
    : Task(TASK_DEBUG_QUEUE_DEPTH_OBJS), kUart_(UART::Debug2) {
  memset(debugBuffer, 0, sizeof(debugBuffer));
  debugMsgIdx = 0;
  isDebugMsgReady = false;
}

/**
 * @brief Init task for RTOS
 */
void DebugTask::InitTask() {
  // Make sure the task is not already initialized
  CUBE_ASSERT(rtTaskHandle == nullptr, "Cannot initialize Debug task twice");

  // Start the task
  BaseType_t rtValue = xTaskCreate(
      (TaskFunction_t)DebugTask::RunTask, (const char*)"DebugTask",
      (uint16_t)TASK_DEBUG_STACK_DEPTH_WORDS, (void*)this,
      (UBaseType_t)TASK_DEBUG_PRIORITY, (TaskHandle_t*)&rtTaskHandle);

  // Ensure creation succeded
  CUBE_ASSERT(rtValue == pdPASS, "DebugTask::InitTask - xTaskCreate() failed");
}

// TODO: Only run thread when appropriate GPIO pin pulled HIGH (or by define)
/**
 *    @brief Runcode for the DebugTask
 */
void DebugTask::Run(void* pvParams) {
  // Arm the interrupt
  ReceiveData();

  while (1) {
    Command cm;

    // Wait forever for a command
    qEvtQueue->ReceiveWait(cm);

    // Process the command
    if (cm.GetCommand() == DATA_COMMAND &&
        cm.GetTaskCommand() == EVENT_DEBUG_RX_COMPLETE) {
      HandleDebugMessage((const char*)debugBuffer);
    }

    cm.Reset();
  }
}

/**
 * @brief Handles debug messages, assumes msg is null terminated
 * @param msg Message to read, must be null termianted
 */
void DebugTask::HandleDebugMessage(const char* msg) {
  //-- SYSTEM / CHAR COMMANDS -- (Must be last)
  if (strcmp(msg, "sysreset") == 0) {
    // Reset the system
    CUBE_ASSERT(false, "System reset requested");
  } else if (strcmp(msg, "sysinfo") == 0) {
    // Print message
    CUBE_PRINT("\n\n-- CUBE SYSTEM --\n");
    CUBE_PRINT("Current System Free Heap: %d Bytes\n", xPortGetFreeHeapSize());
    CUBE_PRINT("Lowest Ever Free Heap: %d Bytes\n",
               xPortGetMinimumEverFreeHeapSize());
    CUBE_PRINT("Debug Task Runtime  \t: %d ms\n\n",
               TICKS_TO_MS(xTaskGetTickCount()));
  } else {
    // Single character command, or unknown command
    switch (msg[0]) {
      default:
        CUBE_PRINT("Debug, unknown command: %s\n", msg);
        break;
    }
  }

  // We've read the data, clear the buffer
  debugMsgIdx = 0;
  isDebugMsgReady = false;
}

/**
 * @brief Receive data, currently receives by arming interrupt
 */
bool DebugTask::ReceiveData() { return kUart_->ReceiveIT(&debugRxChar, this); }

/**
 * @brief Receive data to the buffer
 * @return Whether the debugBuffer is ready or not
 */
void DebugTask::InterruptRxData(uint8_t errors) {
  // If we already have an unprocessed debug message, ignore this byte
  if (!isDebugMsgReady) {
    // Check byte for end of message - note if using termite you must turn on
    // append CR
    if (debugRxChar == '\r' || debugMsgIdx == DEBUG_RX_BUFFER_SZ_BYTES) {
      // Null terminate and process
      debugBuffer[debugMsgIdx++] = '\0';
      isDebugMsgReady = true;

      // Notify the debug task
      Command cm(DATA_COMMAND, EVENT_DEBUG_RX_COMPLETE);
      bool res = qEvtQueue->SendFromISR(cm);

      // If we failed to send the event, we should reset the buffer, that way
      // DebugTask doesn't stall
      if (res == false) {
        debugMsgIdx = 0;
        isDebugMsgReady = false;
      }
    } else {
      debugBuffer[debugMsgIdx++] = debugRxChar;
    }
  }

  // Re-arm the interrupt
  ReceiveData();
}

/* Helper Functions
 * --------------------------------------------------------------*/
/**
 * @brief Extracts an integer parameter from a string
 * @brief msg Message to extract from, MUST be at least identifierLen long, and
 * properly null terminated
 * @brief identifierLen Length of the identifier eg. 'rsc ' (Including the
 * space) is 4
 * @return ERRVAL on failure, otherwise the extracted value
 */
int32_t DebugTask::ExtractIntParameter(const char* msg,
                                       uint16_t identifierLen) {
  // Handle a command with an int parameter at the end
  if (static_cast<uint16_t>(strlen(msg)) < identifierLen + 1) {
    CUBE_PRINT("Int parameter command insufficient length\r\n");
    return ERRVAL;
  }

  // Extract the value and attempt conversion to integer
  const int32_t val = Utils::StringToLong(&msg[identifierLen]);
  if (val == ERRVAL) {
    CUBE_PRINT("Int parameter command invalid value\r\n");
  }

  return val;
}
