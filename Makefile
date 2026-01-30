# ----------------------------
# agondev Makefile
# ----------------------------

NAME = ledflash
DESCRIPTION = "Flash the old LED"

FAE_HOME = ~/agon/fab/

# ----------------------------
include $(shell agondev-config --makefile)

install: bin/$(NAME).bin
	cp bin/$(NAME).bin ../$(NAME).bin
	cp bin/$(NAME).bin $(FAE_HOME)/sdcard/$(NAME).bin
