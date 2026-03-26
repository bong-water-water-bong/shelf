#include "dockwindow.h"

#include <LayerShellQt/Window>

void DockWindow::configureLayerShell(QQuickWindow *window, int exclusiveZone)
{
    auto *layerWindow = LayerShellQt::Window::get(window);
    if (!layerWindow) {
        qWarning() << "shelf: failed to get Layer Shell window — is this Wayland?";
        return;
    }

    // Dock behavior: bottom edge, top layer, reserve screen space
    layerWindow->setLayer(LayerShellQt::Window::LayerTop);
    layerWindow->setAnchors(LayerShellQt::Window::AnchorBottom);
    layerWindow->setExclusiveZone(exclusiveZone);
    layerWindow->setKeyboardInteractivity(
        LayerShellQt::Window::KeyboardInteractivityNone);

    // Let the dock size itself — no fixed margins
    layerWindow->setMargins(QMargins(0, 0, 0, 0));
}
