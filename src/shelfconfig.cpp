#include "shelfconfig.h"

#include <QProcess>
#include <KConfig>
#include <KConfigGroup>
#include <KSharedConfig>

static const auto CONFIG_FILE = QStringLiteral("shelfrc");

ShelfConfig::ShelfConfig(QObject *parent)
    : QObject(parent)
{
    load();
}

void ShelfConfig::load()
{
    auto config = KSharedConfig::openConfig(CONFIG_FILE);
    KConfigGroup general = config->group(QStringLiteral("General"));

    m_iconSize = general.readEntry("IconSize", 40);
    m_maxZoom = general.readEntry("MaxZoom", 2.2);
    m_zoomRange = general.readEntry("ZoomRange", 65);
    m_iconSpacing = general.readEntry("IconSpacing", 10);
    m_pinnedLaunchers = general.readEntry("PinnedLaunchers", QStringList{
        QStringLiteral("applications:org.kde.dolphin.desktop"),
        QStringLiteral("preferred://browser"),
        QStringLiteral("applications:org.kde.konsole.desktop"),
    });
}

void ShelfConfig::save()
{
    auto config = KSharedConfig::openConfig(CONFIG_FILE);
    KConfigGroup general = config->group(QStringLiteral("General"));

    general.writeEntry("IconSize", m_iconSize);
    general.writeEntry("MaxZoom", m_maxZoom);
    general.writeEntry("ZoomRange", m_zoomRange);
    general.writeEntry("IconSpacing", m_iconSpacing);
    general.writeEntry("PinnedLaunchers", m_pinnedLaunchers);

    config->sync();
}

void ShelfConfig::setIconSize(int size)
{
    if (m_iconSize != size) {
        m_iconSize = size;
        save();
        Q_EMIT iconSizeChanged();
        Q_EMIT dockHeightChanged();
    }
}

void ShelfConfig::setMaxZoom(qreal zoom)
{
    if (!qFuzzyCompare(m_maxZoom, zoom)) {
        m_maxZoom = zoom;
        save();
        Q_EMIT maxZoomChanged();
        Q_EMIT dockHeightChanged();
    }
}

void ShelfConfig::setZoomRange(int range)
{
    if (m_zoomRange != range) {
        m_zoomRange = range;
        save();
        Q_EMIT zoomRangeChanged();
    }
}

void ShelfConfig::setIconSpacing(int spacing)
{
    if (m_iconSpacing != spacing) {
        m_iconSpacing = spacing;
        save();
        Q_EMIT iconSpacingChanged();
    }
}

int ShelfConfig::dockHeight() const
{
    return static_cast<int>(m_iconSize * m_maxZoom) + 24;
}

void ShelfConfig::setPinnedLaunchers(const QStringList &launchers)
{
    if (m_pinnedLaunchers != launchers) {
        m_pinnedLaunchers = launchers;
        save();
        Q_EMIT pinnedLaunchersChanged();
    }
}

void ShelfConfig::launch(const QString &command)
{
    auto parts = command.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    if (parts.isEmpty()) return;
    auto program = parts.takeFirst();
    QProcess::startDetached(program, parts);
}
