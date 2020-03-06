import QtQuick 2.3
import lcvcore 1.0
import dlib 1.0 as DB
import fs 1.0 as FS
import lcvimgproc 1.0 as ImgProc
Column{
    spacing: 5

    
    ImageFile{id: inputFile; visible:false; source: project.path('girl.jpg')}

    ImageFile{id: overlayFile; visible:false; source: project.path('sym2.jpg')}
    
    MatView {
        mat: {     
            
            function readPoints()
            {
                var file = FS.File.open(project.path("sym2.txt"), FS.File.ReadOnly | FS.File.Text)
                var contents = file.read(-1)
                var array = new Uint8Array(contents); 
                
                var points = []
                var number = 0
                var ind = 0
                var p
                for (var i=0; i<array.length; ++i)
                {
                    if (array[i] === 10 || array[i] === 32) 
                    {
                       if (ind === 0)
                        {
                            p  = Qt.point(0.0,0.0)
                            p.x = number
                        } else 
                        {
                            p.y = number
                            points.push(p)
                        }
                        ind = (ind+1)%2
                        number = 0                
                    }
                    else 
                    {
                        number = number*10 + (array[i]-48)
                    }
                }
                
                return points
            }
            
            function pointsFromIndices(points,indices)
            {
                var result = []
                for (var i=0; i<indices.length; ++i)
                    result.push(points[indices[i]])
                    
                return result
            }
            
            function trianglesFromIndices(points,indices)
            {
                var result = []
                for (var i=0; i<indices.length; ++i)
                    result.push([
                                 points[indices[i][0]], 
                                 points[indices[i][1]], 
                                 points[indices[i][2]]
                                ])
                    
                return result   
            }
            
            
            var result = inputFile.output.cloneMat()
            var overlayPoints = readPoints()
            overlayPoints = overlayPoints.slice(0, 68)
                                
            var faces = DB.ImageProcess.detectFaces(inputFile.output)
            if (faces.length == 0) return result

            var inputPoints = DB.ImageProcess.detectLandmarks(inputFile.output, faces[0])
            
            
            
            var hullIndices = ImgProc.ShapeDescriptors.convexHullIndices(overlayPoints)
            var inputHull = pointsFromIndices(inputPoints, hullIndices)
            var overlayHull = pointsFromIndices(overlayPoints, hullIndices)

            var triangleIndices = ImgProc.ShapeDescriptors.DelaunayTriangles(inputFile.output.dimensions(), inputHull)
            
            var inputTrianglePoints = trianglesFromIndices(inputHull, triangleIndices)
            var overlayTrianglePoints = trianglesFromIndices(overlayHull, triangleIndices)
            
            ImgProc.Geometry.warpTriangles(overlayFile.output, result, overlayTrianglePoints, inputTrianglePoints)
            
            return result
        }
    }
    
}
