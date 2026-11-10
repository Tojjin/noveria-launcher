#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

#include <cstddef>
#include <string>
#include <string_view>

#include <toml++/toml.hpp>

#include "theme.h"

namespace {

template <typename T>
T readValue(const toml::table& config, std::string_view section, std::string_view key, T fallback) {

    if (const auto* sectionTable = config[section].as_table()) {
        if (const auto value = (*sectionTable)[key].value<T>()) {
            return *value;
        }
    }

    return fallback;
}

int readInt(const toml::table& config, std::string_view section, std::string_view key, int fallback, int minimum) {

    const int value = readValue<int>(config, section, key, fallback);

    if (value < minimum) {
        qWarning() << "Invalid theme value"
                   << QString::fromLatin1(section.data(), static_cast<int>(section.size()))
                   << QString::fromLatin1(key.data(), static_cast<int>(key.size()))
                   << "=" << value << "- using" << fallback;
        return fallback;
    }

    return value;
}

QColor readColor(const toml::table& config, std::string_view section, std::string_view key, const QColor& fallback) {

    const std::string value = readValue<std::string>(config, section, key, {});

    if (value.empty()) {
        return fallback;
    }

    const QColor color{QString::fromStdString(value)};

    if (!color.isValid()) {
        qWarning() << "Invalid theme color:" << QString::fromStdString(value)
                   << "- using" << fallback.name(QColor::HexArgb);
        return fallback;
    }

    return color;
}

}

Theme::Theme(QObject* parent) : QObject(parent) {
    loadConfig();
}

void Theme::loadConfig() {

    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

    if (configDir.isEmpty()) {
        configDir = QDir::homePath() + QStringLiteral("/.config/noveria-launcher");
    }

    const QString path = configDir + QStringLiteral("/config.toml");

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) {
        qInfo() << "Theme config not found, using defaults:" << path;
        return;
    }

    const QByteArray data = file.readAll();

    if (data.isEmpty()) {
        qWarning() << "Theme config is empty:" << path;
        return;
    }

    try {
        const toml::table config = toml::parse(
            std::string_view(data.constData(), static_cast<std::size_t>(data.size())),
            path.toStdString());

        m_launcherWidth = readInt(config, "launcher", "width", m_launcherWidth, 1);
        m_launcherHeight = readInt(config, "launcher", "height", m_launcherHeight, 1);
        m_launcherRadius = readInt(config, "launcher", "radius", m_launcherRadius, 0);
        m_launcherBorderWidth = readInt(config, "launcher", "border_width", m_launcherBorderWidth, 0);

        m_background = readColor(config, "colors", "background", m_background);
        m_launcherBorder = readColor(config, "colors", "border", m_launcherBorder);
        m_fieldBackground = readColor(config, "colors", "field_background", m_fieldBackground);
        m_fieldBorder = readColor(config, "colors", "field_border", m_fieldBorder);
        m_text = readColor(config, "colors", "text", m_text);
        m_textMuted = readColor(config, "colors", "text_muted", m_textMuted);
        m_textSelected = readColor(config, "colors", "text_selected", m_textSelected);
        m_accent = readColor(config, "colors", "accent", m_accent);
        m_scrollBar = readColor(config, "colors", "scrollbar", m_scrollBar);

        const QString fontFamily = QString::fromStdString(
            readValue<std::string>(config, "fonts", "family", m_fontFamily.toStdString()));

        if (!fontFamily.trimmed().isEmpty()) {
            m_fontFamily = fontFamily;
        }

        m_searchFontSize = readInt(config, "fonts", "search_size", m_searchFontSize, 1);
        m_appsNameFontSize = readInt(config, "fonts", "app_name_size", m_appsNameFontSize, 1);
        m_appsCommentFontSize = readInt(config, "fonts", "app_comment_size", m_appsCommentFontSize, 1);

        m_radius = readInt(config, "layout", "radius", m_radius, 0);
        m_spacing = readInt(config, "layout", "spacing", m_spacing, 0);
        m_textFieldBorderWidth = readInt(config, "layout", "text_field_border_width", m_textFieldBorderWidth, 0);
        m_searchFieldHeight = readInt(config, "layout", "search_field_height", m_searchFieldHeight, 1);
        m_searchFieldPadding = readInt(config, "layout", "search_field_padding", m_searchFieldPadding, 0);
        m_listSpacing = readInt(config, "layout", "list_spacing", m_listSpacing, 0);
        m_itemHeight = readInt(config, "layout", "item_height", m_itemHeight, 1);
        m_scrollBarWidth = readInt(config, "layout", "scrollbar_width", m_scrollBarWidth, 1);
        m_scrollBarStaticWidth = readInt(config, "layout", "scrollbar_static_width", m_scrollBarStaticWidth, 0);
        m_iconSize = readInt(config, "layout", "icon_size", m_iconSize, 1);
        m_iconSourceSize = readInt(config, "layout", "icon_source_size", m_iconSourceSize, 1);

        qInfo() << "Loaded theme config:" << path;
    }
    catch (const toml::parse_error& error) {
        qWarning() << "Failed to parse theme config:" << path << "-" << error.what();
    }
}