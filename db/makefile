CROSS =
CC = $(CROSS)gcc 
CXX = $(CROSS)g++ --std=c++11
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
FPIC = -fpic
SHARE = -shared
RM = rm -rf

HEADER_PATH = -I/home/db2inst1/sqllib/include/ -I./
LIB_PATH = -L/home/db2inst1/sqllib/lib/
LIBS = -ldb2 -lpthread

OBJS_DIR = ../objs/

SRCS = $(wildcard ./*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
OBJS_PATH_ALL = $(addsuffix .o, $(addprefix $(OBJS_DIR), $(basename $(notdir $(SRCS)))))

all: $(OBJS)

# %.o %.cpp 别乱改
$(OBJS):%.o:%.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH) $< -o $(OBJS_DIR)$@  $(LIB_PATH) $(LIBS)
	
clean:
	$(RM) $(OBJS_PATH_ALL)
