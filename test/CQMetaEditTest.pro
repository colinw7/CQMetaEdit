TEMPLATE = app

TARGET = CQMetaEditTest

QT += widgets

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++14

MOC_DIR = .moc

SOURCES += \
CQMetaEditTest.cpp \

HEADERS += \
CQMetaEditTest.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj

INCLUDEPATH += \
. \
../include \
../../CQUtil/include \
../../CExpr/include \
../../CImageLib/include \
../../CFont/include \
../../CReadLine/include \
../../CFile/include \
../../CMath/include \
../../CStrUtil/include \
../../CUtil/include \
../../COS/include \

unix:LIBS += \
-L../lib \
-L../../CQUtil/lib \
-L../../CImageLib/lib \
-L../../CFont/lib \
-L../../CConfig/lib \
-L../../CMath/lib \
-L../../CReadLine/lib \
-L../../CFileUtil/lib \
-L../../CFile/lib \
-L../../CUtil/lib \
-L../../CRegExp/lib \
-L../../CStrUtil/lib \
-L../../COS/lib \
-lCQMetaEdit -lCQUtil \
-lCImageLib -lCFont -lCConfig -lCMath \
-lCReadLine -lCFileUtil -lCFile -lCRegExp -lCStrUtil \
-lCUtil -lCOS \
-lreadline -lpng -ljpeg -ltre
