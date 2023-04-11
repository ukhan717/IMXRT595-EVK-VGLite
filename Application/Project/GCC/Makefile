###############################################################################
# Makefile for Embedded Wizard GUI Application
###############################################################################
export MAKEFLAGS += --silent

###############################################################################
# GENERAL PROJECT CONFIGURATION
###############################################################################
APP_FILE          = EmbeddedWizard-IMXRT595-EVK-VGLite

###############################################################################
# GENERAL SETTINGS & PATHS
###############################################################################
EMWI_APP_PATH     = ../../GeneratedCode

SRC_PATH          = ../../Source
EMWI_BSP_PATH     = ../../../TargetSpecific

OBJ_PATH          = ./Obj
BIN_PATH          = ./Bin

SDK_PATH          = ../../../ThirdParty/MCUXpressoSDK
DEVICE_PATH       = $(SDK_PATH)/devices/MIMXRT595S
FREE_RTOS_PATH    = $(SDK_PATH)/rtos/freertos/freertos_kernel
VGLITE_PATH       = $(SDK_PATH)/middleware/vglite
STARTUP           = $(DEVICE_PATH)/gcc/startup_MIMXRT595S_cm33.S
LINK_SCRIPT       = ./MIMXRT595Sxxxx_cm33_flash.ld

FREE_RTOS_SOURCE_PATH =                                                        \
                    $(FREE_RTOS_PATH)                                          \
                    $(FREE_RTOS_PATH)/portable/MemMang                         \
                    $(FREE_RTOS_PATH)/portable/GCC/ARM_CM33_NTZ/non_secure

###############################################################################
# Include standard rules and utilities
# Include Embedded Wizard configuration and list of generated source code
###############################################################################
include ./utilities.mk
include ./rules.mk

ifeq (,$(wildcard $(EMWI_APP_PATH)/ewfiles.inc))
  $(error ERROR: $n$nThe file '(EMWI_APP_PATH)/ewfiles.inc' is missing!\
    $nPlease open Embedded Wizard project and generate code before calling make!)
endif

include $(EMWI_APP_PATH)/ewfiles.inc

EMWI_RTE_PATH     = ../../../PlatformPackage/RTE
EMWI_GFX_PATH     = ../../../PlatformPackage/$(EMWI_COLOR_FORMAT)

ifeq (,$(wildcard $(EMWI_GFX_PATH)/ewgfx.inc))
  $(error ERROR: $n$nThe requested color format $(EMWI_COLOR_FORMAT) is not supported for this platform!\
    $nPlease open Embedded Wizard project, select one of the supported color formats and generate code again)
endif

include $(EMWI_GFX_PATH)/ewgfx.inc
include $(EMWI_RTE_PATH)/ewrte.inc

###############################################################################
# Standard directories for C files
###############################################################################
vpath %.c           $(SRC_PATH)                                                \
                    $(EMWI_APP_PATH)                                           \
                    $(EMWI_RTE_PATH)                                           \
                    $(EMWI_GFX_PATH)                                           \
                    $(EMWI_BSP_PATH)                                           \
                    $(EMWI_BSP_PATH)/Drivers                                   \
                    $(DEVICE_PATH)                                             \
                    $(DEVICE_PATH)/drivers                                     \
                    $(DEVICE_PATH)/utilities                                   \
                    $(DEVICE_PATH)/utilities/debug_console                     \
                    $(DEVICE_PATH)/utilities/str                               \
                    $(DEVICE_PATH)/mcuxpresso                                  \
                    $(SDK_PATH)/components/serial_manager                      \
                    $(SDK_PATH)/components/video                               \
                    $(SDK_PATH)/components/video/display/fbdev                 \
                    $(SDK_PATH)/components/video/display/dc/lcdifv             \
                    $(SDK_PATH)/components/video/display/dc/dsi_cmd            \
                    $(SDK_PATH)/components/video/display/rm67162               \
                    $(SDK_PATH)/components/video/display/mipi_dsi_cmd          \
                    $(SDK_PATH)/components/gt911                               \
                    $(SDK_PATH)/components/ft3267                              \
                    $(SDK_PATH)/components/uart                                \
                    $(FREE_RTOS_SOURCE_PATH)                                   \
                    $(VGLITE_PATH)/VGLite                                      \
                    $(VGLITE_PATH)/VGLite/rtos                                 \
                    $(VGLITE_PATH)/VGLiteKernel                                \
                    $(VGLITE_PATH)/VGLiteKernel/rtos

###############################################################################
# SOURCES
###############################################################################
APP_C =                                                                        \
                    main.c                                                     \
                    ewmain.c                                                   \
                    DeviceDriver.c                                             \

# automatically compile all files generated by Embedded Wizard
APP_EMWI_C =        $(EMWIFILES)

# compile all files for the Embedded Wizard Runtime Environment (RTE)
RTE_EMWI_C =        $(EMWI_RTE_FILES)

# compile all files for the Embedded Wizard Graphics Engine (GFX)
GFX_EMWI_C =        $(EMWI_GFX_FILES)

