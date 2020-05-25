CROSS =
CC = $(CROSS)gcc 
CXX = $(CROSS)g++ --std=c++11
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
RM = rm -rf 



SRCS_JSON = $(wildcard ./readJosnConf/*.cpp)
OBJS_JSON = $(patsubst %.cpp, %.o, $(SRCS_JSON))
HEADERS_PATH_JSON = -I./configData/ -I/usr/include/ -I./readJosnConf/
LIBS_PATH_JSON = -L/usr/lib64/
LIBS_JSON = -ljsoncpp

SRCS_DB2 = $(wildcard ./db2/*.cpp)
OBJS_DB2 = $(patsubst %.cpp, %.o, $(SRCS_DB2))
HEADER_PATH_DB2 = -I./configData/ -I/home/db2inst1/sqllib/include/ -I./db2/
LIB_PATH_DB2 = -L/home/db2inst1/sqllib/lib/
LIBS_DB2 = -ldb2

SRCS_ORACLE = $(wildcard ./oracle/*.cpp)
OBJS_ORACLE = $(patsubst %.cpp, %.o, $(SRCS_ORACLE))
HEADER_PATH_ORACLE = -I./configData/ -I/usr/local/oracle/instantclient_12_2/sdk/include -I./oracle/ 
LIB_PATH_ORACLE = -L/usr/local/oracle/instantclient_12_2/
LIBS_ORACLE = -lsqlplus -lclntsh -lpthread

HEADER_PATH = -I/usr/include/ -I./configData/ -I./readJosnConf/ \
			  -I/home/db2inst1/sqllib/include/ -I./db \
			  -I/usr/local/oracle/instantclient_12_2/sdk/include 
			  
LIB_PATH += $(LIBS_PATH_JSON)
LIB_PATH += $(LIB_PATH_DB2) 
LIB_PATH += $(LIB_PATH_ORACLE)  
#-L/usr/lib64/ \
#		   -L/home/db2inst1/sqllib/lib/ \
#		   -L/usr/local/oracle/instantclient_12_2

LIBS = -ljsoncpp -lpthread \
	   -ldb2 \
	   -lsqlplus -lclntsh

TARGET = testCode
SRCS_MAIN = $(wildcard ./*.cpp)
OBJS_MAIN = $(patsubst %.cpp, %.o, $(SRCS_MAIN))
#OBJS_MAIN += $(OBJS_JSON)
#OBJS_MAIN += $(OBJS_DB2)
#OBJS_MAIN += $(OBJS_ORACLE)
HEADER_PATH_MAIN = -I./configData/ -I./readJosnConf/ -I./db2/ -I./oracle/ -I/usr/local/oracle/instantclient_12_2/sdk/include

#all:
	#echo $(OBJS_MAIN)
	

$(TARGET):$(OBJS_JSON) $(OBJS_DB2) $(OBJS_ORACLE) $(OBJS_MAIN)
	$(CXX) $(CFLAGS) $^ -o $@ $(LIB_PATH) $(LIBS)
#all: $(OBJS_JSON) $(OBJS_DB2) $(OBJS_ORACLE) $(OBJS_MAIN)
#$(OBJS_ORACLE) 

$(OBJS_JSON):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADERS_PATH_JSON) $< -o $@ 
	
$(OBJS_DB2):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH_DB2) $< -o $@ 
	
$(OBJS_ORACLE):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH_ORACLE) $< -o $@ 
	
$(OBJS_MAIN):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH_MAIN) $< -o $@ 

clean:
	$(RM) $(TARGET) $(OBJS_JSON) $(OBJS_DB2) $(OBJS_ORACLE) $(OBJS_MAIN) 
#$(OBJS_DB2) $(OBJS_ORACLE)
#$(OBJS_ORACLE) $(OBJS_MAIN)