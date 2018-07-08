#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T11:41:04
#
#-------------------------------------------------

QT       += gui
QT += core

TARGET = SUB+
TEMPLATE = lib
INCLUDEPATH+="C:\Feflow-Plugin-Develop\IfmLib"
INCLUDEPATH+="C:\Users\Public\Documents\WASY FEFLOW 6.2\sdk\ifm\include"
INCLUDEPATH+="C:\Users\Public\Documents\WASY FEFLOW 6.2\sdk\ifm\include\xdk"
INCLUDEPATH+="C:\Eigen\Eigen"
INCLUDEPATH+="C:\Qt\Static\source\qtbase\include"

INCLUDEPATH += "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2016.4.246/windows/mkl/include"
INCLUDEPATH += "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2016.4.246/windows/mkl/include/intel64"
INCLUDEPATH += "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2016.4.246/windows/mkl/lib/intel64"
INCLUDEPATH += "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2016.4.246/windows/mkl/lib/intel64_win"

LIBS+="C:\Feflow-Plugin-Develop\IfmLib\ifm.lib"
LIBS += "C:\Program Files (x86)\IntelSWTools\compilers_and_libraries_2016.4.246\windows\mkl\lib\intel64_win\mkl_core.lib"
LIBS += "C:\Program Files (x86)\IntelSWTools\compilers_and_libraries_2016.4.246\windows\mkl\lib\intel64_win\mkl_intel_lp64.lib"
LIBS += "C:\Program Files (x86)\IntelSWTools\compilers_and_libraries_2016.4.246\windows\mkl\lib\intel64_win\mkl_intel_thread.lib"
LIBS += "C:\Program Files (x86)\IntelSWTools\compilers_and_libraries_2016.4.246\windows\compiler\lib\intel64_win\libiomp5md.lib"


CONFIG +=shared
DEFINES += SUB_LIBRARY
DEF_FILE+=SUB.def

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        SUB.cpp \
    writetofile.cpp \
    gauss.cpp \
    elementmatrix.cpp

HEADERS += \
        SUB.h \
        sub_global.h \  
    writetofile.h \
    gauss.h \
    elementmatrix.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    SUB.htm \
    SUB.txt \
    SUB.def

FORMS +=
