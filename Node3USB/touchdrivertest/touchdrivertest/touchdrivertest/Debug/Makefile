################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../oled.c \
../touch.c \
../touchdrivertest.c


PREPROCESSING_SRCS +=  \
../qm_asm_tiny_mega.S


ASM_SRCS += 


OBJS +=  \
oled.o \
qm_asm_tiny_mega.o \
touch.o \
touchdrivertest.o

OBJS_AS_ARGS +=  \
oled.o \
qm_asm_tiny_mega.o \
touch.o \
touchdrivertest.o

C_DEPS +=  \
oled.d \
qm_asm_tiny_mega.d \
touch.d \
touchdrivertest.d

C_DEPS_AS_ARGS +=  \
oled.d \
qm_asm_tiny_mega.d \
touch.d \
touchdrivertest.d

OUTPUT_FILE_PATH +=touchdrivertest.elf

OUTPUT_FILE_PATH_AS_ARGS +=touchdrivertest.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler







./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG -D_QMATRIX_ -D_ROTOR_SLIDER_ -DQT_DELAY_CYCLES=1 -DQT_NUM_CHANNELS=16 -DQT_MAX_NUM_ROTORS_SLIDERS=2 -DNUM_X_LINES=8 -DNUM_Y_LINES=2 -DNUM_X_PORTS=2 -DPORT_NUM_1=1 -DPORT_NUM_2=2 -DPORT_X_1=E -DPORT_X_2=C -DPORT_YA=C -DPORT_YB=F -DPORT_SMP=F -DSMP_PIN=5 -DF_CPU=16000000  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=at90usb1287 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler
./qm_asm_tiny_mega.o: .././qm_asm_tiny_mega.S
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=at90usb1287 -D_QMATRIX_ -D_ROTOR_SLIDER_ -DQT_DELAY_CYCLES=1 -DQT_NUM_CHANNELS=16 -DQT_MAX_NUM_ROTORS_SLIDERS=2 -DNUM_X_LINES=8  -DNUM_Y_LINES=2 -DNUM_X_PORTS=2 -DPORT_NUM_1=1 -DPORT_NUM_2=2 -DPORT_X_1=E -DPORT_X_2=C -DPORT_YA=C -DPORT_YB=F -DPORT_SMP=F -DSMP_PIN=5 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -mrelax -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	


./%.o: .././%.S
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=at90usb1287 -D_QMATRIX_ -D_ROTOR_SLIDER_ -DQT_DELAY_CYCLES=1 -DQT_NUM_CHANNELS=16 -DQT_MAX_NUM_ROTORS_SLIDERS=2 -DNUM_X_LINES=8  -DNUM_Y_LINES=2 -DNUM_X_PORTS=2 -DPORT_NUM_1=1 -DPORT_NUM_2=2 -DPORT_X_1=E -DPORT_X_2=C -DPORT_YA=C -DPORT_YB=F -DPORT_SMP=F -DSMP_PIN=5 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -mrelax -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="touchdrivertest.map" -Wl,--start-group -Wl,-lm -Wl,-lavr51g2_16qm_8x_2y_krs_2rs  -Wl,--end-group -Wl,-L".."  -Wl,--gc-sections -mrelax -mmcu=at90usb1287  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "touchdrivertest.elf" "touchdrivertest.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "touchdrivertest.elf" "touchdrivertest.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "touchdrivertest.elf" > "touchdrivertest.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "touchdrivertest.elf" "touchdrivertest.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-size.exe" "touchdrivertest.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "touchdrivertest.elf" "touchdrivertest.a" "touchdrivertest.hex" "touchdrivertest.lss" "touchdrivertest.eep" "touchdrivertest.map" "touchdrivertest.srec" "touchdrivertest.usersignatures"
	