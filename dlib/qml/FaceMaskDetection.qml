import QtQuick 2.3
import lcvcore 1.0
import dlib 1.0 as DB
import fs 1.0 as FS
import lcvimgproc 1.0 as ImgProc

Item {
    id: faceMaskDetector
    property Mat input: null
    property Mat output: null

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



    onInputChanged: {

        var result = input.cloneMat()

        var faces = DB.ImageProcess.detectFaces(input)
        if (faces.length === 0) return result

        var inputPoints = DB.ImageProcess.detectLandmarks(input, faces[0])

        var hullIndices = ImgProc.ShapeDescriptors.convexHullIndices(inputPoints)
        var inputHull = pointsFromIndices(inputPoints, hullIndices)

        var triangleIndices = ImgProc.ShapeDescriptors.DelaunayTriangles(input.dimensions(), inputHull)

        var inputTrianglePoints = trianglesFromIndices(inputHull, triangleIndices)

        result = ImgProc.ShapeDescriptors.getMaskFromHullPoints(inputHull, input.dimensions(), input.depth())

        output = result
    }
}
