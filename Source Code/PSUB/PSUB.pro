#-------------------------------------------------
#
# Project created by QtCreator 2018-06-12T14:51:55
#
#-------------------------------------------------

QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PSUB
TEMPLATE = app
INCLUDEPATH="C:/Eigen/Eigen"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:RC_ICONS += myIcon.ico

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    BasedClass/importfile.cpp \
    BasedClass/exportfile.cpp \
    BasedClass/importmultifiles.cpp \
    importfeflowmesh.cpp \
    importresultsdata.cpp \
    scalesetting.cpp \
    BasedClass/basescaleclass.cpp \
    BasedClass/basecontoursetting.cpp \
    contoursetting.cpp \
    BasedClass/basecuttingplane.cpp \
    cuttingplane.cpp \
    BasedClass/basestepresult.cpp \
    stepresult.cpp \
    BasedClass/basecontoursetting.cpp \
    BasedClass/basecuttingplane.cpp \
    BasedClass/basescaleclass.cpp \
    BasedClass/basestepresult.cpp \
    BasedClass/exportfile.cpp \
    BasedClass/importfile.cpp \
    BasedClass/importmultifiles.cpp \   
    contoursetting.cpp \
    cuttingplane.cpp \
    importfeflowmesh.cpp \
    importresultsdata.cpp \
    main.cpp \
    mainwindow.cpp \
    scalesetting.cpp \
    stepresult.cpp \
    BasedClass/basecontoursetting.cpp \
    BasedClass/basecuttingplane.cpp \
    BasedClass/basescaleclass.cpp \
    BasedClass/basestepresult.cpp \
    BasedClass/exportfile.cpp \
    BasedClass/importfile.cpp \
    BasedClass/importmultifiles.cpp \
    OpenGLCLass/glwidget.cpp \
    OpenGLCLass/input.cpp \
    contoursetting.cpp \
    cuttingplane.cpp \
    importfeflowmesh.cpp \
    importresultsdata.cpp \
    main.cpp \
    mainwindow.cpp \
    scalesetting.cpp \
    stepresult.cpp \
    BasedClass/base3dviewport.cpp

HEADERS += \
        mainwindow.h \
    mainwindow.h \
    BasedClass/importfile.h \
    BasedClass/exportfile.h \
    BasedClass/importmultifiles.h \
    importfeflowmesh.h \
    importresultsdata.h \
    scalesetting.h \
    BasedClass/basescaleclass.h \
    BasedClass/basecontoursetting.h \
    contoursetting.h \
    BasedClass/basecuttingplane.h \
    cuttingplane.h \
    BasedClass/basestepresult.h \
    stepresult.h \
    BasedClass/basecontoursetting.h \
    BasedClass/basecuttingplane.h \
    BasedClass/basescaleclass.h \
    BasedClass/basestepresult.h \
    BasedClass/exportfile.h \
    BasedClass/importfile.h \
    BasedClass/importmultifiles.h \
    contoursetting.h \
    cuttingplane.h \
    importfeflowmesh.h \
    importresultsdata.h \
    mainwindow.h \
    scalesetting.h \
    stepresult.h \
    BasedClass/basecontoursetting.h \
    BasedClass/basecuttingplane.h \
    BasedClass/basescaleclass.h \
    BasedClass/basestepresult.h \
    BasedClass/exportfile.h \
    BasedClass/importfile.h \
    BasedClass/importmultifiles.h \
    OpenGLCLass/glwidget.h \
    OpenGLCLass/input.h \
    contoursetting.h \
    cuttingplane.h \
    importfeflowmesh.h \
    importresultsdata.h \
    mainwindow.h \
    scalesetting.h \
    stepresult.h \
    BasedClass/base3dviewport.h

FORMS += \
        mainwindow.ui \
    importfeflowmesh.ui \
    importresultsdata.ui \
    scalesetting.ui \
    contoursetting.ui \
    cuttingplane.ui \
    stepresult.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
