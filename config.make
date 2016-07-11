# compilation type
# debug:            adds lots of runtime assertions, adds debugging tools too
# release:          for shipping only!
# release-tools:    same optimization options as release, but adds debuggint tools
TYPE = release

# SRAM's usage
# 0: don't use as WRAM
# 1: use as WRAM, adds 8KB of WRAM where all static variables will be loaded (experimental)
SRAM_WRAM = 1
