#ifndef FRONTALFACEDETECTOR_H
#define FRONTALFACEDETECTOR_H

#include <QQuickItem>
#include "qmatfilter.h"
#include <dlib/image_processing/frontal_face_detector.h>

namespace lv{

class FrontalFaceDetector : public QQuickItem{

    Q_OBJECT
    Q_PROPERTY(QMat* input        READ input WRITE setInput NOTIFY inputChanged)
    Q_PROPERTY(QVariantList faces READ faces NOTIFY facesChanged)

public:
    explicit FrontalFaceDetector(QQuickItem* parent = 0);
    virtual ~FrontalFaceDetector();

    QMat* input();
    void setInput(QMat* input);

    const QVariantList& faces() const;

signals:
    void inputChanged();
    void facesChanged();

protected:
    virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *nodeData);

private:
    void detect();
    dlib::frontal_face_detector m_detector;

    QMat*        m_input;
    QMat*        m_display;
    bool         m_displayDirty;
    QVariantList m_faces;
};

inline QMat *FrontalFaceDetector::input(){
    return m_input;
}

inline void FrontalFaceDetector::setInput(QMat *input){
    m_input = input;
    emit inputChanged();
    detect();
}

inline const QVariantList &FrontalFaceDetector::faces() const{
    return m_faces;
}

}// namespace

#endif // FRONTALFACEDETECTOR_H
