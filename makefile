# Makefile taken from Wikipedia.org

# Default build type
TYPE = debug
#TYPE = release
#TYPE = release-tools
#TYPE = preprocessor

# output dir
BUILD_DIR = build

# compiler
COMPILER = 4.7
COMPILER_OUTPUT = c
COMPILER_NAME = v810

# Small data sections' usage
MSDA_SIZE                       = 0
MEMORY_POOL_SECTION             =
NON_INITIALIZED_DATA_SECTION    =
INITIALIZED_DATA_SECTION        =
STATIC_SINGLETONS_DATA_SECTION  =
VIRTUAL_TABLES_DATA_SECTION     =

MEMORY_POOL_SECTION_ATTRIBUTE               = __MEMORY_POOL_SECTION_ATTRIBUTE=
NON_INITIALIZED_DATA_SECTION_ATTRIBUTE      = __NON_INITIALIZED_DATA_SECTION_ATTRIBUTE=
INITIALIZED_DATA_SECTION_ATTRIBUTE          = __INITIALIZED_DATA_SECTION_ATTRIBUTE=
STATIC_SINGLETONS_DATA_SECTION_ATTRIBUTE    = __STATIC_SINGLETONS_DATA_SECTION_ATTRIBUTE=
VIRTUAL_TABLES_DATA_SECTION_ATTRIBUTE       = __VIRTUAL_TABLES_DATA_SECTION_ATTRIBUTE=


MEMORY_POOL_IN_SRAM =

# include overrides
CONFIG_MAKE_FILE = $(shell pwd)/config.make
include $(CONFIG_MAKE_FILE)

ifeq ($(COMPILER), 4.7)
COMPILER_NAME = v810
endif

GCC = $(COMPILER_NAME)-gcc
AS = $(COMPILER_NAME)-as
LD = $(COMPILER_NAME)-ld
OBJCOPY = $(COMPILER_NAME)-objcopy
OBJDUMP = $(COMPILER_NAME)-objdump

DUMP_TARGET =
ifeq ($(DUMP_ELF), 1)
DUMP_TARGET = dump
endif

PAD =
ifeq ($(PAD_ROM), 1)
PAD = pad
endif


STORE_SUFIX =
PROLOG_FUNCTIONS_FLAG =
ifeq ($(USE_PROLOG_FUNCTIONS), 1)
PROLOG_FUNCTIONS_FLAG = -mprolog-function
STORE_SUFIX = -pf
endif

FRAME_POINTER_USAGE_FLAG = -fomit-frame-pointer
ifeq ($(USE_FRAME_POINTER), 1)
FRAME_POINTER_USAGE_FLAG = -fno-omit-frame-pointer
endif


ifneq ($(MEMORY_POOL_SECTION),)
MEMORY_POOL_SECTION_ATTRIBUTE = __MEMORY_POOL_SECTION_ATTRIBUTE="__attribute__((section(\"$(MEMORY_POOL_SECTION)\")))"
endif

ifneq ($(NON_INITIALIZED_DATA_SECTION),)
NON_INITIALIZED_DATA_SECTION_ATTRIBUTE = __NON_INITIALIZED_DATA_SECTION_ATTRIBUTE="__attribute__((section(\"$(NON_INITIALIZED_DATA_SECTION)\")))"
endif

ifneq ($(INITIALIZED_DATA_SECTION),)
INITIALIZED_DATA_SECTION_ATTRIBUTE = __INITIALIZED_DATA_SECTION_ATTRIBUTE="__attribute__((section(\"$(INITIALIZED_DATA_SECTION)\")))"
endif

ifneq ($(STATIC_SINGLETONS_DATA_SECTION),)
STATIC_SINGLETONS_DATA_SECTION_ATTRIBUTE = __STATIC_SINGLETONS_DATA_SECTION_ATTRIBUTE="__attribute__((section(\"$(STATIC_SINGLETONS_DATA_SECTION)\")))"
endif

ifneq ($(VIRTUAL_TABLES_DATA_SECTION),)
VIRTUAL_TABLES_DATA_SECTION_ATTRIBUTE = __VIRTUAL_TABLES_DATA_SECTION_ATTRIBUTE="__attribute__((section(\"$(VIRTUAL_TABLES_DATA_SECTION)\")))"
endif

