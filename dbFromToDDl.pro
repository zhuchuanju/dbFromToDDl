TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include (./configData/configData.pri)
include (./readJosnConf/readJosnConf.pri)
include (./transfromData/transfromData.pri)
include (./toOracleDDL/toOracleDDL.pri)
include (./db/db.pri)
