# Compiler's version to use
COMPILER = 4.7

# Compiler's output
COMPILER_OUTPUT = c

# Compilation type
# debug:            Adds lots of runtime assertions. Enables debugging tools too.
#                   It is recommended to use SRAM_WRAM = 1 when debugging in order to
#                   avoid stack overflows (SRAM as WRAM only works on emulators).
# release:          For shipping only!
# release-tools:    Same optimization options as release, but adds debugging tools
# preprocessor:     The .o files are preprocessor's output instead of compiler's.
TYPE                = release

# Pad ROM for hardware testing
# 0:                No padding.
# 1:                Pad the ROM for hardware testing.
PAD_ROM             = 1

# Dump elf
# 0:                No dumping.
# 1:                Dump the assembly code and the memory sections.
DUMP_ELF            = 1

# Sections' usage
# SRAM's usage
# You can use SRAM as WRAM. It adds, theoretically, 16MB of WRAM where all non initialized variables can be allocated.
# This feature is experimental and only works properly on emulators.
# Since only 8KB of SRAM is available on real carts, more than that will only work on emulators.
# To make effective any change to these options, the whole project needs to be recompiled.

# valid options are [/.bss/.sbss/.sram]
MEMORY_POOL_SECTION                     = .bss
# valid options are [/.bss/.sbss/.sram]
NON_INITIALIZED_DATA_SECTION            = .bss
# valid options are [/.data/.sdata]
INITIALIZED_DATA_SECTION                = .data
# valid options are [/.bss/.sbss/.sram]
STATIC_SINGLETONS_DATA_SECTION          = .bss
# valid options are [/.bss/.sbss/.sram]
VIRTUAL_TABLES_DATA_SECTION             = .sbss


# Size of variables to be loaded in the .sdata section
# Only affects the engine since const qualified variables are placed in the .rosdata by the compiler
# and the linking phase fails.
MSDA_SIZE = 0

