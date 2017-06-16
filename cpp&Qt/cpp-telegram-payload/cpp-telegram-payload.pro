QT += core network
QT -= gui

CONFIG += c++11

TARGET = cpp-telegram-payload
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

include(../plugin/QtTelegramBot.pri)
