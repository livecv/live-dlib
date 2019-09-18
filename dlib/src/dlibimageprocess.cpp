#include "dlibimageprocess.h"
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include "opencv2/imgproc.hpp"
#include "qmatnode.h"
#include "qmatshader.h"
#include <QSGSimpleMaterial>
#include <QVariant>

namespace lv {

dlib::shape_predictor DlibImageProcess::m_shapePredictor;

DlibImageProcess::DlibImageProcess(QObject *parent) : QObject(parent)
{
    try
    {
        // local copy of the "68_landmarks" dat from https://github.com/davisking/dlib-models
        dlib::deserialize("C:/Users/nenad/OneDrive/Desktop/live-dlib-master/dlib/files/68Landmarks.dat") >> m_shapePredictor;
    }
    catch (std::exception e)
    {
        qDebug() << e.what();
    }
}

/**
 * @brief DlibImageProcess::detectFaces
 * @param Image containing faces (QMat)
 * @return Detected faces as rectangles (QRect's)
 */
QVariantList DlibImageProcess::detectFaces(QMat* mat)
{
    if (!mat || mat->cvMat()->channels() != 3) return QVariantList();

    QVariantList result;
    dlib::frontal_face_detector detector(dlib::get_frontal_face_detector());
    dlib::cv_image<dlib::bgr_pixel> cimg(mat->data());
    std::vector<dlib::rectangle> faces = detector(cimg);
    for ( auto it = faces.begin(); it != faces.end(); ++it ){
        dlib::rectangle& face = *it;
        result.append(QRect(face.left(), face.top(), face.width(), face.height()));
    }

    return result;
}

/**
 * @brief DlibImageProcess::detectLandmarks
 * @param Image containing the faces (QMat)
 * @param Rectangle in the image above containing a faces (QRect's)
 * @return 68 landmark points from the face (QVariantList of QPointF's)
 */
QVariantList DlibImageProcess::detectLandmarks(QMat *mat, QVariant face)
{
    if (face.isNull() || face.userType() != QVariant::Rect ||  !mat || mat->cvMat()->channels() != 3) return QVariantList();

    dlib::cv_image<dlib::bgr_pixel> cimg(mat->data());
    dlib::full_object_detection fod;
    QVariantList landmarks;
    dlib::rectangle faceRect;
    QRect rect = face.toRect();
    faceRect.set_top(rect.top());
    faceRect.set_bottom(rect.bottom());
    faceRect.set_left(rect.left());
    faceRect.set_right(rect.right());

    fod = m_shapePredictor(cimg, faceRect);

    for (unsigned int i = 0; i < fod.num_parts(); ++i ){
        landmarks.push_back(QPointF(fod.part(i).x(), fod.part(i).y()));
    }

    return landmarks;
}

}
