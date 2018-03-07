#ifndef DLIB_PLUGIN_H
#define DLIB_PLUGIN_H

#include <QQmlExtensionPlugin>

class DlibPlugin : public QQmlExtensionPlugin{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // DLIB_PLUGIN_H
