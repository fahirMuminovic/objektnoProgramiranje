#-------------------------------------------------
#
# Project created by QtCreator 2023-03-01T13:29:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FahirMuminovicObjektnoZadaca
TEMPLATE = app


SOURCES += main.cpp\
		dialog.cpp \
	stanje.cpp \
	tranzicija.cpp

HEADERS  += dialog.h \
	stanje.h \
	tranzicija.h

FORMS    += dialog.ui

CONFIG += c++11
