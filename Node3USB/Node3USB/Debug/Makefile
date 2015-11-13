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
SUBDIRS :=  \
../Communication_drivers \
../TouchDrivers


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Communication_drivers/USB.c \
../Node3.c \
../TouchDrivers/oled.c \
../TouchDrivers/touch.c \
../TouchDrivers/touchdrivertest.c \
../TouchDrivers/touchPWM.c


PREPROCESSING_SRCS +=  \
../TouchDrivers/qm_asm_tiny_mega.S


ASM_SRCS += 


OBJS +=  \
Communication_drivers/USB.o \
Node3.o \
TouchDrivers/oled.o \
TouchDrivers/qm_asm_tiny_mega.o \
TouchDrivers/touch.o \
TouchDrivers/touchdrivertest.o \
TouchDrivers/touchPWM.o

OBJS_AS_ARGS +=  \
Communication_drivers/USB.o \
Node3.o \
TouchDrivers/oled.o \
TouchDrivers/qm_asm_tiny_mega.o \
TouchDrivers/touch.o \
TouchDrivers/touchdrivertest.o \
TouchDrivers/touchPWM.o

C_DEPS +=  \
Communication_drivers/USB.d \
Node3.d \
TouchDrivers/oled.d \
TouchDrivers/qm_asm_tiny_mega.d \
TouchDrivers/touch.d \
TouchDrivers/touchdrivertest.d \
TouchDrivers/touchPWM.d

C_DEPS_AS_ARGS +=  \
Communication_drivers/USB.d \
Node3.d \
TouchDrivers/oled.d \
TouchDrivers/qm_asm_tiny_mega.d \
TouchDrivers/touch.d \
TouchDrivers/touchdrivertest.d \
TouchDrivers/touchPWM.d

OUTPUT_FILE_PATH +=Node3USB.elf

OUTPUT_FILE_PATH_AS_ARGS +=Node3USB.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+=  \
C:/Users/TEMP/byggern/Node3USB/Node3USB/TouchDrivers/libavr51g2_16qm_8x_2y_krs_2rs.a

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler













Communication_drivers/%.o: ../Communication_drivers/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -DDEBUG -D_QMATRIX_ -D_ROTOR_SLIDER_ -DQT_DELAY_CYCLES=1 -DQT_NUM_CHANNELS=16 -DQT_MAX_NUM_ROTORS_SLIDERS=2 -DNUM_X_LINES=8 -DNUM_Y_LINES=2 -DNUM_X_PORTS=2 -DPORT_NUM_1=1 -DPORT_NUM_2=2 -DPORT_X_1=E -DPORT_X_2=C -DPORT_YA=C -DPORT_YB=F -DPORT_SMP=F -DSMP_PIN=5 -DF_CPU=16000000 -DNDEBUG -DBOARD=USER_BOARD  -I"../common/applications/user_application/user_board/config" -I"../src/config" -I"../src/ASF/common/boards" -I"../src/ASF/mega/utils" -I"../src/ASF/common/utils" -I"../src/ASF/mega/utils/preprocessor" -I"../src" -I"../src/ASF/common/boards/user_board"  -O1 -fdata-sections -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=at90usb1287 -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -DDEBUG -D_QMATRIX_ -D_ROTOR_SLIDER_ -DQT_DELAY_CYCLES=1 -DQT_NUM_CHANNELS=16 -DQT_MAX_NUM_ROTORS_SLIDERS=2 -DNUM_X_LINES=8 -DNUM_Y_LINES=2 -DNUM_X_PORTS=2 -DPORT_NUM_1=1 -DPORT_NUM_2=2 -DPORT_X_1=E -DPORT_X_2=C -DPORT_YA=C -DPORT_YB=F -DPORT_SMP=F -DSMP_PIN=5 -DF_CPU=16000000 -DNDEBUG -DBOARD=USER_BOARD  -I"../common/applications/user_application/user_board/config" -I"../src/config" -I"../src/ASF/common/boards" -I"../src/ASF/mega/utils" -I"../src/ASF/common/utils" -I"../src/ASF/mega/utils/preprocessor" -I"../src" -I"../src/ASF/common/boards/user_board"  -O1 -fdata-sections -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=at90usb1287 -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

