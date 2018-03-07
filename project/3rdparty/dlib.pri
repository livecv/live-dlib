# Avoid Multiple Inclusion
isEmpty(DLIBCONFIG_PRO){
DLIBCONFIG_PRO = 1

win32{
    INCLUDEPATH += $$(dlib_DIR)/../../../include
    LIBS += -L$$(dlib_DIR)/../.. -ldlib
}

unix{
    # Unix Configuration
    macx:QT_CONFIG -= no-pkg-config

    CONFIG += link_pkgconfig
    PKGCONFIG += dlib-1
}


}
