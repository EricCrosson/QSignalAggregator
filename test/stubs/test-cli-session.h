/* -*- mode: c++; -*- */

#include <QObject>
#include <QtNetwork/QLocalSocket>

#include "icli-session.h"

class TestCliSession : public ICliSession {
    Q_OBJECT

public:
    TestCliSession(QObject *parent,
                   QLocalSocket *localsocket) :
        ICliSession(parent), localsocket(new QLocalSocket(this))
        {
            Q_UNUSED(localsocket);
        }

    void displayMOTD() override { }

    void displayPrompt(const IExitCode *exitCode) override {
        Q_UNUSED(exitCode);
    }

public slots:
    void dispatchCommand() override { }

    const IExitCode *dispatchCommand(QString command, QStringList args) override {
        Q_UNUSED(command);
        Q_UNUSED(args);
        return ExitCode::success();
    }

public:
    QLocalSocket *localsocket;
};
