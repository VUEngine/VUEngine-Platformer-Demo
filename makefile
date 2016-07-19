# Makefile taken from Wikipedia.org

# Default build type
TYPE = debug
#TYPE = release
#TYPE = release-tools
#TYPE = preprocessor

# compiler
COMPILER = 4.4
COMPILER_OUTPUT = c
COMPILER_NAME = v810

# linker script
LINKER_SCRIPT = vb.ld

# Small data sections' usage
SMALL_DATA_SECTION_SUFIX =
SMALL_DATA_SECTION_MACRO =

MEMORY_POOL_IN_SRAM =

# include overrides
include config.make

ifeq ($(COMPILER), 4.7)
COMPILER_NAME = v810-nec-elf32
endif

GCC = $(COMPILER_NAME)-gcc
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

ifneq ($(SMALL_DATA_SECTION),)
SMALL_DATA_SECTION_SUFIX = $(SMALL_DATA_SECTION)
SMALL_DATA_SECTION_MACRO = __SMALL_DATA_SECTION=\"$(SMALL_DATA_SECTION)\"
endif

ifeq ($(BSS_IN_SRAM), 1)
LINKER_SCRIPT = vb_sram.ld
endif

# Which directories contain source files
DIRS := $(shell find * -type d -print)

# Which libraries are linked
LIBS =
ROMHEADER=lib/vb.hdr

# Dynamic libraries
DLIBS =

# engine's home
VBJAENGINE = $(VBDE)libs/vbjaengine

# Obligatory headers
VBJAENGINE_CONFIG_FILE = $(shell pwd)/config.h
GAME_ESSENTIALS = 	-include $(VBJAENGINE_CONFIG_FILE) \
					-include $(VBJAENGINE)/libvbjae.h


# The next blocks changes some variables depending on the build type
ifeq ($(TYPE),debug)
LDPARAM = -fno-builtin -ffreestanding -T$(VBJAENGINE)/lib/compiler/extra/$(LINKER_SCRIPT) -L/opt/gccvb/v810/lib/ -L/opt/gccvb/v810/include/ -lm -lvbjae
CCPARAM = -fno-builtin -ffreestanding -nodefaultlibs -mv810 -O0 -Wall -std=gnu99 -fstrict-aliasing $(GAME_ESSENTIALS)
MACROS = __DEBUG __TOOLS $(SMALL_DATA_SECTION_MACRO)
endif

ifeq ($(TYPE), release)
LDPARAM = -T$(VBJAENGINE)/lib/compiler/extra/$(LINKER_SCRIPT) -L/opt/gccvb/v810/lib/ -L/opt/gccvb/v810/include/ -lm -lvbjae
CCPARAM = -nodefaultlibs -mv810 -finline-functions -Wall -O2 -Winline -std=gnu99 -fstrict-aliasing $(GAME_ESSENTIALS)
MACROS = $(SMALL_DATA_SECTION_MACRO)
endif

ifeq ($(TYPE), release-tools)
LDPARAM = -T$(VBJAENGINE)/lib/compiler/extra/$(LINKER_SCRIPT) -L/opt/gccvb/v810/lib/ -L/opt/gccvb/v810/include/ -lm -lvbjae
CCPARAM = -nodefaultlibs -mv810 -finline-functions -Wall -O2 -Winline -std=gnu99 -fstrict-aliasing $(GAME_ESSENTIALS)
MACROS = __TOOLS $(SMALL_DATA_SECTION_MACRO)
endif

ifeq ($(TYPE),preprocessor)
LDPARAM = -T$(VBJAENGINE)/lib/compiler/extra/$(LINKER_SCRIPT) -L/opt/gccvb/v810/lib/ -L/opt/gccvb/v810/include/ -lm -lvbjae
CCPARAM = -nodefaultlibs -mv810 -Wall -Winline -std=gnu99 -fstrict-aliasing $(GAME_ESSENTIALS) -E
MACROS = __TOOLS $(SMALL_DATA_SECTION_MACRO)
endif


# Add directories to the include and library paths
INCPATH_ENGINE := $(shell find $(VBJAENGINE) -type d -print)
INCPATH_GAME := $(shell find * -type d -print)

LIBPATH =

# Which files to add to backups, apart from the source code
EXTRA_FILES = makefile

# Where to store object and dependency files.
STORE = .make-$(TYPE)-$(COMPILER)-$(COMPILER_OUTPUT)$(SMALL_DATA_SECTION_SUFIX)

