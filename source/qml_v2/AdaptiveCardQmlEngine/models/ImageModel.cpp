#include "ImageModel.h"
#include "SharedAdaptiveCard.h"
#include <QDebug.h>
#include "Utils.h"
#include "MarkDownParser.h"


ImageModel::ImageModel(std::shared_ptr<AdaptiveCards::Image> image, QObject* parent) : QObject(parent)
{
    const auto hostConfig = AdaptiveCardQmlEngine::AdaptiveCardContext::getInstance().getHostConfig();
    const auto rendererConfig = AdaptiveCardQmlEngine::AdaptiveCardContext::getInstance().getCardConfig();

    mSourceImage = GetImagePath(image->GetUrl());
    mVisibleRect = image->GetIsVisible() ? "true" : "false";
    mIsImage = true;

    int imageHeightEstimate = 0;
    int imageHeight = 0;
    if (image->GetPixelWidth() != 0 || image->GetPixelHeight() != 0)
    {
        if (image->GetPixelWidth() != 0)
        {
            mImageWidth=image->GetPixelWidth();
            imageHeightEstimate = image->GetPixelWidth();
        }
        if (image->GetPixelHeight() != 0)
        {
            imageHeight = image->GetPixelHeight();
            mImageWidth = imageHeight;

            imageHeightEstimate = image->GetPixelHeight();
        }
    }
    else 
    {
        int imageWidth = 0;
        switch (image->GetImageSize())
        {
        case AdaptiveCards::ImageSize::None:
        case AdaptiveCards::ImageSize::Auto:
        case AdaptiveCards::ImageSize::Small:
            imageWidth = AdaptiveCardQmlEngine::AdaptiveCardContext::getInstance().getHostConfig()->GetImageSizes().smallSize;
            mImageWidth= imageWidth;
            break;
        case AdaptiveCards::ImageSize::Medium:
            imageWidth = AdaptiveCardQmlEngine::AdaptiveCardContext::getInstance().getHostConfig()->GetImageSizes().mediumSize;
            mImageWidth= imageWidth;
            break;
        case AdaptiveCards::ImageSize::Large:
            imageWidth = AdaptiveCardQmlEngine::AdaptiveCardContext::getInstance().getHostConfig()->GetImageSizes().largeSize;
            mImageWidth=imageWidth;
            break;
        }
        imageHeightEstimate = (imageWidth == 0 ? AdaptiveCardQmlEngine::AdaptiveCardContext::getInstance().getHostConfig()->GetImageSizes().smallSize : imageWidth);

        if (image->GetImageSize() != AdaptiveCards::ImageSize::None)
        {
            mImplicitWidth= imageWidth;
        }
    }
    AdaptiveCardQmlEngine::AdaptiveCardContext::getInstance().addHeightEstimate(imageHeightEstimate);

        if (!image->GetBackgroundColor().empty())
        {
            mBgColor =  QString::fromStdString(image->GetBackgroundColor());
        }

    const auto imageHorizontalAlignment = image->GetHorizontalAlignment().value_or(AdaptiveCards::HorizontalAlignment::Left);

        switch (imageHorizontalAlignment)
        {
        case AdaptiveCards::HorizontalAlignment::Center:
            mAnchorCenter = "center";
            break;
        case AdaptiveCards::HorizontalAlignment::Right:
            mAnchorRight = "right";
            break;
        default:
            break;
        }

        switch (image->GetImageStyle())
        {
        case AdaptiveCards::ImageStyle::Default:
            break;
        case AdaptiveCards::ImageStyle::Person:
            mRadius= mImageWidth/2;
            break;
        }
         
}

QString ImageModel::GetImagePath(const std::string url)
{
    if (url.rfind("data:image", 0) == 0)
    {
        return QString::fromStdString(url);
    }

    auto contentNumber = AdaptiveCardQmlEngine::AdaptiveCardContext::getInstance().getContentIndex();
    AdaptiveCardQmlEngine::AdaptiveCardContext::getInstance().incrementContentIndex();
    const auto imageName = QString::number(contentNumber) + ".jpg";
    QString file_path = __FILE__;
    QString dir_path = file_path.left(file_path.lastIndexOf("\\models")) ;
    dir_path.append("\\images\\" + imageName);
    std::replace(dir_path.begin(), dir_path.end(), '\\', '/');
    dir_path =  "file:/" + dir_path;
    return dir_path;
}
ImageModel::~ImageModel()
{
}
