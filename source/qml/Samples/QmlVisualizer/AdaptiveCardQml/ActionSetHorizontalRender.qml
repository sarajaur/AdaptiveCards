import "AdaptiveCardUtils.js" as AdaptiveCardUtils
import QtQuick 2.3

Flow {
    id: flowActionId

    property int _spacing
    property string _layoutDirection
    property var actionButtonModel
    property var adaptiveCard
    property var _toggleVisibilityTarget: null
    property var activeShowCard: null
    property var prevLoaderId: null
    property bool isCentreAlign: false
    property var rectangleElements: []
    property var actionElements: []

    function handleCentreAligmentFunction() {
        if (isCentreAlign)
            AdaptiveCardUtils.horizontalAlignActionSet(this, actionElements, rectangleElements);

    }

    function setActiveShowCard(showcardLoaderElement, buttonElement) {
        if (prevLoaderId !== null)
            prevLoaderId.visible = false;

        if (activeShowCard !== null)
            activeShowCard.showCard = !activeShowCard.showCard;

        if (buttonElement == activeShowCard) {
            activeShowCard = null;
            prevLoaderId = null;
            return ;
        }
        buttonElement.showCard = !buttonElement.showCard;
        showcardLoaderElement.visible = !showcardLoaderElement.visible;
        activeShowCard = buttonElement;
        prevLoaderId = showcardLoaderElement;
    }

    onWidthChanged: handleCentreAligmentFunction()
    onImplicitWidthChanged: handleCentreAligmentFunction()
    onImplicitHeightChanged: handleCentreAligmentFunction()
    Component.onCompleted: {
        handleCentreAligmentFunction();
    }
    width: parent.width
    spacing: _spacing
    layoutDirection: _layoutDirection === 'Qt.RightToLeft' ? Qt.RightToLeft : Qt.LeftToRight

   ActionSetRepeaterElement {
        model: actionButtonModel
        _rectangleElements: rectangleElements
        _actionElements: actionElements
        toggleVisibilityTarget: _toggleVisibilityTarget
        _setActiveShowCard: setActiveShowCard
        _adaptivecard: adaptiveCard
        _width:  flowActionId.width > implicitWidth ? implicitWidth :  flowActionId.width
        parentElement: flowActionId
   }

}
