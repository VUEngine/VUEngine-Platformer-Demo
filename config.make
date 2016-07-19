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
PAD_ROM             = 0

# Dump elf
# 0:                No dumping.
# 1:                Dump the assembly code and the memory sections.
DUMP_ELF            = 1

# Small data section
# [no value]:       Don't use the small data sections.
# [.sdata/.sbss]:   Small data section to use.
SMALL_DATA_SECTION  = .sbss

# SRAM's usage
# 0:                Don't use SRAM as WRAM.
# 1:                Use SRAM as WRAM. Adds, theoretically, 16MB of WRAM where all static variables will be loaded.
#                   Since only 8KB of SRAM is available on real carts, more than that will only work on emulators.
#                   This feature is experimental and only works properly on emulators
#                   The memory pool will be placed in SRAM only if the BSS section is placed too.
#                   To make effective the memory pool's location change, it needs to be recompiled.
BSS_IN_SRAM         = 0
MEMORY_POOL_IN_SRAM = 0
