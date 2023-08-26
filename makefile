# ----------------------------
# Makefile Options
# ----------------------------

NAME = GROWMI
ICON = icon.png
DESCRIPTION = "A port of growmi on the ti 84 plus ce"
COMPRESSED = NO
HAS_PRINTF = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
