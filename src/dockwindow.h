#pragma once

#include <QQuickWindow>

class DockWindow : public QObject
{
    Q_OBJECT
public:
    explicit DockWindow(QObject *parent = nullptr) : QObject(parent) {}

    static void configureLayerShell(QQuickWindow *window, int exclusiveZone);

    Q_INVOKABLE static void setExclusiveZone(QQuickWindow *window, int zone);
};
