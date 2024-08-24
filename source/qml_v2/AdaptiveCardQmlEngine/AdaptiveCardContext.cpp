#include "AdaptiveCardContext.h"


namespace AdaptiveCardQmlEngine
{
    AdaptiveCardContext::AdaptiveCardContext()
    : mHostConfig(nullptr)
    {
    }

    AdaptiveCardContext::~AdaptiveCardContext()
    {
    }

    void AdaptiveCardContext::initAdaptiveCardContext()
    {
        // Initializing Host config and Card config
        mCardConfig = std::make_shared<AdaptiveCardQmlEngine::AdaptiveCardConfig>(true);
        mHostConfig = std::make_shared<AdaptiveCards::HostConfig>(AdaptiveCards::HostConfig::DeserializeFromString(DarkConfig::darkConfig));
    }

    void AdaptiveCardContext::setAdaptiveCardTheme(AdaptiveCardEnums::AdaptiveCardTheme theme)
    {
        mAdaptiveCardTheme = theme;

        // ReInitializing AdaptiveCard and Host config
        mCardConfig = std::make_shared<AdaptiveCardConfig>(mAdaptiveCardTheme == AdaptiveCardEnums::AdaptiveCardTheme::DarkTheme ? true : false);

        if (mAdaptiveCardTheme == AdaptiveCardEnums::AdaptiveCardTheme::DarkTheme)
        {
			mHostConfig = std::make_shared<AdaptiveCards::HostConfig>(AdaptiveCards::HostConfig::DeserializeFromString(DarkConfig::darkConfig));
		}
        else
        {
			mHostConfig = std::make_shared<AdaptiveCards::HostConfig>(AdaptiveCards::HostConfig::DeserializeFromString(LightConfig::lightConfig));
		}
    }


    std::shared_ptr<AdaptiveCards::HostConfig> AdaptiveCardContext::getHostConfig()
    {
        return mHostConfig;
    }

    std::shared_ptr<AdaptiveCardConfig> AdaptiveCardContext::getCardConfig()
    {
        return mCardConfig;
    }

    std::string AdaptiveCardContext::getRGBColor(const std::string& color, bool isQml)
    {
        if (color.length() > 1 && color[0] == '#')
        {
            if (color.length() == 7)
            {
                return isQml ? Formatter() << "'" << color << "'" : color;
            }
            if (color.length() == 9)
            {
                try
                {
                    const float opacity = static_cast<float>(Utils::hexStrToInt(color.substr(1, 2))) / 255;
                    const int r = Utils::hexStrToInt(color.substr(3, 2));
                    const int g = Utils::hexStrToInt(color.substr(5, 2));
                    const int b = Utils::hexStrToInt(color.substr(7, 2));
                    return isQml ? Formatter() << "Qt.rgba(" << r << ", " << g << ", " << b << ", " << std::fixed
                                               << std::setprecision(2) << opacity << ")"
                                 : Formatter() << "rgba(" << r << ", " << g << ", " << b << ", " << std::fixed
                                               << std::setprecision(2) << opacity << ")";
                }
                catch (const std::exception&)
                {
                    return isQml ? Formatter() << "'" << color << "'" : color;
                }
            }
        }
        return isQml ? Formatter() << "'" << color << "'" : color;
    }

    QString AdaptiveCardContext::getColor(AdaptiveCards::ForegroundColor color, bool isSubtle, bool highlight, bool isQml)
    {
        AdaptiveCards::ColorConfig colorConfig; 
        switch (color)
        {
        case AdaptiveCards::ForegroundColor::Accent:
            colorConfig = mRenderArgs.GetForegroundColors().accent;
            break;
        case AdaptiveCards::ForegroundColor::Good:
            colorConfig = mRenderArgs.GetForegroundColors().good;
            break;
        case AdaptiveCards::ForegroundColor::Warning:
            colorConfig = mRenderArgs.GetForegroundColors().warning;
            break;
        case AdaptiveCards::ForegroundColor::Attention:
            colorConfig = mRenderArgs.GetForegroundColors().attention;
            break;
        case AdaptiveCards::ForegroundColor::Dark:
            colorConfig = mRenderArgs.GetForegroundColors().attention;
            break;
        case AdaptiveCards::ForegroundColor::Light:
            colorConfig = mRenderArgs.GetForegroundColors().light;
            break;
        default:
            if (mAdaptiveCardTheme == AdaptiveCardEnums::AdaptiveCardTheme::DarkTheme)
            {
				colorConfig = mRenderArgs.GetForegroundColors().light;
			}
            break;
        }

        if (highlight)
        {
            const auto color = isSubtle ? colorConfig.highlightColors.subtleColor : colorConfig.highlightColors.defaultColor;
            return QString::fromStdString(color);
        }
        else
        {
            const auto color = isSubtle ? colorConfig.subtleColor : colorConfig.defaultColor;
            return QString::fromStdString(color);
        }
	}

     const int AdaptiveCardQmlEngine::AdaptiveCardContext::getContentIndex()
    {
        return m_ContentIndex;
    }

    void AdaptiveCardQmlEngine::AdaptiveCardContext::setContentIndex(int contentIndex)
    {
        m_ContentIndex = contentIndex;
    }

    void AdaptiveCardQmlEngine::AdaptiveCardContext::incrementContentIndex()
    {
        m_ContentIndex++;
    }
    void AdaptiveCardContext::addHeightEstimate(const int height)
    {
        m_HeightEstimate += height;
    }

    void AdaptiveCardContext::setHeightEstimate(const int height)
    {
        m_HeightEstimate = height;
    }

    const int AdaptiveCardContext::getHeightEstimate()
    {
        return m_HeightEstimate;
    }
    } // namespace AdaptiveCardQmlEngine

