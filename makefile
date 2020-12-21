
# ------------------------------------------------
# Makefile
#
# Authors: Mia Wei 
#          krithigasr
#	   
#
# Changelog :
# 2020-12-05: Inital Makefile
# 2020-12-12: Generate two executables (main program + test program)
# 2020-12-18: Relocate test object files to the obj folder, instead of test/obj
# 2020-12-20: Adding command for running the application
# 2020-12-21: Adding doxygen command
#
# ------------------------------------------------
# project name (generate executable with this name)
TARGET   = UNO-Card-Game
TARGET_TEST   = UNO-Card-Game_Test

# change these to proper directories where each file should be
BINDIR    	 = bin
OBJDIR    	 = obj
SRCDIR     	 = src
INCDIR	  	 = include
SRCTESTDIR	 = test/src
INCTESTDIR	 = test/include
OBJTESTDIR       = obj

CC       = gcc

#For TARGET   = UNO-Card-Game
INC      := -I$(INCDIR)
SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS1 := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

#For TARGET   = UNO-Card-Game_Test
INC      := -I$(INCTESTDIR)
TSOURCES := $(wildcard $(SRCTESTDIR)/*.c)
OBJECTS2 := $(TSOURCES:$(SRCTESTDIR)/%.c=$(OBJDIR)/%.o)
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
$(BINDIR)/$(TARGET_TEST) :$(OBJDIR)/test.o $(OBJDIR)/test_game.o $(OBJDIR)/test_cards_management.o $(OBJDIR)/test_computer_player.o $(OBJDIR)/test_human_player.o $(OBJDIR)/game.o $(OBJDIR)/cards_management.o $(OBJDIR)/computer_player.o $(OBJDIR)/human_player.o $(OBJDIR)/console_print.o 
	@mkdir -p $(BINDIR)
	@$(CC) $(OBJDIR)/test.o $(OBJDIR)/test_game.o $(OBJDIR)/test_cards_management.o $(OBJDIR)/test_computer_player.o $(OBJDIR)/test_human_player.o $(OBJDIR)/game.o $(OBJDIR)/cards_management.o $(OBJDIR)/computer_player.o $(OBJDIR)/human_player.o $(OBJDIR)/console_print.o -o $@
	@echo "Test Linking complete!"
$(OBJECTS2): $(OBJDIR)/%.o : $(SRCTESTDIR)/%.c
	@$(CC) $(INC) -c $< -o $@
	@echo "Test Compiled "$<" successfully!"

#TARGET TO GENERATE ALL THE EXECUTABLES (MAIN PROGRAM + TESTS TOGETHER)
all: $(BINDIR)/$(TARGET)   $(BINDIR)/$(TARGET_TEST)

# To remove all the previously generated obj files
.PHONY: clean
clean:
	@$(rm) $(OBJECTS1) $(BINDIR)/$(TARGET)
	@$(rm) $(OBJECTS2) $(BINDIR)/$(TARGET_TEST)
	
	@echo "Cleanup complete!"
# To run the game
run: 
	bin/UNO-Card-Game
	
# Command to generate the doxygen files
doxygen:	
	doxygen doc/Doxyfile_config