TouchDrivers/%.o: ../TouchDrivers/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -DDEBUG -D_QMATRIX_ -D_ROTOR_SLIDER_ -DQT_DELAY_CYCLES=1 -DQT_NUM_CHANNELS=16 -DQT_MAX_NUM_ROTORS_SLIDERS=2 -DNUM_X_LINES=8 -DNUM_Y_LINES=2 -DNUM_X_PORTS=2 -DPORT_NUM_1=1 -DPORT_NUM_2=2 -DPORT_X_1=E -DPORT_X_2=C -DPORT_YA=C -DPORT_YB=F -DPORT_SMP=F -DSMP_PIN=5 -DF_CPU=16000000 -DNDEBUG -DBOARD=USER_BOARD  -I"../common/applications/user_application/user_board/config" -I"../src/config" -I"../src/ASF/common/boards" -I"../src/ASF/mega/utils" -I"../src/ASF/common/utils" -I"../src/ASF/mega/utils/preprocessor" -I"../src" -I"../src/ASF/common/boards/user_board"  -O1 -fdata-sections -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g3 -Wall -mmcu=at90usb1287 -c -std=gnu99 -fno-strict-aliasing -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration -Wpointer-arith -mrelax -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler
TouchDrivers/qm_asm_tiny_mega.o: ../TouchDrivers/qm_asm_tiny_mega.S
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=at90usb1287 -mrelax -DBOARD=USER_BOARD -D_QMATRIX_ -D_ROTOR_SLIDER_ -DQT_DELAY_CYCLES=1 -DQT_NUM_CHANNELS=16 -DQT_MAX_NUM_ROTORS_SLIDERS=2 -DNUM_X_LINES=8  -DNUM_Y_LINES=2 -DNUM_X_PORTS=2 -DPORT_NUM_1=1 -DPORT_NUM_2=2 -DPORT_X_1=E -DPORT_X_2=C -DPORT_YA=C -DPORT_YB=F -DPORT_SMP=F -DSMP_PIN=5 -I "../common/applications/user_application/user_board/config" -I "../src/config" -I "../src/ASF/common/boards" -I "../src/ASF/mega/utils" -I "../src/ASF/common/utils" -I "../src/ASF/mega/utils/preprocessor" -I "../src" -I "../src/ASF/common/boards/user_board"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -mrelax -Wa,-g   -o "$@" "$<" 
	@echo Finished building: $<
	


TouchDrivers/%.o: ../TouchDrivers/%.S
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=at90usb1287 -mrelax -DBOARD=USER_BOARD -D_QMATRIX_ -D_ROTOR_SLIDER_ -DQT_DELAY_CYCLES=1 -DQT_NUM_CHANNELS=16 -DQT_MAX_NUM_ROTORS_SLIDERS=2 -DNUM_X_LINES=8  -DNUM_Y_LINES=2 -DNUM_X_PORTS=2 -DPORT_NUM_1=1 -DPORT_NUM_2=2 -DPORT_X_1=E -DPORT_X_2=C -DPORT_YA=C -DPORT_YB=F -DPORT_SMP=F -DSMP_PIN=5 -I "../common/applications/user_application/user_board/config" -I "../src/config" -I "../src/ASF/common/boards" -I "../src/ASF/mega/utils" -I "../src/ASF/common/utils" -I "../src/ASF/mega/utils/preprocessor" -I "../src" -I "../src/ASF/common/boards/user_board"  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -mrelax -Wa,-g   -o "$@" "$<" 
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
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Node3USB.map" -Wl,--start-group -Wl,-lm -Wl,-lavr51g2_16qm_8x_2y_krs_2rs  -Wl,--end-group -Wl,-L"C:\Users\TEMP\byggern\Node3USB\Node3USB\TouchDrivers" -Wl,-L"../TouchDrivers"  -Wl,--gc-sections -mrelax -mmcu=at90usb1287 -Wl,--relax  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Node3USB.elf" "Node3USB.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Node3USB.elf" "Node3USB.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Node3USB.elf" > "Node3USB.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Node3USB.elf" "Node3USB.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1061\avr8-gnu-toolchain\bin\avr-size.exe" "Node3USB.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Node3USB.elf" "Node3USB.a" "Node3USB.hex" "Node3USB.lss" "Node3USB.eep" "Node3USB.map" "Node3USB.srec" "Node3USB.usersignatures"
	