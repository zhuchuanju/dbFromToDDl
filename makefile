CROSS =
CC = $(CROSS)gcc 
CXX = $(CROSS)g++ --std=c++11
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
RM = rm -rf 

SRCS = $(wildcard ./*.cpp)
MAIN_OBJ = $(patsubst %.cpp, %.o, $(SRCS))
OBJS = $(wildcard ./objs/*.o)

HEADER_PATH = -I/usr/include/ -I./configData/ -I./readJosnConf/
LIB_PATH = -L/usr/lib64/

LIBS = -ljsoncpp -lpthread

TARGET = testCode

$(TARGET) : $(MAIN_OBJ)
	$(CXX) $^ -o $@ $(OBJS) $(LIB_PATH) $(LIBS)

$(MAIN_OBJ):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH) $< -o $@ 

clean:
	$(RM) $(TARGET)