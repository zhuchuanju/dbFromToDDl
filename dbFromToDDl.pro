TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include (./configData/configData.pri)
include (./readJosnConf/readJosnConf.pri)
include (./db2/db2.pri)
include (./oracle/oracle.pri)
