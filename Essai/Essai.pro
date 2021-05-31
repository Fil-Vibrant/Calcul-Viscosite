QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        delta0.cpp \
        calibration.cpp \
        viscosite.cpp \
        essai.cpp \
        main.cpp

HEADERS += \
    delta0.h \
    calibration.h \
    viscosite.h \
    essai.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/'../../../../../../Program Files/scilab-5.5.2/modules/core/includes'
INCLUDEPATH += $$PWD/'../../../../../../Program Files/scilab-5.5.2/modules/call_scilab/includes'
INCLUDEPATH += $$PWD/'../../../../../../Program Files/scilab-5.5.2/modules/api_scilab/includes'


unix|win32: LIBS += -L$$PWD/'../../../../../../Program Files/scilab-5.5.2/bin/' -lapi_scilab

INCLUDEPATH += $$PWD/'../../../../../../Program Files/scilab-5.5.2/bin'
DEPENDPATH += $$PWD/'../../../../../../Program Files/scilab-5.5.2/bin'



win32: LIBS += -L$$PWD/'../../../../../../Program Files/scilab-5.5.2/bin/' -lcall_scilab

INCLUDEPATH += $$PWD/'../../../../../../Program Files/scilab-5.5.2/bin'
DEPENDPATH += $$PWD/'../../../../../../Program Files/scilab-5.5.2/bin'