# Makes a list of the source (.cpp) files.
SOURCE := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.c))

# List of header files.
HEADERS := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.h))

# Makes a list of the object files that will have to be created.
OBJECTS := $(addprefix $(STORE)/, $(SOURCE:.c=.o))

# Same for the .d (dependency) files.
DFILES := $(addprefix $(STORE)/,$(SOURCE:.c=.d))

# Specify phony rules. These are rules that are not real files.
.PHONY: clean backup dirs

# Main target. The @ in front of a command prevents make from displaying it to the standard output.

# first build the engine
ENGINE = libvbjae.a

# first build the engine
TARGET = ouput$(SMALL_DATA_SECTION_SUFIX)

all: $(TARGET).vb $(PAD) $(DUMP_TARGET)

pad: $(TARGET).vb
	@echo "Padding " $(TARGET).vb
	@$(VBJAENGINE)/lib/utilities/padder $(TARGET).vb
	@echo " "

deleteEngine:
	@rm -f $(ENGINE)

$(ENGINE): deleteEngine
	@$(MAKE) -f $(VBJAENGINE)/makefile $@ -e TYPE=$(TYPE) -e COMPILER=$(COMPILER) -e COMPILER_OUTPUT=$(COMPILER_OUTPUT) -e SMALL_DATA_SECTION=$(SMALL_DATA_SECTION) -e MEMORY_POOL_IN_SRAM=$(MEMORY_POOL_IN_SRAM) -e BSS_IN_SRAM=$(BSS_IN_SRAM) -e CONFIG_FILE=$(VBJAENGINE_CONFIG_FILE)

$(TARGET).vb: $(TARGET).elf
	@echo Creating $@
	@$(OBJCOPY) -O binary $(TARGET).elf $@
	@echo Done creating $(TARGET).vb in $(TYPE) mode with GCC $(COMPILER)

dump: $(TARGET).elf
	@echo
	@echo Dumping elf
	@$(OBJDUMP) -t $(TARGET).elf > sections-$(TYPE)-$(COMPILER)$(SMALL_DATA_SECTION_SUFIX).txt
	@$(OBJDUMP) -S $(TARGET).elf > machine-$(TYPE)-$(COMPILER)$(SMALL_DATA_SECTION_SUFIX).asm
	@echo Dumping elf done

$(TARGET).elf: $(ENGINE) dirs $(OBJECTS)
	@echo Linking $(TARGET)
	@$(GCC) -o $@ -nostartfiles $(OBJECTS) $(LDPARAM) \
		$(foreach LIBRARY, $(LIBS),-l$(LIBRARY)) $(foreach LIB,$(LIBPATH),-L$(LIB)) -Wl,-Map=$(TARGET)-$(COMPILER).map

# Rule for creating object file and .d file, the sed magic is to add the object path at the start of the file
# because the files gcc outputs assume it will be in the same dir as the source file.
$(STORE)/%.o: %.c
	@echo Creating object file for $*
	@$(GCC) -Wp,-MD,$(STORE)/$*.dd $(CCPARAM) $(foreach INC,$(INCPATH_ENGINE) $(INCPATH_GAME),-I$(INC))\
        $(foreach MACRO,$(MACROS),-D$(MACRO)) -$(COMPILER_OUTPUT) $< -o $@
	@sed -e '1s/^\(.*\)$$/$(subst /,\/,$(dir $@))\1/' $(STORE)/$*.dd > $(STORE)/$*.d
	@rm -f $(STORE)/$*.dd

# Empty rule to prevent problems when a header is deleted.
%.h: ;

# Cleans up the objects, .d files and executables.
clean:
	@echo Making clean.
	@-rm -f $(foreach DIR,$(DIRS),$(STORE)/$(DIR)/*.d $(STORE)/$(DIR)/*.o)
	@-rm -Rf $(STORE)
	@-rm -f $(ENGINE)

# Backup the source files.
backup:
	@-if [ ! -e .backup ]; then mkdir .backup; fi;
	@zip .backup/backup_`date +%d-%m-%y_%H.%M`.zip $(SOURCE) $(HEADERS) $(EXTRA_FILES)

# Create necessary directories
dirs:
	@-if [ ! -e $(STORE) ]; then mkdir $(STORE); fi;
	@-$(foreach DIR,$(DIRS), if [ ! -e $(STORE)/$(DIR) ]; \
         then mkdir -p $(STORE)/$(DIR); fi; )

# Includes the .d files so it knows the exact dependencies for every source
-include $(DFILES)
