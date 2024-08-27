TARGET:=ThreadPool
TOPDIR:=$(shell pwd)
CC:=gcc
HEADER_DIR:=$(TOPDIR)/header
SRC_DIR:=$(TOPDIR)/src
LIBS:=pthread
SRC:=$(wildcard $(SRC_DIR)/*.c)
OBJ:=$(subst .c,.o,$(SRC))
OBJ:=$(subst $(SRC_DIR)/,,$(OBJ))
STAGING_DIR:=$(TOPDIR)/staging
BIN_DIR:=$(STAGING_DIR)/bin
OBJ_DIR:=$(STAGING_DIR)/obj
CFLAGS:=-Wall -std=c11

$(TARGET): dir $(OBJ)
	$(CC) -o $(BIN_DIR)/$(TARGET) $(OBJ_DIR)/*.o $(CFLAGS) -l$(LIBS) $(CFLAGS)

dir:
	mkdir $(STAGING_DIR)
	mkdir $(BIN_DIR)
	mkdir $(OBJ_DIR)
$(OBJ): %.o: $(SRC_DIR)/%.c
	$(CC) -c -o $(OBJ_DIR)/$@ -I$(HEADER_DIR) $< 
	

.PHONY: clean

clean: 
	rm -r $(STAGING_DIR)	 