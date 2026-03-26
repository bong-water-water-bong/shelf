#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include <KCrash>
#include <KLocalizedString>

#include "dockwindow.h"
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

    engine.load(QUrl(QStringLiteral("qrc:/DockView.qml")));

    if (engine.rootObjects().isEmpty()) {
        qCritical() << "shelf: failed to load QML";
        return -1;
    }

    auto *window = qobject_cast<QQuickWindow *>(engine.rootObjects().first());
    if (window) {
        DockWindow::configureLayerShell(window, config.dockHeight());
        window->setColor(Qt::transparent);
    }

    return app.exec();
}
