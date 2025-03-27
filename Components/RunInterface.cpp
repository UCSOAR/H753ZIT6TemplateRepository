/*
 *  RunInterface.cpp
 *
 *  Created on: Apr 3, 2023
 *      Author: Chris (cjchanx)
 */

#include "main_system.hpp"
#include "UARTDriver.hpp"

extern "C" {
    void run_interface()
    {
        run_main();
    }

    void cpp_USART4_IRQHandler()
    {
        Driver::uart4.HandleIRQ_UART();
    }

    void cpp_USART2_IRQHandler()
		{
				Driver::usart2.HandleIRQ_UART();
		}
}
