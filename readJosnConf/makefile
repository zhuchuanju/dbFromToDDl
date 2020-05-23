CROSS =
CC = $(CROSS)gcc 
CXX = $(CROSS)g++ --std=c++11
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
FPIC = -fpic
SHARE = -shared
RM = rm -rf

HEADER_PATH = -I/usr/include/ -I../configData -I./
LIB_PATH = -L/usr/lib64/
LIBS = -ljsoncpp -lpthread

OBJS_DIR = ../objs/

SRCS = $(wildcard ./*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
#OBJS = $(addsuffix .o, $(addprefix $(OBJS_DIR), $(basename $(notdir $(SRCS)))))

all: $(OBJS)

# %.o %.cpp 别乱改
$(OBJS):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH) $< -o $@  $(LIB_PATH) $(LIBS)
	
clean:
	$(RM) $(OBJS)
