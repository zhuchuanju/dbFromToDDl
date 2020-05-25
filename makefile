CROSS =
CC = $(CROSS)gcc 
CXX = $(CROSS)g++ --std=c++11
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
RM = rm -rf 

SRCS = $(wildcard ./*/*.cpp ./*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
#OBJS = $(wildcard ./objs/*.o)
#OBJS += $(MAIN_OBJ)

HEADER_PATH = -I/usr/include/ -I./configData/ -I./readJosnConf/ \
			  -I/home/db2inst1/sqllib/include/ -I./db \
			  -I./transfromData
LIB_PATH = -L/usr/lib64/ \
		   -L/home/db2inst1/sqllib/lib/

LIBS = -ljsoncpp -lpthread \
	   -ldb2

TARGET = testCode

$(TARGET):$(OBJS)
	$(CXX) $^ -o $@ $(LIB_PATH) $(LIBS)

$(OBJS):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH) $< -o $@ 

clean:
	$(RM) $(TARGET) $(OBJS)