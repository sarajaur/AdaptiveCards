#pragma once
#include <QObject>
#include <QColor>
#include <QFont>

#include "AdaptiveCardContext.h"
#include "Image.h"
#include <QString>

class ImageModel : public QObject
{

	Q_OBJECT
    Q_PROPERTY(QString bgColor MEMBER mBgColor CONSTANT);
    Q_PROPERTY(bool isImage MEMBER mIsImage CONSTANT);
    Q_PROPERTY(QString sourceImage MEMBER mSourceImage CONSTANT);
    Q_PROPERTY(bool visibleRect MEMBER mVisibleRect CONSTANT);
    Q_PROPERTY(int imageHeight MEMBER mImageHeight CONSTANT);
    Q_PROPERTY(int width MEMBER mWidth CONSTANT);
    Q_PROPERTY(int imageWidth MEMBER mImageWidth CONSTANT);
    Q_PROPERTY(int implicitWidth MEMBER mImplicitWidth CONSTANT);
    Q_PROPERTY(int imageHeightEstimate MEMBER mImageHeightEstimate CONSTANT);
    Q_PROPERTY(QString anchorCenter MEMBER mAnchorCenter CONSTANT);
    Q_PROPERTY(QString anchorRight MEMBER mAnchorRight CONSTANT);
    Q_PROPERTY(int  radius MEMBER mRadius CONSTANT);

public:
    explicit ImageModel(std::shared_ptr<AdaptiveCards::Image> image, QObject* parent = nullptr);
    ~ImageModel();

private:
    QString GetImagePath(const std::string url);

    

private :
    QString mBgColor;
    bool mIsImage;
    QString mSourceImage;
    bool mVisibleRect;
    int mWidth;
    int mImageHeight;
    int mImageWidth;
    int mImplicitWidth;
    int mImageHeightEstimate;
    QString mAnchorCenter;
    QString mAnchorRight;
    int mRadius;
};
