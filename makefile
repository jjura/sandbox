BINDIR := bin
SRCDIR := src
OBJDIR := obj

BIN := sandbox
SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CFLAGS := -Wall -Wextra -Wpedantic -std=c11
LDFLAGS :=

all: $(BINDIR)/$(BIN)

clean:
	@rm -f $(BINDIR)/$(BIN) $(OBJ)

$(BINDIR)/$(BIN): $(OBJ)
	@echo "Assembling binary: $@"
	@mkdir -p $(BINDIR)
	@$(CC) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "-- Building: $@"
	@mkdir -p $(OBJDIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
