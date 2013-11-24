################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/TWR-MCF5225X_sysinit.c" \
"../Sources/adc.c" \
"../Sources/console_io_cf.c" \
"../Sources/dtim.c" \
"../Sources/exceptions.c" \
"../Sources/gpio.c" \
"../Sources/main.c" \
"../Sources/note.c" \
"../Sources/oct_spkr.c" \
"../Sources/pit.c" \
"../Sources/pwm.c" \
"../Sources/song.c" \
"../Sources/uart.c" \
"../Sources/uart_support.c" \
"../Sources/uc_led.c" \
"../Sources/uc_pot.c" \
"../Sources/uc_pushb.c" \

C_SRCS += \
../Sources/TWR-MCF5225X_sysinit.c \
../Sources/adc.c \
../Sources/console_io_cf.c \
../Sources/dtim.c \
../Sources/exceptions.c \
../Sources/gpio.c \
../Sources/main.c \
../Sources/note.c \
../Sources/oct_spkr.c \
../Sources/pit.c \
../Sources/pwm.c \
../Sources/song.c \
../Sources/uart.c \
../Sources/uart_support.c \
../Sources/uc_led.c \
../Sources/uc_pot.c \
../Sources/uc_pushb.c \

S_SRCS += \
../Sources/gpt.s \
../Sources/int.s \

S_SRCS_QUOTED += \
"../Sources/gpt.s" \
"../Sources/int.s" \

OBJS += \
./Sources/TWR-MCF5225X_sysinit_c.obj \
./Sources/adc_c.obj \
./Sources/console_io_cf_c.obj \
./Sources/dtim_c.obj \
./Sources/exceptions_c.obj \
./Sources/gpio_c.obj \
./Sources/gpt_s.obj \
./Sources/int_s.obj \
./Sources/main_c.obj \
./Sources/note_c.obj \
./Sources/oct_spkr_c.obj \
./Sources/pit_c.obj \
./Sources/pwm_c.obj \
./Sources/song_c.obj \
./Sources/uart_c.obj \
./Sources/uart_support_c.obj \
./Sources/uc_led_c.obj \
./Sources/uc_pot_c.obj \
./Sources/uc_pushb_c.obj \

OBJS_QUOTED += \
"./Sources/TWR-MCF5225X_sysinit_c.obj" \
"./Sources/adc_c.obj" \
"./Sources/console_io_cf_c.obj" \
"./Sources/dtim_c.obj" \
"./Sources/exceptions_c.obj" \
"./Sources/gpio_c.obj" \
"./Sources/gpt_s.obj" \
"./Sources/int_s.obj" \
"./Sources/main_c.obj" \
"./Sources/note_c.obj" \
"./Sources/oct_spkr_c.obj" \
"./Sources/pit_c.obj" \
"./Sources/pwm_c.obj" \
"./Sources/song_c.obj" \
"./Sources/uart_c.obj" \
"./Sources/uart_support_c.obj" \
"./Sources/uc_led_c.obj" \
"./Sources/uc_pot_c.obj" \
"./Sources/uc_pushb_c.obj" \

C_DEPS += \
./Sources/TWR-MCF5225X_sysinit_c.d \
./Sources/adc_c.d \
./Sources/console_io_cf_c.d \
./Sources/dtim_c.d \
./Sources/exceptions_c.d \
./Sources/gpio_c.d \
./Sources/main_c.d \
./Sources/note_c.d \
./Sources/oct_spkr_c.d \
./Sources/pit_c.d \
./Sources/pwm_c.d \
./Sources/song_c.d \
./Sources/uart_c.d \
./Sources/uart_support_c.d \
./Sources/uc_led_c.d \
./Sources/uc_pot_c.d \
./Sources/uc_pushb_c.d \

OBJS_OS_FORMAT += \
./Sources/TWR-MCF5225X_sysinit_c.obj \
./Sources/adc_c.obj \
./Sources/console_io_cf_c.obj \
./Sources/dtim_c.obj \
./Sources/exceptions_c.obj \
./Sources/gpio_c.obj \
./Sources/gpt_s.obj \
./Sources/int_s.obj \
./Sources/main_c.obj \
./Sources/note_c.obj \
./Sources/oct_spkr_c.obj \
./Sources/pit_c.obj \
./Sources/pwm_c.obj \
./Sources/song_c.obj \
./Sources/uart_c.obj \
./Sources/uart_support_c.obj \
./Sources/uc_led_c.obj \
./Sources/uc_pot_c.obj \
./Sources/uc_pushb_c.obj \

C_DEPS_QUOTED += \
"./Sources/TWR-MCF5225X_sysinit_c.d" \
"./Sources/adc_c.d" \
"./Sources/console_io_cf_c.d" \
"./Sources/dtim_c.d" \
"./Sources/exceptions_c.d" \
"./Sources/gpio_c.d" \
"./Sources/main_c.d" \
"./Sources/note_c.d" \
"./Sources/oct_spkr_c.d" \
"./Sources/pit_c.d" \
"./Sources/pwm_c.d" \
"./Sources/song_c.d" \
"./Sources/uart_c.d" \
"./Sources/uart_support_c.d" \
"./Sources/uc_led_c.d" \
"./Sources/uc_pot_c.d" \
"./Sources/uc_pushb_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/TWR-MCF5225X_sysinit_c.obj: ../Sources/TWR-MCF5225X_sysinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/TWR-MCF5225X_sysinit.args" -o "Sources/TWR-MCF5225X_sysinit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/adc_c.obj: ../Sources/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/adc.args" -o "Sources/adc_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/console_io_cf_c.obj: ../Sources/console_io_cf.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/console_io_cf.args" -o "Sources/console_io_cf_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/dtim_c.obj: ../Sources/dtim.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/dtim.args" -o "Sources/dtim_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/exceptions_c.obj: ../Sources/exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/exceptions.args" -o "Sources/exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/gpio_c.obj: ../Sources/gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/gpio.args" -o "Sources/gpio_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/gpt_s.obj: ../Sources/gpt.s
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ColdFire Assembler'
	"$(CF_ToolsDirEnv)/mwasmmcf" @@"Sources/gpt.args" -o "Sources/gpt_s.obj" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/int_s.obj: ../Sources/int.s
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ColdFire Assembler'
	"$(CF_ToolsDirEnv)/mwasmmcf" @@"Sources/int.args" -o "Sources/int_s.obj" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/note_c.obj: ../Sources/note.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/note.args" -o "Sources/note_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/oct_spkr_c.obj: ../Sources/oct_spkr.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/oct_spkr.args" -o "Sources/oct_spkr_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/pit_c.obj: ../Sources/pit.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/pit.args" -o "Sources/pit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/pwm_c.obj: ../Sources/pwm.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/pwm.args" -o "Sources/pwm_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/song_c.obj: ../Sources/song.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/song.args" -o "Sources/song_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart_c.obj: ../Sources/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/uart.args" -o "Sources/uart_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart_support_c.obj: ../Sources/uart_support.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/uart_support.args" -o "Sources/uart_support_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uc_led_c.obj: ../Sources/uc_led.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/uc_led.args" -o "Sources/uc_led_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uc_pot_c.obj: ../Sources/uc_pot.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/uc_pot.args" -o "Sources/uc_pot_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uc_pushb_c.obj: ../Sources/uc_pushb.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/uc_pushb.args" -o "Sources/uc_pushb_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


