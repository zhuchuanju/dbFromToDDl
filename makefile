CROSS =
CC = $(CROSS)gcc 
CXX = $(CROSS)g++ --std=c++11
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
OFLAGS = $(DEBUG) -Wall -o
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

SRCS_MYSQL = $(wildcard ./mysql/*.cpp)
OBJS_MYSQL = $(patsubst %.cpp, %.o, $(SRCS_MYSQL))
HEADER_PATH_MYSQL = -I./configData/ -I./mysql/ 
LIB_PATH_MYSQL = -L/usr/lib64/
LIBS_MYSQL = -lodbc -lpthread 

TARGET = testCode
SRCS_MAIN = $(wildcard ./*.cpp)
OBJS_MAIN = $(patsubst %.cpp, %.o, $(SRCS_MAIN))

HEADER_PATH_MAIN = -I./configData/ 
HEADER_PATH_MAIN += -I./readJosnConf/ 
HEADER_PATH_MAIN += -I./db2/ -I/home/db2inst1/sqllib/include/
#HEADER_PATH_MAIN += -I./oracle/ 
#HEADER_PATH_MAIN += -I./mysql/ 

OBJS_ALL = $(OBJS_MAIN)
OBJS_ALL += $(OBJS_JSON) 
OBJS_ALL += $(OBJS_DB2) 
#OBJS_ALL += $(OBJS_ORACLE)
#OBJS_ALL += $(OBJS_MYSQL) 


LIBS_ALL = $(LIBS_PATH_JSON) $(LIBS_JSON)
LIBS_ALL += $(LIB_PATH_DB2) $(LIBS_DB2)
#LIBS_ALL += $(LIB_PATH_ORACLE) $(LIBS_ORACLE)
#LIBS_ALL += $(LIB_PATH_MYSQL) $(LIBS_MYSQL)

$(TARGET):$(OBJS_ALL)
	$(CXX) $(OFLAGS) $@ $^ $(LIBS_ALL)

$(OBJS_JSON):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADERS_PATH_JSON) $< -o $@ 
	
$(OBJS_DB2):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH_DB2) $< -o $@ 
	
$(OBJS_ORACLE):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH_ORACLE) $< -o $@ 

$(OBJS_MYSQL):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH_MYSQL) $< -o $@ 
	
$(OBJS_MAIN):%.o : %.cpp
	$(CXX) $(CFLAGS) $(HEADER_PATH_MAIN) $< -o $@ 

clean:
	$(RM) $(TARGET) $(OBJS_ALL) 