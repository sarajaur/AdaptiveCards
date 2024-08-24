import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15
import AdaptiveCardQmlEngine 1.0
import "JSUtils/AdaptiveCardUtils.js" as AdaptiveCardUtils

Rectangle {
    id: imageRender
    property var imageModel: model.imageRole
   
    visible: imageModel.visibleRect
    width: (parent.width > 0 && parent.width < imageModel.imageWidth) ? parent.width : imageModel.imageWidth
    implicitHeight: image.implicitHeight / image.implicitWidth * width
    color: imageModel.bgColor
    implicitWidth: image.implicitWidth
    anchors.horizontalCenter: imageModel.anchorCenter ? parent.horizontalCenter : undefined
    anchors.right: imageModel.anchorRight ? parent.right : undefined
    radius: imageModel.radius
    clip: true
 
        Image {
        id: image

        width:imageModel.imageWidth
        height:imageModel.imageWidth  
        source:imageModel.sourceImage
        cache: false
        visible: true
    
        }
}
