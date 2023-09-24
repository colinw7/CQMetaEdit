TEMPLATE = lib

TARGET = CQMetaEdit

QT += widgets

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++17

MOC_DIR = .moc

CONFIG += staticlib

SOURCES += \
CQMetaEdit.cpp \
CQMetaEditModel.cpp \
CQMetaEditOptions.cpp \
CQMetaEditPalette.cpp \
CQMetaEditTree.cpp \
CQMetaLayoutDelegate.cpp \
CQMetaLayoutEditor.cpp \
CQMetaLayoutModel.cpp \
CQMetaLayoutTree.cpp \
CQMetaPropertyDelegate.cpp \
CQMetaPropertyModel.cpp \
CQMetaPropertyTree.cpp \
CQMetaSignalDelegate.cpp \
CQMetaSignalModel.cpp \
CQMetaSignalTree.cpp \
CQMetaSlotDelegate.cpp \
CQMetaSlotModel.cpp \
CQMetaSlotTree.cpp \
CQMetaWidgetDelegate.cpp \
CQMetaWidgetModel.cpp \
CQMetaWidgetTree.cpp \
CQLinkLabel.cpp \
CQPicker.cpp \

HEADERS += \
CQMetaEditModel.h \
CQMetaEditOptions.h \
CQMetaEditPalette.h \
CQMetaEditTree.h \
CQMetaLayoutDelegate.h \
CQMetaLayoutEditor.h \
CQMetaLayoutModel.h \
CQMetaLayoutTree.h \
CQMetaPropertyDelegate.h \
CQMetaPropertyModel.h \
CQMetaPropertyTree.h \
CQMetaSignalDelegate.h \
CQMetaSignalModel.h \
CQMetaSignalTree.h \
CQMetaSlotDelegate.h \
CQMetaSlotModel.h \
CQMetaSlotTree.h \
CQMetaWidgetDelegate.h \
CQMetaWidgetModel.h \
CQMetaWidgetTree.h \
CQLinkLabel.h \
../include/CQMetaEdit.h \
../include/CQPicker.h \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../include \
../../CQUtil/include \
../../CImageLib/include \
../../CFont/include \
../../CFile/include \
../../CMath/include \
../../CUtil/include \
../../CStrUtil/include \
../../COS/include \
