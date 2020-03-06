#include "dlib_plugin.h"
#include "frontalfacedetector.h"
#include "dlibimageprocess.h"
#include <qqml.h>

static QObject* dlibImageProcessProvider(QQmlEngine *engine, QJSEngine *){
    return new lv::DlibImageProcess(engine);
}

void DlibPlugin::registerTypes(const char *uri){
    qmlRegisterType<lv::FrontalFaceDetector>(uri, 1, 0, "FrontalFaceDetector");
    qmlRegisterSingletonType<lv::DlibImageProcess>(
                uri, 1, 0, "ImageProcess", &dlibImageProcessProvider);
}
