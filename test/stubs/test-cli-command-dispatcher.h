/* -*- mode: c++; -*- */

#include <QObject>

#include "icli-command-dispatcher.h"

class TestCliCommandDispatcher : public QObject,
                                 public ICliCommandDispatcher {
    Q_OBJECT
    Q_INTERFACES(ICliCommandDispatcher)

public:

    TestCliCommandDispatcher() { }
    ~TestCliCommandDispatcher() override { }

    const IExitCode *execute(QString command, QStringList args, QIODevice &stdout)
        override {
        Q_UNUSED(args);
        Q_UNUSED(stdout);
        if (QString::compare("pass", command)) {
            return ExitCode::success();
        } else {
            return ExitCode::newError();
        }
    }

    bool addCommand(ICliCommand *command) override {
        Q_UNUSED(command);
        return true;
    }

    int populatePath() override {
        return 0;
    }
    QStringList knownCommands() override {
        return QStringList();
    }
};
