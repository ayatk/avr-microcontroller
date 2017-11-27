cmake_minimum_required(VERSION 2.8)
project(avr_microcontroller)


set(AVR_UPLOADTOOL_PORT /dev/cu.usbmodem1421)
set(AVR_MCU atmega88pa)
set(MCU_FREQ 8000000UL)
set(AVR_PROGRAMMER atmega88pa)

include(generic-avr-gcc.cmake)

set(SOURCE_FILES training/week1/work2.c)
add_avr_executable(work ${SOURCE_FILES})
