#ifndef DLIBIMAGEPROCESS_H
#define DLIBIMAGEPROCESS_H

#include <QObject>
#include <dlib/image_processing/frontal_face_detector.h>
#include "qmatfilter.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing/shape_predictor.h>

namespace lv {

class QmlVariantList;

class DlibImageProcess : public QObject
{
    Q_OBJECT
public:
    explicit DlibImageProcess(QObject *parent = nullptr);

signals:

public slots:
    QVariantList detectFaces(QMat* mat);
    QVariantList detectLandmarks(QMat* mat, QVariant face);
private:
    static dlib::shape_predictor m_shapePredictor;

};

}

#endif // DLIBIMAGEPROCESS_H
