/**
 ******************************************************************************
 * File Name          : USBTask.cpp
 * Description        : Task for USB Host initialization
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "USBTask.hpp"
#include "SystemDefines.hpp"
#include "usb_host.h"

/* Macros --------------------------------------------------------------------*/

/* Structs -------------------------------------------------------------------*/

/* Constants -----------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/* Prototypes ----------------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/**
 * @brief Constructor, sets all member variables
 */
USBTask::USBTask() : Task(TASK_USB_QUEUE_DEPTH_OBJS) {}

/**
 * @brief Init task for RTOS
 */
void USBTask::InitTask()
{
    // Make sure the task is not already initialized
    SOAR_ASSERT(rtTaskHandle == nullptr, "Cannot initialize USB task twice");

    // Start the task
    BaseType_t rtValue = xTaskCreate(
        (TaskFunction_t)USBTask::RunTask, (const char *)"USBTask",
        (uint16_t)TASK_USB_STACK_DEPTH_WORDS, (void *)this,
        (UBaseType_t)TASK_USB_PRIORITY, (TaskHandle_t *)&rtTaskHandle);

    // Ensure creation succeeded
    SOAR_ASSERT(rtValue == pdPASS, "USBTask::InitTask - xTaskCreate() failed");
}

/**
 * @brief Runcode for the USBTask
 */
void USBTask::Run(void *pvParams)
{
    // Initialize USB Host


    while (1)
    {

    	//MX_USB_HOST_Process();

        Command cm;


        // Wait forever for a command
        qEvtQueue->ReceiveWait(cm);

        // Process the command
        // Add command handling here if needed

        cm.Reset();
    }
}
