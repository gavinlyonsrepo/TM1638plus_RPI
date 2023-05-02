# Gavin lyons 06-2021 
# Makefile to build example program for TM1638plus_RPI library.
# URL: https://github.com/gavinlyonsrepo/TM1638plus_RPI

# ************************************************

# **************************************
# Options
# 1. make  
# 2. make clean
# 3. make run (note :: wraps sudo)
# **************************************

# **** User SRC directory Option Section *********
# pick on example "SRC" dir and ONE ONLY.
# Comment out the others. 
SRC=src/HELLOWORLD_Model1
#SRC=src/HELLOWORLD_Model2
#SRC=src/HELLOWORLD_Model3
#SRC=src/TEST_Model1
#SRC=src/TEST_Model2
#SRC=src/TEST_Model3
# ************************************************


CC=g++
LDFLAGS= -lbcm2835 -lrt -lTM1638plus_RPI
CFLAGS = -Iinclude/ -c -Wall 
MD=mkdir
OBJ=obj
SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp,  $(OBJ)/%.o, $(SRCS))
BIN=./bin
TARGET=$(BIN)/test

all: clean pre-build $(TARGET) 

run:
	sudo $(TARGET) 

pre-build:
	@echo '****************'
	@echo 'START!'
	$(MD) -vp $(BIN)
	$(MD) -vp $(OBJ)


$(TARGET): $(OBJS) $(OBJ)
	@echo 'MAKE EXE FILE'
	$(CC)  $(OBJS) -o $@ $(LDFLAGS)
	@echo 'DONE!'
	@echo '****************'

$(OBJ)/%.o :  $(SRC)/%.cpp   $(OBJ) 
	@echo 'MAKE OBJECT FILE'
	$(CC) $(CFLAGS) $< -o  $@ 

clean:
	@echo '****************'
	@echo 'CLEANUP!'
	rm -vf  $(OBJS) $(TARGET)
	@echo 'DONE!'
	@echo '****************'
