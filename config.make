# Compiler's version to use
COMPILER                = 4.7

# Compiler's output
COMPILER_OUTPUT          = c

# Compilation type
# debug:                Adds lots of runtime assertions. Enables debugging tools too.
#                       It is recommended to use SRAM_WRAM = 1 when debugging in order to
#                       avoid stack overflows (SRAM as WRAM only works on emulators).
# release:              For shipping only!
# release-tools:        Same optimization options as release, but adds debugging tools.
# preprocessor:         The .o files are preprocessor's output instead of compiler's.
TYPE                    = release

# Frame pointer's usage
# 0:                    Omit.
# 1:                    Use.
USE_FRAME_POINTER       = 0

# Prolog functions' usage
# 0:                    Omit.
# 1:                    Use.
USE_PROLOG_FUNCTIONS    = 0

# Pad ROM for hardware testing
# 0:                    No padding.
# 1:                    Pad the ROM for hardware testing.
PAD_ROM                 = 1

# Dump elf
# 0:                    No dumping.
# 1:                    Dump the assembly code and the memory sections.
DUMP_ELF                = 1

# Sections' usage
# SRAM's usage
# You can use SRAM as WRAM. It adds, theoretically, 16MB of WRAM where all non initialized variables can be allocated.
# This feature is experimental and only works properly on emulators.
# Since only 8KB of SRAM is available on real carts, more than that will only work on emulators.
# To make effective any change to these options, the whole project needs to be recompiled.

# valid options are [/.bss/.sbss/.sram]
MEMORY_POOL_SECTION                     = .sbss
# valid options are [/.bss/.sbss/.sram]
NON_INITIALIZED_DATA_SECTION            = .sbss
# valid options are [/.data/.sdata]
INITIALIZED_DATA_SECTION                = .sdata
# valid options are [/.bss/.sbss/.sram]
STATIC_SINGLETONS_DATA_SECTION          = .sbss
# valid options are [/.bss/.sbss/.sram]
VIRTUAL_TABLES_DATA_SECTION             = .sbss


# Size of variables to be loaded in the .sdata section
# Not working properly because rosdata is used instead of rodata section
# MSDA_SIZE = 0

