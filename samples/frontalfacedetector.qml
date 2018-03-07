import QtQuick 2.3
import lcvcore 1.0
import dlib 1.0

Column{
    
    spacing: 5
    
    ImageFile{
        id: imageFile
        source: project.path('girl.jpg')
    }
    
    FrontalFaceDetector{
        input: imageFile.output
    }
    
}