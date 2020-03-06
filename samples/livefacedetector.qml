import QtQuick 2.3
import lcvcore 1.0
import dlib 1.0
Column{

    property string videoPath : ""//project.path('gaga.mp4')

    VideoCapture{
        id : videoArea
        loop : true
        fps : 1
        Component.onCompleted : staticOpen(parent.videoPath)
    }
    
    FaceMaskDetection {
        id: fmd
        input: videoArea.output
    }
    
    MatView {
        mat: fmd.output
    }

}