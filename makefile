
# ------------------------------------------------
# Makefile
#
# Authors: Mia Wei 
#	   
#
# Changelog :
# 2020-12-05: Inital Makefile
# 2020-12-12: Generate two executables (main program + test program)
#
# ------------------------------------------------
# project name (generate executable with this name)
TARGET   = UNO-Card-Game
TARGET_TEST   = UNO-Card-Game_Test

# change these to proper directories where each file should be
SRCDIR     	 = src
OBJDIR    	 = obj
BINDIR    	 = bin
INCDIR	  	 = include
SRCTESTDIR	 = test/src
INCTESTDIR	 = test/include
OBJTESTDIR   = test/obj

CC       = gcc

#For TARGET   = UNO-Card-Game
INC      := -I$(INCDIR)
SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS1 := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

#For TARGET   = UNO-Card-Game_Test
INC      := -I$(INCTESTDIR)
TSOURCES := $(wildcard $(SRCTESTDIR)/*.c)
OBJECTS2 := $(TSOURCES:$(SRCTESTDIR)/%.c=$(OBJTESTDIR)/%.o)
rm       = rm -f

#For TARGET   = UNO-Card-Game
$(BINDIR)/$(TARGET) : $(OBJECTS1)
	@mkdir -p $(BINDIR)
	@$(CC) $(OBJECTS1) -o $@
	@echo "Linking complete!"
$(OBJECTS1): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(INC) -c $< -o $@
	@echo "Compiled "$<" successfully!"
	
#For TARGET   = UNO-Card-Game_Test
$(BINDIR)/$(TARGET_TEST) :$(OBJECTS2) $(OBJDIR)/cards_management.o $(OBJDIR)/computer_player.o $(OBJDIR)/game.o $(OBJDIR)/human_player_module.o
	@mkdir -p $(BINDIR)
	@$(CC) $(OBJECTS2) $(OBJDIR)/cards_management.o $(OBJDIR)/computer_player.o $(OBJDIR)/game.o $(OBJDIR)/human_player_module.o -o $@
	@echo "Test Linking complete!"
$(OBJECTS2): $(OBJTESTDIR)/%.o : $(SRCTESTDIR)/%.c
	@$(CC) $(INC) -c $< -o $@
	@echo "Test Compiled "$<" successfully!"

#TARGET TO GENERATE ALL THE EXECUTABLES (MAIN PROGRAM + TESTS TOGETHER)
all: $(BINDIR)/$(TARGET)   $(BINDIR)/$(TARGET_TEST)

.PHONY: clean
clean:
	@$(rm) $(OBJECTS1) $(BINDIR)/$(TARGET)
	@$(rm) $(OBJECTS2) $(BINDIR)/$(TARGET_TEST)
	@echo "Cleanup complete!"
