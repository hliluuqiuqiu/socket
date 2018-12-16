CC := g++
MKDIR := mkdir
RM := rm -fr

DIR_OBJS := objs
DIR_TARGET := target

DIRS := $(DIR_OBJS) $(DIR_TARGET)
DEBUG := true
CPP_FLAG := -std=c++11
LD_FLAG := -lpthread
TARGET := $(DIR_TARGET)/tcpServer.out
# main.c const.c func.c
SRCS := $(wildcard *.cpp)
# main.o const.o func.o
OBJS := $(SRCS:.cpp=.o)
# objs/main.o objs/const.o objs/func.o
OBJS := $(addprefix $(DIR_OBJS)/, $(OBJS))

.PHONY : rebuild clean all

$(TARGET) : $(DIRS) $(OBJS)
	$(CC) -o $@ $(OBJS) $(LD_FLAG)
	@echo "Target File ==> $@"
	
$(DIRS) :
	$(MKDIR) $@
	

$(DIR_OBJS)/%.o : %.cpp
    ifeq ($(DEBUG),true)
		$(CC) -o $@ -g -c $^  $(CPP_FLAG)
    else   
		$(CC) -o $@ -c $^  $(CPP_FLAG)
    endif
	
rebuild : clean all

all : $(TARGET)

clean :
	$(RM) $(DIRS)
	
	
