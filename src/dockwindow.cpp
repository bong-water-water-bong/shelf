#include "dockwindow.h"

#include <LayerShellQt/Window>

void DockWindow::configureLayerShell(QQuickWindow *window, int exclusiveZone)
{
    auto *layerWindow = LayerShellQt::Window::get(window);
    if (!layerWindow) {
        qWarning() << "shelf: failed to get Layer Shell window — is this Wayland?";
        return;
    }

    layerWindow->setLayer(LayerShellQt::Window::LayerTop);
    layerWindow->setAnchors(LayerShellQt::Window::Anchors(
        LayerShellQt::Window::AnchorBottom
        | LayerShellQt::Window::AnchorLeft
        | LayerShellQt::Window::AnchorRight));
    layerWindow->setExclusiveZone(exclusiveZone);
    layerWindow->setKeyboardInteractivity(
        LayerShellQt::Window::KeyboardInteractivityNone);
    layerWindow->setMargins(QMargins(0, 0, 0, 0));
}

void DockWindow::setExclusiveZone(QQuickWindow *window, int zone)
{
    auto *layerWindow = LayerShellQt::Window::get(window);
    if (layerWindow) {
        layerWindow->setExclusiveZone(zone);
    }
}
