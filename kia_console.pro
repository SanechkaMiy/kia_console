QT -= gui
QT += network
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17 console
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread
LIBS += -L/usr/lib -lssl -lcrypto -lrt
LIBS += -ldl
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../../kia_gui/source
DEPENDPATH += $$PWD/../../kia_gui/source
SOURCES += \
#        ltmk.c \
        Kia_bokz/bokz.cpp \
        Kia_bokz/bokzm60.cpp \
        Kia_bi/kia_bi.cpp \
        Kia_bi/kia_biu.cpp \
        Kia_bi/kia_bkpik.cpp \
        Kia_modules/kia_db.cpp \
        Kia_modules/kia_help_functions.cpp \
        Kia_modules/kia_mpi.cpp \
        Kia_modules/kia_port.cpp \
        kia_cyclogram.cpp \
        kia_ftdi.cpp \
        kia_load_initial_settings.cpp \
        kia_matrox.cpp \
        kia_protocol.cpp \
        kia_synch_timer.cpp \
        kiainformationbot.cpp \
        ltmkUsb.c \
        main.cpp \
        parsetodb.cpp \
        simpletimer.cpp \
        timer.cpp \
        workwithmain.cpp \
        workwithstruct.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../../../../usr/local/lib/BiLib_20231123_1653/BiLibNE.h \
    ../../kia_gui/source/Kia_enums.h \
    Kia_modules/kia_db.h \
    Kia_modules/kia_help_functions.h \
    Kia_modules/kia_mpi.h \
    Kia_modules/kia_port.h \
    Kia_struct/Kia_mko_struct.h \
    Kia_bokz/bokz.h \
    Kia_bokz/bokzm60.h \
    config.h \
#    ltmk.h \
    Kia_bi/kia_bi.h \
    Kia_bi/kia_biu.h \
    Kia_bi/kia_bkpik.h \
    kia_cyclogram.h \
    kia_ftdi.h \
    kia_load_initial_settings.h \
    kia_matrox.h \
    kia_protocol.h \
    kia_synch_timer.h \
    kiainformationbot.h \
    ltmkUsb.h \
    mainStruct.h \
    parsetodb.h \
    simpletimer.h \
    timer.h \
    workwithmain.h \
    workwithstruct.h



INCLUDEPATH += Kia_struct/
DEPENDPATH += Kia_struct/

INCLUDEPATH += Kia_bokz/
DEPENDPATH += Kia_bokz/

INCLUDEPATH += Kia_bi/
DEPENDPATH += Kia_bi/
INCLUDEPATH += ../../../../../usr/local/lib/BiLib_20231123_1653
DEPENDPATH += ../../../../../usr/local/lib/BiLib_20231123_1653

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lCppLinuxSerial

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/lib/libCppLinuxSerial.a

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib64/ -lTgBot

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/lib64/libTgBot.a

unix:!macx: LIBS += -L$$PWD/../../../../../usr/lib64/ -lftdi1

INCLUDEPATH += $$PWD/../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../usr/include

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lftd2xx

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../../../opt/matrox_imaging/mil/lib/ -lmil

INCLUDEPATH += $$PWD/../../../../../opt/matrox_imaging/mil/include
DEPENDPATH += $$PWD/../../../../../opt/matrox_imaging/mil/include


unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lpqxx

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/lib/libpqxx.a


unix:!macx: LIBS += -L$$PWD/../../../../../usr/pgsql-13/lib/ -lpq

INCLUDEPATH += $$PWD/../../../../../usr/pgsql-13/include
DEPENDPATH += $$PWD/../../../../../usr/pgsql-13/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../usr/pgsql-13/lib/libpq.a