BOARD_CONFIG_C =                                                               \
                    ew_bsp_os.c                                                \
                    ew_bsp_system.c                                            \
                    ew_bsp_clock.c                                             \
                    ew_bsp_event.c                                             \
                    ew_bsp_display.c                                           \
                    ew_bsp_touch.c                                             \
                    ew_bsp_console.c                                           \
                    ew_bsp_inout.c                                             \
                    system_MIMXRT595S_cm33.c                                   \
                    board.c                                                    \
                    flash_config.c                                             \
                    clock_config.c                                             \
                    pin_mux.c                                                  \
                    display_support.c                                          \
                    vglite_support.c

BSP_C =                                                                        \
                    fsl_assert.c                                               \
                    fsl_cache.c                                                \
                    fsl_clock.c                                                \
                    fsl_common.c                                               \
                    fsl_common_arm.c                                           \
                    fsl_dma.c                                                  \
                    fsl_flexcomm.c                                             \
                    fsl_fbdev.c                                                \
                    fsl_flexio.c                                               \
                    fsl_flexio_mculcd.c                                        \
                    fsl_flexio_mculcd_smartdma.c                               \
                    fsl_flexspi.c                                              \
                    fsl_gpio.c                                                 \
                    fsl_i2c.c                                                  \
                    fsl_iap.c                                                  \
                    fsl_inputmux.c                                             \
                    fsl_lcdif.c                                                \
                    fsl_mipi_dsi.c                                             \
                    fsl_mipi_dsi_smartdma.c                                    \
                    fsl_mipi_dsi_cmd.c                                         \
                    fsl_dc_fb_dsi_cmd.c                                        \
                    fsl_rm67162.c                                              \
                    fsl_ft3267.c                                               \
                    fsl_video_common.c                                         \
                    fsl_power.c                                                \
                    fsl_reset.c                                                \
                    fsl_rtc.c                                                  \
                    fsl_smartdma.c                                             \
                    fsl_usart.c                                                \
                    fsl_debug_console.c                                        \
                    fsl_component_serial_manager.c                             \
                    fsl_component_serial_port_uart.c                           \
                    fsl_adapter_usart.c

VGLITE_C =          vg_lite_kernel.c                                           \
                    vg_lite_hal.c                                              \
                    vg_lite_os.c                                               \
                    vg_lite.c                                                  \
                    vg_lite_image.c                                            \
                    vg_lite_matrix.c                                           \
                    vg_lite_path.c                                             \

FREE_RTOS_C =                                                                  \
                    list.c                                                     \
                    queue.c                                                    \
                    tasks.c                                                    \
                    timers.c                                                   \
                    heap_4.c                                                   \
                    port.c                                                     \
                    portasm.c                                                  \

###############################################################################
# LIBRARIES
###############################################################################
LIBS :=             m                                                          \
                    c                                                          \
                    nosys                                                      \
                    $(EMWI_GFX_LIB)                                            \
                    $(EMWI_RTE_LIB)                                            \

###############################################################################
# INCLUDES
###############################################################################
INCLUDES =                                                                     \
                    -I$(SRC_PATH)                                              \
                    -I$(EMWI_BSP_PATH)                                         \
                    -I$(EMWI_BSP_PATH)/Drivers                                 \
                    -I$(EMWI_APP_PATH)                                         \
                    -I$(EMWI_RTE_PATH)                                         \
                    -I$(EMWI_GFX_PATH)                                         \
                    -I$(SDK_PATH)/CMSIS/Core/Include                           \
                    -I$(DEVICE_PATH)                                           \
                    -I$(DEVICE_PATH)/drivers                                   \
                    -I$(DEVICE_PATH)/drivers/cm7                               \
                    -I$(DEVICE_PATH)/utilities                                 \
                    -I$(DEVICE_PATH)/utilities/str                             \
                    -I$(DEVICE_PATH)/utilities/debug_console                   \
                    -I$(SDK_PATH)/components/serial_manager                    \
                    -I$(SDK_PATH)/components/video/display                     \
                    -I$(SDK_PATH)/components/video/display/fbdev               \
                    -I$(SDK_PATH)/components/video/display/rm67162             \
                    -I$(SDK_PATH)/components/video/display/rm68200             \
                    -I$(SDK_PATH)/components/video/display/rm68191             \
                    -I$(SDK_PATH)/components/video/display/mipi_dsi_cmd        \
                    -I$(SDK_PATH)/components/video/display/dc                  \
                    -I$(SDK_PATH)/components/video/display/dc/lcdifv           \
                    -I$(SDK_PATH)/components/video/display/dc/dsi_cmd          \
                    -I$(SDK_PATH)/components/gt911                             \
                    -I$(SDK_PATH)/components/ft3267                            \
                    -I$(SDK_PATH)/components/video                             \
                    -I$(SDK_PATH)/components/uart                              \
                    -I$(VGLITE_PATH)/inc                                       \
                    -I$(VGLITE_PATH)/VGLite/rtos                               \
                    -I$(VGLITE_PATH)/VGLiteKernel                              \
                    -I$(VGLITE_PATH)/VGLiteKernel/rtos                         \
                    -I$(FREE_RTOS_PATH)/portable/GCC/ARM_CM33_NTZ/non_secure   \
                    -I$(FREE_RTOS_PATH)/include

