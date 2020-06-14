#
#             LUFA Library
#     Copyright (C) Dean Camera, 2019.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.

MCU          = atmega328
ARCH         = AVR8
BOARD        = NONE
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = wifiprinter
SRC          = $(TARGET).c
CC_FLAGS     = -flto
LD_FLAGS     = -Os -flto -fuse-linker-plugin -g2
AVRDUDE_PROGRAMMER = usbasp
AVRDUDE_HFUSE = 0xd9
AVRDUDE_EFUSE = 0xfc
AVRDUDE_LFUSE = 0xff
AVRDUDE_LOCK  = 0x3f

# Default target
all:

# Include common DMBS build system modules
DMBS_PATH      ?= ../dmbs/DMBS
include $(DMBS_PATH)/core.mk
include $(DMBS_PATH)/cppcheck.mk
include $(DMBS_PATH)/doxygen.mk
include $(DMBS_PATH)/dfu.mk
include $(DMBS_PATH)/gcc.mk
include $(DMBS_PATH)/hid.mk
include $(DMBS_PATH)/avrdude.mk
include $(DMBS_PATH)/atprogram.mk
