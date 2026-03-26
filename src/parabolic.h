#pragma once

#include <QObject>
#include <QVector>
#include <QtQml/qqmlregistration.h>
#include <cmath>

/// C++ parabolic zoom calculator — eliminates JS overhead for smooth animation.
/// Call update() with mouse position, get per-icon scales back instantly.
class ParabolicCalc : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(qreal mouseX READ mouseX WRITE setMouseX NOTIFY mouseXChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(int iconCount READ iconCount WRITE setIconCount NOTIFY iconCountChanged)
    Q_PROPERTY(int cellWidth READ cellWidth WRITE setCellWidth NOTIFY cellWidthChanged)
    Q_PROPERTY(int rowX READ rowX WRITE setRowX NOTIFY rowXChanged)
    Q_PROPERTY(qreal maxZoom READ maxZoom WRITE setMaxZoom NOTIFY maxZoomChanged)
    Q_PROPERTY(int zoomRange READ zoomRange WRITE setZoomRange NOTIFY zoomRangeChanged)

public:
    explicit ParabolicCalc(QObject *parent = nullptr) : QObject(parent) {}

    qreal mouseX() const { return m_mouseX; }
    void setMouseX(qreal x) {
        if (!qFuzzyCompare(m_mouseX, x)) {
            m_mouseX = x;
            recalc();
            Q_EMIT mouseXChanged();
        }
    }

    bool active() const { return m_active; }
    void setActive(bool a) {
        if (m_active != a) {
            m_active = a;
            recalc();
            Q_EMIT activeChanged();
        }
    }

    int iconCount() const { return m_iconCount; }
    void setIconCount(int c) {
        if (m_iconCount != c) {
            m_iconCount = c;
            m_scales.resize(c, 1.0);
            recalc();
            Q_EMIT iconCountChanged();
        }
    }

    int cellWidth() const { return m_cellWidth; }
    void setCellWidth(int w) { if (m_cellWidth != w) { m_cellWidth = w; recalc(); Q_EMIT cellWidthChanged(); } }

    int rowX() const { return m_rowX; }
    void setRowX(int x) { if (m_rowX != x) { m_rowX = x; recalc(); Q_EMIT rowXChanged(); } }

    qreal maxZoom() const { return m_maxZoom; }
    void setMaxZoom(qreal z) { if (!qFuzzyCompare(m_maxZoom, z)) { m_maxZoom = z; recalc(); Q_EMIT maxZoomChanged(); } }

    int zoomRange() const { return m_zoomRange; }
    void setZoomRange(int r) { if (m_zoomRange != r) { m_zoomRange = r; recalc(); Q_EMIT zoomRangeChanged(); } }

    Q_INVOKABLE qreal scaleAt(int index) const {
        if (index < 0 || index >= m_scales.size()) return 1.0;
        return m_scales[index];
    }

Q_SIGNALS:
    void mouseXChanged();
    void activeChanged();
    void iconCountChanged();
    void cellWidthChanged();
    void rowXChanged();
    void maxZoomChanged();
    void zoomRangeChanged();
    void scalesChanged();

private:
    void recalc() {
        if (m_cellWidth <= 0 || m_iconCount <= 0) return;

        bool changed = false;
        for (int i = 0; i < m_iconCount; ++i) {
            qreal center = i * m_cellWidth + m_cellWidth * 0.5;
            qreal newScale = 1.0;

            if (m_active) {
                qreal dist = std::abs(m_mouseX - center);
                if (dist < m_zoomRange) {
                    newScale = 1.0 + (m_maxZoom - 1.0) * 0.5
                               * (1.0 + std::cos(M_PI * dist / m_zoomRange));
                }
            }

            if (!qFuzzyCompare(m_scales[i], newScale)) {
                m_scales[i] = newScale;
                changed = true;
            }
        }

        if (changed) {
            Q_EMIT scalesChanged();
        }
    }

    qreal m_mouseX = -10000;
    bool m_active = false;
    int m_iconCount = 0;
    int m_cellWidth = 50;
    int m_rowX = 0;
    qreal m_maxZoom = 2.2;
    int m_zoomRange = 65;
    QVector<qreal> m_scales;
};
