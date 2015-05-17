#Makefile taken from Wikipedia.org
#
# Specify the main target
TARGET = output

# Default build type
#TYPE = debug
TYPE = release
#TYPE = preprocessor

# Don't build tools by default
TOOLS = 1

# Which directories contain source files
DIRS := $(shell find * -type d -print)
		
# Which libraries are linked
LIBS =
ROMHEADER=lib/vb.hdr

# Dynamic libraries
DLIBS =

# Obligatory headers
VBJAENGINE = $(VBDE)/libs/vbjaengine
VBJANEGINE_CONFIG_FILE = $(shell pwd)/config.h
GAME_ESSENTIALS = 	-include $(VBJANEGINE_CONFIG_FILE) \
					-include $(VBJAENGINE)/libvbjae.h
						

# The next blocks change some variables depending on the build type
ifeq ($(TYPE),debug)
LDPARAM = -fno-builtin -ffreestanding -T$(VBJAENGINE)/lib/compiler/extra/vb.ld -L/opt/gccvb/v810/lib/ -L/opt/gccvb/v810/include/ -lm -lvbjae
CCPARAM = -fno-builtin -ffreestanding -nodefaultlibs -mv810 -O0 -Wall $(GAME_ESSENTIALS)
ifeq ($(TOOLS),1)
MACROS = __DEBUG __DEBUG_TOOLS __STAGE_EDITOR __ANIMATION_EDITOR
else
MACROS = __DEBUG
endif
endif

ifeq ($(TYPE), release)
LDPARAM = -T$(VBJAENGINE)/lib/compiler/extra/vb.ld -L/opt/gccvb/v810/lib/ -L/opt/gccvb/v810/include/ -lm -lvbjae
CCPARAM = -nodefaultlibs -mv810 -finline-functions -Wall -O3 -Winline $(GAME_ESSENTIALS)
ifeq ($(TOOLS),1)
MACROS = __DEBUG_TOOLS __STAGE_EDITOR __ANIMATION_EDITOR
else
MACROS =
endif
endif

ifeq ($(TYPE),preprocessor)
LDPARAM = -T$(VBJAENGINE)/lib/compiler/extra/vb.ld -L/opt/gccvb/v810/lib/ -L/opt/gccvb/v810/include/ -lm -lvbjae
CCPARAM = -nodefaultlibs -mv810 -Wall -Winline $(GAME_ESSENTIALS) -E
ifeq ($(TOOLS),1)
MACROS = __DEBUG __DEBUG_TOOLS __STAGE_EDITOR __ANIMATION_EDITOR
else
MACROS = __DEBUG
endif
endif


# Add directories to the include and library paths
INCPATH_ENGINE := $(shell find $(VBJAENGINE) -type d -print)
INCPATH_GAME := $(shell find * -type d -print)

LIBPATH =

# Which files to add to backups, apart from the source code
EXTRA_FILES = makefile

# The compiler
GCC = v810-gcc
OBJCOPY = v810-objcopy
OBJDUMP = v810-objdump

# Where to store object and dependancy files.
STORE = .make-$(TYPE)

# Makes a list of the source (.cpp) files.
SOURCE := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.c))

# List of header files.
HEADERS := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.h))

# Makes a list of the object files that will have to be created.
OBJECTS := $(addprefix $(STORE)/, $(SOURCE:.c=.o))

# Same for the .d (dependancy) files.
DFILES := $(addprefix $(STORE)/,$(SOURCE:.c=.d))

# Specify phony rules. These are rules that are not real files.
.PHONY: clean backup dirs

# Main target. The @ in front of a command prevents make from displaying
# it to the standard output.

# first build the engine
ENGINE = libvbjae.a

pad: $(TARGET).vb
	@echo "Padding " $(TARGET).vb
	@$(VBJAENGINE)/lib/utilities/padder $(TARGET).vb

all: $(TARGET).vb

deleteEngine:
		@rm -f $(ENGINE)

$(ENGINE): deleteEngine
	$(MAKE) -f $(VBJAENGINE)/makefile $@ -e TYPE=$(TYPE) -e CONFIG_FILE=$(VBJANEGINE_CONFIG_FILE) -e TOOLS=$(TOOLS)

$(TARGET).vb: main.elf
	@echo Creating $@
	@$(OBJCOPY) -O binary main.elf $@
	@echo $(TARGET).vb done

asm: main.elf
	@echo Generating assembler code...
	@$(OBJDUMP) -t main.elf > sections.txt
	@$(OBJDUMP) -S main.elf > machine.asm
	@echo machine.asm done
	
main.elf: $(ENGINE) dirs $(OBJECTS)
		@echo Linking $(TARGET).
		@$(GCC) -o $@ $(OBJECTS) $(LDPARAM) \
			$(foreach LIBRARY, $(LIBS),-l$(LIBRARY)) $(foreach LIB,$(LIBPATH),-L$(LIB))

# Rule for creating object file and .d file, the sed magic is to add
# the object path at the start of the file because the files gcc
# outputs assume it will be in the same dir as the source file.
$(STORE)/%.o: %.c
		@echo Creating object file for $*...
		@$(GCC) -Wp,-MD,$(STORE)/$*.dd $(CCPARAM) $(foreach INC,$(INCPATH_ENGINE) $(INCPATH_GAME),-I$(INC))\
                $(foreach MACRO,$(MACROS),-D$(MACRO)) -c $< -o $@
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

# Includes the .d files so it knows the exact dependencies for every
# source.
-include $(DFILES)