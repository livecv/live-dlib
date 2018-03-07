#include "frontalfacedetector.h"
#include "opencv2/imgproc.hpp"
#include "qmatnode.h"
#include "qmatshader.h"
#include <QSGSimpleMaterial>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>

namespace lv{

FrontalFaceDetector::FrontalFaceDetector(QQuickItem *parent)
    : QQuickItem(parent)
    , m_detector(dlib::get_frontal_face_detector())
    , m_input(QMat::nullMat())
    , m_display(new QMat)
    , m_displayDirty(false)
{
    setFlag(ItemHasContents, true);
}

FrontalFaceDetector::~FrontalFaceDetector(){
    delete m_display;
}

QSGNode *FrontalFaceDetector::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *){
    if ( m_displayDirty ){
        m_input->cvMat()->copyTo(*m_display->cvMat());
        setImplicitWidth(m_display->data().cols);
        setImplicitHeight(m_display->data().rows);
        for ( auto it = m_faces.begin(); it != m_faces.end(); ++it ){
            QRect qr = it->toRect();
            cv::Rect r(qr.x(), qr.y(), qr.width(), qr.height());
            cv::rectangle(*m_display->cvMat(), r, cv::Scalar(255, 255, 0));
        }
        m_displayDirty = false;
    }

    QMatNode *n = static_cast<QMatNode*>(node);
    if (!node)
        n = new QMatNode();

    QSGGeometry::updateTexturedRectGeometry(n->geometry(), boundingRect(), QRectF(0, 0, 1, 1));
    QMatState* state = static_cast<QSGSimpleMaterial<QMatState>*>(n->material())->state();
    state->mat          = m_display;
    state->textureSync  = false;
    state->linearFilter = false;
    n->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);

    return n;
}

void FrontalFaceDetector::detect(){
    m_faces.clear();
    if ( m_input->cvMat()->channels() == 3 ){
        dlib::cv_image<dlib::bgr_pixel> cimg(*m_input->cvMat());
        std::vector<dlib::rectangle> faces = m_detector(cimg);
        for ( auto it = faces.begin(); it != faces.end(); ++it ){
            dlib::rectangle& face = *it;
            m_faces.append(QRect(face.left(), face.top(), face.width(), face.height()));
        }

        emit facesChanged();
        m_displayDirty = true;
        update();
    }
}

}// namespace
