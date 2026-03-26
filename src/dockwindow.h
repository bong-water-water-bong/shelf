#pragma once

#include <QQuickWindow>

class DockWindow
{
public:
    /// Configure a QQuickWindow as a Wayland Layer Shell dock surface.
    /// Anchors to bottom center, reserves exclusive zone, top layer.
    static void configureLayerShell(QQuickWindow *window, int exclusiveZone);
};
