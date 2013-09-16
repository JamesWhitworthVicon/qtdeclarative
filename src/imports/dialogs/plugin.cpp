/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtQuick.Dialogs module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlextensionplugin.h>
#include "qquickfiledialog_p.h"
#include "qquickabstractfiledialog_p.h"
#include "qquickplatformfiledialog_p.h"
#include "qquickcolordialog_p.h"
#include "qquickabstractcolordialog_p.h"
#include "qquickplatformcolordialog_p.h"
#include <private/qguiapplication_p.h>
#include <qpa/qplatformintegration.h>

//#define PURE_QML_ONLY

QT_BEGIN_NAMESPACE

/*!
    \qmlmodule QtQuick.Dialogs 1
    \title Qt Quick Dialogs QML Types
    \ingroup qmlmodules
    \brief Provides QML types for standard file, color picker and message dialogs

    This QML module contains types for creating and interacting with system dialogs.

    To use the types in this module, import the module with the following line:

    \code
    import QtQuick.Dialogs 1.0
    \endcode
*/

class QtQuick2DialogsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")

public:
    QtQuick2DialogsPlugin() : QQmlExtensionPlugin() { }

    virtual void initializeEngine(QQmlEngine *engine, const char * /*uri*/) {
        //qDebug() << Q_FUNC_INFO << uri << m_decorationComponentUrl;
        QQuickAbstractDialog::m_decorationComponent =
            new QQmlComponent(engine, m_decorationComponentUrl, QQmlComponent::Asynchronous);
    }

    virtual void registerTypes(const char *uri) {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtQuick.Dialogs"));
        bool hasTopLevelWindows = QGuiApplicationPrivate::platformIntegration()->
            hasCapability(QPlatformIntegration::MultipleWindows);
        QDir qmlDir(baseUrl().toLocalFile());
        m_decorationComponentUrl = QUrl::fromLocalFile(qmlDir.filePath(QString("qml/DefaultWindowDecoration.qml")));
        QDir widgetsDir(baseUrl().toLocalFile());
        // TODO: find the directory by searching rather than assuming a relative path
        widgetsDir.cd("../PrivateWidgets");

        // Prefer the QPA dialog helpers if the platform supports them.
        // Else if there is a QWidget-based implementation, check whether it's
        // possible to instantiate it from Qt Quick.
        // Otherwise fall back to a pure-QML implementation.

        // FileDialog
#ifndef PURE_QML_ONLY
        if (QGuiApplicationPrivate::platformTheme()->usePlatformNativeDialog(QPlatformTheme::FileDialog))
            qmlRegisterType<QQuickPlatformFileDialog>(uri, 1, 0, "FileDialog");
        else
#endif
            registerWidgetOrQmlImplementation<QQuickFileDialog>(widgetsDir, qmlDir, "FileDialog", uri, hasTopLevelWindows, 1, 0);

        // ColorDialog
#ifndef PURE_QML_ONLY
        if (QGuiApplicationPrivate::platformTheme()->usePlatformNativeDialog(QPlatformTheme::ColorDialog))
            qmlRegisterType<QQuickPlatformColorDialog>(uri, 1, 0, "ColorDialog");
        else
#endif
            registerWidgetOrQmlImplementation<QQuickColorDialog>(widgetsDir, qmlDir, "ColorDialog", uri, hasTopLevelWindows, 1, 0);
    }

protected:
    template <class WrapperType>
    void registerWidgetOrQmlImplementation(QDir widgetsDir, QDir qmlDir,
            const char *qmlName, const char *uri, bool hasTopLevelWindows, int versionMajor, int versionMinor) {
        //qDebug() << Q_FUNC_INFO << qmlDir << qmlName << uri;
        bool needQml = true;

#ifdef PURE_QML_ONLY
        Q_UNUSED(widgetsDir)
        Q_UNUSED(hasTopLevelWindows)
#else
        // If there is a qmldir and we have a QApplication instance (as opposed to a
        // widget-free QGuiApplication), assume that the widget-based dialog will work.
        if (hasTopLevelWindows && widgetsDir.exists("qmldir") &&
                !qstrcmp(QCoreApplication::instance()->metaObject()->className(), "QApplication")) {
            QString dialogQmlPath = qmlDir.filePath(QString("Widget%1.qml").arg(qmlName));
            if (qmlRegisterType(QUrl::fromLocalFile(dialogQmlPath), uri, versionMajor, versionMinor, qmlName) >= 0)
                needQml = false;
            // qDebug() << "registering" << qmlName << " as " << dialogQmlPath << "success?" << !needQml;
        }
#endif
        if (needQml) {
            QByteArray abstractTypeName = QByteArray("Abstract") + qmlName;
            qmlRegisterType<WrapperType>(uri, versionMajor, versionMinor, abstractTypeName); // implementation wrapper
            QString dialogQmlPath = qmlDir.filePath(QString("Default%1.qml").arg(qmlName));
            // qDebug() << "registering" << qmlName << " as " << dialogQmlPath << "success?" <<
            qmlRegisterType(QUrl::fromLocalFile(dialogQmlPath), uri, versionMajor, versionMinor, qmlName);
        }
    }

    QUrl m_decorationComponentUrl;
};

QT_END_NAMESPACE

#include "plugin.moc"
