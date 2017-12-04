# Project name
PROJECT =  work

# Week number
W = 0

# Exercise number
E = 0

# Source files
ifeq ($(W), 0)
	SRCS = $(shell ls src/**/*.c)
else
	SRCS = training/week$(W)/work$(E).c
endif

# Device name
DEV = /dev/ttyACM0

# if macOS used
UNAME = $(shell uname)
ifeq ($(UNAME),Darwin)
	DEV = $(shell ls /dev/* | grep cu.usbmodem)
endif

# output source directory
OUT_DIR = build

WORK_DIR = ${OUT_DIR}/${PROJECT}

# OBJECTS = $(SRCS:.c=.o)
OBJECTS = $(patsubst %.c,$(OUT_DIR)/%.o,$(SRCS))
MPU = atmega88pa
F_CPU = 8000000UL

MAPFILE = ${WORK_DIR}.map
LSSFILE = ${WORK_DIR}.lss
ELFFILE = ${WORK_DIR}.elf
HEXFILE = ${WORK_DIR}.hex
EEPFILE = ${WORK_DIR}.eep

CC = avr-gcc
CFLAGS = -mmcu=${MPU} -W -Wall -Werror-implicit-function-declaration -DF_CPU=${F_CPU} -Os -g2
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -fdiagnostics-color
LDFLAGS = -mmcu=${MPU} -Wl,-Map=${MAPFILE}

all: clean ${HEXFILE}

${HEXFILE}:	${OBJECTS}
	avr-gcc ${LDFLAGS} ${OBJECTS} -o ${ELFFILE}
	avr-objcopy -j.text -j.data -O ihex ${ELFFILE} ${HEXFILE}
	avr-objcopy -j.eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex ${ELFFILE} ${EEPFILE}
	avr-objdump -h -S ${ELFFILE} > ${LSSFILE}
	@echo
	@avr-size -C --mcu=${MPU} ${ELFFILE}

dl:	all
	/bin/cp ${HEXFILE} ${DEV}

clean:
	/bin/rm -fr ${OUT_DIR} ./a.out **/*.[iso] *~

${OUT_DIR}/%.o: %.c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	${CC}  -c  $< -o $@ ${CFLAGS}
