/**
 ******************************************************************************
 * File Name          : USBTask.hpp
 * Description        : Task for USB Host initialization
 ******************************************************************************
 */
#ifndef CUBE_SYSTEM_USB_TASK_HPP_
#define CUBE_SYSTEM_USB_TASK_HPP_
/* Includes ------------------------------------------------------------------*/
#include "Task.hpp"
#include "SystemDefines.hpp"

/* Enums ------------------------------------------------------------------*/
enum USB_TASK_COMMANDS
{
    USB_TASK_COMMAND_NONE = 0
};

/* Class ------------------------------------------------------------------*/
class USBTask : public Task
{
public:
    static USBTask &Inst()
    {
        static USBTask inst;
        return inst;
    }

    void InitTask();

protected:
    static void RunTask(void *pvParams)
    {
        USBTask::Inst().Run(pvParams);
    } // Static Task Interface, passes control to the instance Run();

    void Run(void *pvParams); // Main run code

private:
    USBTask();                           // Private constructor
    USBTask(const USBTask &);            // Prevent copy-construction
    USBTask &operator=(const USBTask &); // Prevent assignment
};

#endif // CUBE_SYSTEM_USB_TASK_HPP_