DATA_SECTION_ATTRIBUTES = $(MEMORY_POOL_SECTION_ATTRIBUTE) $(NON_INITIALIZED_DATA_SECTION_ATTRIBUTE) $(INITIALIZED_DATA_SECTION_ATTRIBUTE) $(STATIC_SINGLETONS_DATA_SECTION_ATTRIBUTE) $(VIRTUAL_TABLES_DATA_SECTION_ATTRIBUTE)

# engine's home
VBJAENGINE = $(VBDE)libs/vbjaengine

# linker script
LINKER_SCRIPT = $(VBJAENGINE)/lib/compiler/vb.ld

# Which directories contain source files
# DIRS := $(shell find * -type d -print)
DIRS := $(shell find ./source ./assets -type d -print)

# Which libraries are linked
LIBS =  vbjae
ROMHEADER=lib/vb.hdr

# Obligatory headers
CONFIG_FILE =       $(shell pwd)/config.h
ESSENTIAL_HEADERS = -include $(CONFIG_FILE) \
					-include $(VBJAENGINE)/libvbjae.h

# Common macros for all build types
COMMON_MACROS = $(DATA_SECTION_ATTRIBUTES)

# The next blocks changes some variables depending on the build type
ifeq ($(TYPE),debug)
LDPARAM = -fno-builtin -ffreestanding -T$(LINKER_SCRIPT) -lm
CCPARAM = $(PROLOG_FUNCTIONS_FLAG) $(FRAME_POINTER_USAGE_FLAG) -fno-builtin -ffreestanding -nodefaultlibs -mv810 -O0 -Wall -std=gnu99 -fstrict-aliasing $(ESSENTIAL_HEADERS)
MACROS = __DEBUG __TOOLS $(COMMON_MACROS)
endif

ifeq ($(TYPE), release)
LDPARAM = -T$(LINKER_SCRIPT) -lm
CCPARAM = $(PROLOG_FUNCTIONS_FLAG) $(FRAME_POINTER_USAGE_FLAG) -nodefaultlibs -mv810 -finline-functions -Wall -O3 -Winline -std=gnu99 -fstrict-aliasing $(ESSENTIAL_HEADERS)
MACROS = $(COMMON_MACROS)
endif

ifeq ($(TYPE), release-tools)
LDPARAM = -T$(LINKER_SCRIPT) -lm
CCPARAM = $(PROLOG_FUNCTIONS_FLAG) $(FRAME_POINTER_USAGE_FLAG) -nodefaultlibs -mv810 -finline-functions -Wall -O2 -Winline -std=gnu99 -fstrict-aliasing $(ESSENTIAL_HEADERS)
MACROS = __TOOLS $(COMMON_MACROS)
endif

ifeq ($(TYPE),preprocessor)
LDPARAM =
CCPARAM = -nodefaultlibs -mv810 -Wall -Winline -std=gnu99 -fstrict-aliasing $(ESSENTIAL_HEADERS) -E
MACROS = __TOOLS $(COMMON_MACROS)
endif


# Add directories to the include and library paths
INCPATH_ENGINE := $(VBJAENGINE) $(shell find $(VBJAENGINE)/source -type d -print)
INCPATH_GAME := $(shell find * -type d -print)

LIBPATH = $(BUILD_DIR)

# Which files to add to backups, apart from the source code
EXTRA_FILES = makefile

# Where to store object and dependency files.
STORE = $(BUILD_DIR)/$(TYPE)$(STORE_SUFIX)

# Makes a list of the source (.cpp) files.
C_SOURCE := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.c))

# Makes a list of the source (.s) files.
ASSEMBLY_SOURCE := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.s))

# List of header files.
HEADERS := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.h))

# Makes a list of the object files that will have to be created.
C_OBJECTS := $(addprefix $(STORE)/, $(C_SOURCE:.c=.o))

