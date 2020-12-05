
# ------------------------------------------------
# Makefile
#
# Authors: Mia Wei 
#	   
# Date  : 2020-12-05
#
# Changelog :
# 2020-12-05: Inital Makefile
#
# ------------------------------------------------

# project name (generate executable with this name)
TARGET   = Group_G_UNO-Card-Game
TARGET_TEST   = UNO_Test

# change these to proper directories where each file should be
SRCDIR     	 = src
SRCTESTDIR	 = test
OBJDIR    	 = obj
BINDIR    	 = bin
INCDIR	  	 = include

CC       = gcc

INC      := -I$(INCDIR)
SOURCES  := $(wildcard $(SRCDIR)/*.c)
TSOURCES := $(wildcard $(SRCTESTDIR)/*.c)
OBJECTS1 := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS2 := $(TSOURCES:$(SRCTESTDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET) : $(OBJECTS1)
	@mkdir -p $(BINDIR)
	@$(CC) $(OBJECTS1) -o $@
	@echo "Linking complete!"

$(OBJECTS1): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJECTS2): $(OBJDIR)/%.o : $(SRCTESTDIR)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS1) $(BINDIR)/$(TARGET)
	@$(rm) $(OBJECTS2) $(BINDIR)/$(TARGET_TEST)
	@echo "Cleanup complete!"
