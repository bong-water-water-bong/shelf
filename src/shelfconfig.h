#pragma once

#include <QObject>
#include <QStringList>

/// Shelf configuration — exposed to QML as shelfConfig
class ShelfConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
    Q_PROPERTY(qreal maxZoom READ maxZoom WRITE setMaxZoom NOTIFY maxZoomChanged)
    Q_PROPERTY(int zoomRange READ zoomRange WRITE setZoomRange NOTIFY zoomRangeChanged)
    Q_PROPERTY(int iconSpacing READ iconSpacing WRITE setIconSpacing NOTIFY iconSpacingChanged)
    Q_PROPERTY(int dockHeight READ dockHeight NOTIFY dockHeightChanged)
    Q_PROPERTY(QStringList pinnedLaunchers READ pinnedLaunchers WRITE setPinnedLaunchers NOTIFY pinnedLaunchersChanged)

public:
    explicit ShelfConfig(QObject *parent = nullptr);

    int iconSize() const { return m_iconSize; }
    void setIconSize(int size);

    qreal maxZoom() const { return m_maxZoom; }
    void setMaxZoom(qreal zoom);

    int zoomRange() const { return m_zoomRange; }
    void setZoomRange(int range);

    int iconSpacing() const { return m_iconSpacing; }
    void setIconSpacing(int spacing);

    int dockHeight() const;

    QStringList pinnedLaunchers() const { return m_pinnedLaunchers; }
    void setPinnedLaunchers(const QStringList &launchers);

Q_SIGNALS:
    void iconSizeChanged();
    void maxZoomChanged();
    void zoomRangeChanged();
    void iconSpacingChanged();
    void dockHeightChanged();
    void pinnedLaunchersChanged();

private:
    void load();
    void save();

    int m_iconSize = 48;
    qreal m_maxZoom = 1.8;
    int m_zoomRange = 150;
    int m_iconSpacing = 6;
    QStringList m_pinnedLaunchers;
};
