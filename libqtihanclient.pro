#-------------------------------------------------
#
# Project created by QtCreator 2014-03-15T21:59:46
#
#-------------------------------------------------

QT       -= core gui

TARGET = qtihanclient
TEMPLATE = lib
CONFIG += lib_bundle c++11 staticlib

include (libihanclient.pri)

SOURCES = $$QTIHANCLIENTSOURCES
HEADERS = $$QTIHANCLIENTHEADERS
