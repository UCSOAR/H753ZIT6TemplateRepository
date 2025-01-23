################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32h753zitx.s 

S_DEPS += \
./Core/Startup/startup_stm32h753zitx.d 

OBJS += \
./Core/Startup/startup_stm32h753zitx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/Core" -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/Core/Inc" -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/SoarOS/Core" -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/SoarOS/Drivers/Inc" -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/SoarOS/Libraries/embedded-template-library/include" -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/Components" -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/SoarOS" -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/SoarOS/Core/Inc" -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/Core/Src" -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/Components/SoarDebug" -I"C:/Users/danik/SOAR/H753ZIT6TemplateRepository/Components/SoarDebug/Inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32h753zitx.d ./Core/Startup/startup_stm32h753zitx.o

.PHONY: clean-Core-2f-Startup

