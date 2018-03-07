#include "dlib_plugin.h"
#include "frontalfacedetector.h"
#include <qqml.h>

void DlibPlugin::registerTypes(const char *uri){
    qmlRegisterType<lv::FrontalFaceDetector>(uri, 1, 0, "FrontalFaceDetector");
}
