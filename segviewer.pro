# -------------------------------------------------
# Project created by QtCreator 2010-02-22T12:07:36
# -------------------------------------------------
TARGET = segviewer
TEMPLATE = app
SOURCES += main.cpp \
    segviewer.cpp \
    ocropusthread.cpp \
    proxythread.cpp \
    imageview.cpp
HEADERS += segviewer.h \
    ocropusthread.h \
    proxythread.h \
    imageview.h
FORMS += segviewer.ui

# add specific install locations to path if the ocropus
# install and version envs are set:
exists ( $$(OI) ) {
    # Add iulib include path
    INCLUDEPATH += $$(OI)/iulib/ocropus-$$(OCRVER)/include/iulib

    # Note: colib seems to be included as colib/colib.h
    INCLUDEPATH += $$(OI)/iulib/ocropus-$$(OCRVER)/include


    # Add path to ocropus segmenter code
    INCLUDEPATH += $$(OI)/ocropus/ocropus-$$(OCRVER)/include/ocropus

    # NOTE: This path needs to be in the LD_LIBRARY_PATH to run the binary...
    LIBS += -L$$(OI)/iulib/ocropus-$$(OCRVER)/lib \
        -liulib
    LIBS += -L$$(OI)/ocropus/ocropus-$(OCRVER)/lib \
        -locropus     
}

