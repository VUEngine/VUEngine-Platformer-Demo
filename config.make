# compilation type
# debug:            adds lots of runtime assertions, adds debugging tools too
# release:          for shipping only!
# release-tools:    same optimization options as release, but adds debuggint tools
# preprocessor:     the .o files are preprocessor's output instead of compiler's.
TYPE = release

# pad ROM for hardware testing
# 0: no pad
# 1: pad
PAD_ROM = 0

# dump elf
# 0: no dump
# 1: dump
DUMP_ELF = 0

# SRAM's usage
# 0: don't use SRAM as WRAM
# 1: use SRAM as WRAM, adds 8KB of WRAM where all static variables will be loaded (experimental)
SRAM_WRAM = 1