###############################################################################
# DEFINES
###############################################################################
CFLAGS =            -O2 -Wall -mcpu=cortex-m33 -mthumb                         \
                    -mthumb-interwork -mfpu=fpv5-sp-d16 -mfloat-abi=hard       \
                    -ffunction-sections -fdata-sections                        \
                    -ffreestanding                                             \
                    -fno-builtin                                               \
                    -fno-common                                                \
                    -D__MCUXPRESSO                                             \
                    -D__USE_CMSIS                                              \
                    -D__NEWLIB__                                               \
                    -DNDEBUG                                                   \
                    -DCPU_MIMXRT595SFFOC_cm33                                  \
                    -DBOOT_HEADER_ENABLE=1                                     \
                    -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1                     \
                    -DBOARD_ENABLE_PSRAM_CACHE=0                               \
                    -DSSD1963_DATA_WITDH=8                                     \
                    -DFLEXIO_MCULCD_DATA_BUS_WIDTH=8                           \
                    -DCUSTOM_VGLITE_MEMORY_CONFIG=0                            \
                    -DSDK_OS_FREE_RTOS                                         \
                    -DSERIAL_PORT_TYPE_UART=1                                  \
                    -DSDK_DEBUGCONSOLE=1                                       \
                    -DSDK_I2C_BASED_COMPONENT_USED=1                           \
                    -DVG_BLIT_WORKAROUND=1                                     \
                    -DEW_USE_VGLITE_INDEX8=1                                   \
                    -DEW_USE_OPERATING_SYSTEM=1                                \
                    -DEW_FRAME_BUFFER_COLOR_FORMAT=EW_FRAME_BUFFER_COLOR_FORMAT_$(EMWI_COLOR_FORMAT) \
                    -DEW_SURFACE_ROTATION=$(EMWI_SURFACE_ROTATION)             \

###############################################################################
# OBJECTS
###############################################################################
ALL_SRC    = $(APP_C) $(APP_EMWI_C) $(RTE_EMWI_C) $(GFX_EMWI_C) $(BOARD_CONFIG_C) $(BSP_C) $(VGLITE_C) $(FREE_RTOS_C)

OBJS      = $(foreach file,$(ALL_SRC), $(OBJ_PATH)/$(strip $(basename $(file))).o)

MAPFILE   = -Wl,-Map=$(BIN_PATH)/$(APP_FILE).map

LINKING   = $(LD) -mcpu=cortex-m33 -mlittle-endian -mthumb -mthumb-interwork   \
            -mfpu=fpv5-sp-d16 -mfloat-abi=hard -Wl,--gc-sections               \
            $(MAPFILE)                                                         \
            $(STARTUP)                                                         \
            $(OBJS)                                                            \
            $(addprefix -L,$(EMWI_RTE_PATH))                                   \
            $(addprefix -L,$(EMWI_GFX_PATH))                                   \
            $(addprefix -l,$(LIBS))                                            \
            -T $(LINK_SCRIPT)                                                  \
            -o $(BIN_PATH)/$(APP_FILE).elf

TRANSLATE = $(OBJCOPY) -O ihex $(BIN_PATH)/$(APP_FILE).elf $(BIN_PATH)/$(APP_FILE).hex

PRINT_SIZE  = $(SIZE) $(BIN_PATH)/$(APP_FILE).elf

FLASHING  = ..\..\FlashDownload\FlashDownload.cmd $(BIN_PATH)/$(APP_FILE).elf reset

###############################################################################
# RULES
###############################################################################
$(APP_FILE): precompile $(OBJS)
	@echo Linking $(APP_FILE)
	@echo $(LINKING)
	$(LINKING)
	@echo Memory Usage:
	$(PRINT_SIZE)
	$(TRANSLATE)
	@echo $(APP_FILE) successfully built !!

install: $(APP_FILE)
	$(FLASHING)

projectecho:
	@echo -------------------------------------------------
	@echo Creating $(APP_FILE)
	@echo -------------------------------------------------
	@echo Compiler Options: $(CFLAGS)

createdirs:
	@echo -------------------------------------------------
	@echo Creating object and binary directories
	-$(MKDIR) $(OBJ_PATH)
	-$(MKDIR) $(BIN_PATH)
	@echo -------------------------------------------------

precompile: projectecho createdirs ;

.PHONY: clean
clean:
	@echo Cleaning $(OBJ_PATH) and $(BIN_PATH)
	-$(RMDIR) $(OBJ_PATH)
	-$(RMDIR) $(BIN_PATH)

include $(wildcard $(patsubst %,%.d,$(basename $(OBJS))))
