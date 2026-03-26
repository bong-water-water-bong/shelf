#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include <KCrash>
#include <KLocalizedString>

#include <LayerShellQt/Window>

#include "dockwindow.h"
#include "parabolic.h"
#include "shelfconfig.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("shelf"));
    app.setApplicationDisplayName(QStringLiteral("shelf"));
    app.setOrganizationDomain(QStringLiteral("shelf"));
    app.setApplicationVersion(QStringLiteral("0.1.0"));
    app.setDesktopFileName(QStringLiteral("shelf"));

    KCrash::initialize();
    KLocalizedString::setApplicationDomain("shelf");

    ShelfConfig config;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QStringLiteral("shelfConfig"), &config);

    DockWindow dockWindow;
    engine.rootContext()->setContextProperty(QStringLiteral("dockWindow"), &dockWindow);

    // Configure Layer Shell on window creation, BEFORE it's shown
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [&config](QObject *obj, const QUrl &) {
            if (!obj) return;
            auto *window = qobject_cast<QQuickWindow *>(obj);
            if (!window) return;

            window->setColor(Qt::transparent);
            DockWindow::configureLayerShell(window, config.dockHeight());

            // Now show the window after Layer Shell is configured
            window->show();
        }, Qt::DirectConnection);

    engine.load(QUrl(QStringLiteral("qrc:/DockView.qml")));

    if (engine.rootObjects().isEmpty()) {
        qCritical() << "shelf: failed to load QML";
        return -1;
    }

    return app.exec();
}
