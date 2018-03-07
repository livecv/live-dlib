PLUGIN_NAME = dlib
PLUGIN_PATH = dlib

## PLUGIN_NAME and PLUGIN_PATH must be set up prior to including this config file
include($$LIVECV_DEV_PATH/project/plugin.pri)
TARGET = live_dlib

uri = dlib

DEFINES += Q_LCV

## Dependencies

linkPlugin(live,    live)
linkPlugin(lcvcore, lcvcore)

## Deploying qml is handled by the plugin.pri configuration

## Source

include($$PWD/src/dlib.pri)
include($$LIVECV_DEV_PATH/project/3rdparty/opencv.pri)
include($$PROJECT_ROOT/project/3rdparty/dlib.pri)

OTHER_FILES *= \
    qml/*.qml \
    qml/qmldir
