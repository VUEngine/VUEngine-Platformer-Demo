#Makefile taken from Wikipedia.org
#
# Specify the main target
TARGET = skeleton

# Default build type
TYPE = debug
#TYPE = release
#TYPE = preprocessor

# Which directories contain source files
DIRS := $(shell find source -type d -print)
		
# Which libraries are linked
LIBS =
ROMHEADER=lib/vb.hdr 

# Dynamic libraries
DLIBS =

# Binary output dir
OUTPUT = output

# Obligatory headers
GAME_ESSENTIALS = -include source/game/common.h 	
VBJAENGINE = $(VBDE)/libs/vbjaengine

# The next blocks change some variables depending on the build type
ifeq ($(TYPE),debug)
LDPARAM = -fno-builtin -ffreestanding -T$(VBJAENGINE)/lib/compiler/extra/vb.ld -L/opt/gccvb/v810/lib/ -L/opt/gccvb/v810/include/ -lm -lvbjae
CCPARAM = -fno-builtin -ffreestanding -nodefaultlibs -mv810 -O -Wall $(GAME_ESSENTIALS)
MACROS = __DEBUG
endif

ifeq ($(TYPE), release)
LDPARAM = -T$(VBJAENGINE)/lib/compiler/extra/vb.ld -L/opt/gccvb/v810/lib/ -L/opt/gccvb/v810/include/ -lm -lvbjae
CCPARAM = -nodefaultlibs -mv810 -finline-functions -Wall -O3 -Winline $(GAME_ESSENTIALS)
MACROS = NDEBUG
endif

ifeq ($(TYPE),preprocessor)
LDPARAM = -T$(VBJAENGINE)/lib/compiler/extra/vb.ld -L/opt/gccvb/v810/lib/ -L/opt/gccvb/v810/include/ -lm -lvbjae
CCPARAM = -nodefaultlibs -mv810 -Wall -Winline $(GAME_ESSENTIALS) -E
MACROS = __DEBUG
endif


# Add directories to the include and library paths
INCPATH_ENGINE := $(shell find $(VBJAENGINE) -type d -print)
INCPATH_GAME := $(shell find source -type d -print)
 
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

all: $(TARGET).vb

$(OUTPUT)/$(ENGINE):
		@rm -f $(ENGINE)
		@rm -f $(OUTPUT)/$(ENGINE)

	$(MAKE) -f $(VBJAENGINE)/makefile $@ -e TYPE=$(TYPE) 

	
$(TARGET).vb: $(OUTPUT)/main.elf
	@echo Creating $@
	@$(OBJCOPY) -O binary $(OUTPUT)/main.elf $(OUTPUT)/$@
	@echo $(TARGET).vb done
	@echo Padding $@
	@$(VBJAENGINE)/lib/utilities/padder $(OUTPUT)/$@
	@echo 
#	@echo Generating assembler code
#	@$(OBJDUMP) -t $(OUTPUT)/main.elf > $(OUTPUT)/sections.txt
#	@$(OBJDUMP) -S $(OUTPUT)/main.elf > $(OUTPUT)/machine.asm
	
tryLinkingAgain:
	@echo Error linking, deleting library
	@rm -f $(ENGINE)
	@rm -f $(OUTPUT)/$(ENGINE)
	@make all

$(OUTPUT)/main.elf: $(OUTPUT)/$(ENGINE) dirs $(OBJECTS) 
		@echo Linking $(TARGET).		
		@cp $(OUTPUT)/$(ENGINE) .
		@$(GCC) -o $@ $(OBJECTS) $(LDPARAM) \
			$(foreach LIBRARY, $(LIBS),-l$(LIBRARY)) $(foreach LIB,$(LIBPATH),-L$(LIB)) || tryLinkingAgain
		@rm -f $(ENGINE)
		@rm -f $(OUTPUT)/$(ENGINE)



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
		@-rm -f $(OUTPUT)/*

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