# Makes a list of the object files that will have to be created.
ASSEMBLY_OBJECTS := $(addprefix $(STORE)/, $(ASSEMBLY_SOURCE:.s=.o))

# Same for the .d (dependency) files.
DFILES := $(addprefix $(STORE)/,$(C_SOURCE:.c=.d))

# Specify phony rules. These are rules that are not real files.
.PHONY: clean backup dirs

# Main target. The @ in front of a command prevents make from displaying it to the standard output.

# first build the engine
ENGINE = libvbjae.a

# first build the engine
TARGET = $(BUILD_DIR)/output

# first build the engine
ENGINE = $(BUILD_DIR)/libvbjae.a

deleteEngine:
	rm -f $(ENGINE)

$(ENGINE): deleteEngine
	@echo Building VBJaEngine...
	@echo $(VBJAENGINE)/makefile
	@$(MAKE) -f $(VBJAENGINE)/makefile $@ -e TYPE=$(TYPE) -e CONFIG_FILE=$(CONFIG_FILE) -e CONFIG_MAKE_FILE=$(CONFIG_MAKE_FILE)

all: $(TARGET).vb $(PAD) $(DUMP_TARGET)

pad: $(TARGET).vb
	@echo Padding $(TARGET).vb
	@$(VBJAENGINE)/lib/utilities/padder $(TARGET).vb 3
	@echo " "

$(TARGET).vb: $(TARGET).elf
	@echo Creating $@
	@$(OBJCOPY) -O binary $(TARGET).elf $@
	@echo Done creating $(TARGET).vb in $(TYPE) mode with GCC $(COMPILER)

dump: $(TARGET).elf
	@echo Dumping elf
	@$(OBJDUMP) -t $(TARGET).elf > $(STORE)/sections-$(TYPE).txt
	@$(OBJDUMP) -S $(TARGET).elf > $(STORE)/machine-$(TYPE).asm
	@echo Dumping elf done

$(TARGET).elf: dirs $(ENGINE) $(C_OBJECTS) $(ASSEMBLY_OBJECTS)
	@echo Linking $(TARGET)
	@echo Linking $(ENGINE)
	@$(GCC) -o $@ -nostartfiles $(C_OBJECTS) $(ASSEMBLY_OBJECTS) $(LDPARAM) \
		$(foreach LIBRARY, $(LIBS),-l$(LIBRARY)) $(foreach LIB,$(LIBPATH),-L$(LIB)) -Wl,-Map=$(TARGET).map

# Rule for creating object file and .d file, the sed magic is to add the object path at the start of the file
# because the files gcc outputs assume it will be in the same dir as the source file.
$(STORE)/%.o: %.c
	@echo Compiling $<
	@$(GCC) -Wp,-MD,$(STORE)/$*.dd $(foreach INC,$(INCPATH_ENGINE) $(INCPATH_GAME),-I$(INC))\
        $(foreach MACRO,$(MACROS),-D$(MACRO)) $(CCPARAM)  -$(COMPILER_OUTPUT) $< -o $@
	@sed -e '1s/^\(.*\)$$/$(subst /,\/,$(dir $@))\1/' $(STORE)/$*.dd > $(STORE)/$*.d
	@rm -f $(STORE)/$*.dd

$(STORE)/%.o: %.s
	@echo Creating object file for $*
	@$(AS) -o $@ $<

# Empty rule to prevent problems when a header is deleted.
%.h: ;

# Cleans up the objects, .d files and executables.
clean:
	@echo Cleaning...
	@find $(BUILD_DIR) -maxdepth 1 -type f -exec rm -f {} \;
	@rm -f $(foreach DIR,$(DIRS),$(STORE)/$(DIR)/*.d $(STORE)/$(DIR)/*.o)
	@rm -Rf $(STORE)
	@echo Cleaning done.

# Create necessary directories
dirs:
	@-if [ ! -e $(STORE) ]; then mkdir -p $(STORE); fi;
	@-$(foreach DIR,$(DIRS), if [ ! -e $(STORE)/$(DIR) ]; \
         then mkdir -p $(STORE)/$(DIR); fi; )

# Includes the .d files so it knows the exact dependencies for every source
-include $(DFILES)
