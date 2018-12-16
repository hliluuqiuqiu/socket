CC := g++
MAKE := make
MK := mkdir
RM := rm -rf

.PHONY: all clean rebuild

EXE_DIR := target
DEP_DIR := deps
OBJ_DIR := objs
DIRS :=  $(DEP_DIR) $(OBJ_DIR) $(EXE_DIR)
EXE := $(EXE_DIR)/helloMake.out
SRC_SUFFIX := cpp
C_FLAG := -g -std=c++11
LD_FLAG := -pthread

SRCS := $(wildcard *.$(SRC_SUFFIX))
OBJS := $(SRCS:.$(SRC_SUFFIX)=.o)
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJS))
DEPS := $(SRCS:.$(SRC_SUFFIX)=.dep)
DEPS := $(addprefix $(DEP_DIR)/, $(DEPS))

all : $(OBJ_DIR) $(EXE_DIR) $(EXE)

ifeq ("$(MAKECMDGOALS)","all")
include $(DEPS)
endif


ifeq ("$(MAKECMDGOALS)","")
include $(DEPS)
endif



$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LD_FLAG)
#	echo $(SRCS)
#	echo $(OBJS)
#	echo $(DEPS)

$(DIRS):
#	echo $@
	$(MK)	$@
$(OBJ_DIR)/%.o : %.$(SRC_SUFFIX)
	$(CC) -o $@ -c $(filter %.$(SRC_SUFFIX),$^) $(C_FLAG)

ifeq ("$(wildcard $(DEP_DIR))","")
$(DEP_DIR)/%.dep : $(DEP_DIR) %.$(SRC_SUFFIX)
else
$(DEP_DIR)/%.dep : %.$(SRC_SUFFIX)
endif
	@set -e ; \
		$(CC) -MM -E $(filter %.$(SRC_SUFFIX),$^) | sed 's,\(.*\)\.o[ :]*,objs/\1.o $@:, g' > $@

clean:
	$(RM) $(OBJ_DIR) $(EXE_DIR) $(DEP_DIR)

rebuild:
	$(MAKE) clean
	$(MAKE) all





