#include "qsimplesignalaggregator.h"

#include <QMetaMethod>

QSimpleSignalAggregator::QSimpleSignalAggregator(QObject *parent) :
    QSignalAggregator(parent),
    triggerObject(this),
    triggerSignal(convertSignalIntoInvokableMethod(SIGNAL(done())))
{
}

auto QSimpleSignalAggregator::convertSignalIntoInvokableMethod(const char *signal)
    -> QString {
    // Index the char* to remove the "2" prefix added by SIGNAL()
    QString normalizedSignal = QString(signal+1);
    // Remove parentheses (subsequently added back by
    // QMetaObject::invokeMethod)
    normalizedSignal.chop(2);
    return normalizedSignal;
}

auto QSimpleSignalAggregator::reset() -> void {
    lookingFor = monitor;
    // lookingFor.detach();
}

auto QSimpleSignalAggregator::aggregate(const QObject *sender,
                                        const char *signal,
                                        const int occurrences) -> void {
    connect(sender, signal, this, SLOT(captureSignal()));

    QHash<const QString, int> senderHash = lookingFor.value(sender);
    senderHash.insert(signal, occurrences + lookingFor.value(sender).value(signal, 0));
    lookingFor.insert(sender, senderHash);

    QHash<const QString, int> monitorHash = monitor.value(sender);
    monitorHash.insert(signal, occurrences + monitor.value(sender).value(signal, 0));
    monitor.insert(sender, monitorHash);

    printStatus();
}

// TODO: document that only parametereless signals may be invoked
auto QSimpleSignalAggregator::gate(QObject *sender,
                                   const char *signal) -> void {
    triggerObject = sender;
    triggerSignal = convertSignalIntoInvokableMethod(signal);
}

auto QSimpleSignalAggregator::emitGatedSignal() -> void {
    QMetaObject::invokeMethod(triggerObject,
                              triggerSignal.toLocal8Bit().constData());
}

auto QSimpleSignalAggregator::captureSignal() -> void {
    const QObject *sender = QObject::sender();
    const QString signalSignature = sender
        ->metaObject()
        ->method(senderSignalIndex())
        .methodSignature();
    const QByteArray signalString = QString("2%1")
        .arg(signalSignature)
        .toLocal8Bit();
    const char *signal = signalString.constData();

    // qDebug() << "Caught" << signal << "signal from" << sender;

    QHash<const QString, int> senderHash = lookingFor.value(sender);
    const auto remaining = senderHash.value(signal) - 1;

    if (remaining == 0) {
        senderHash.remove(signal);
        // TODO: test that the disconnect works appropriately
        disconnect(sender, signal, this, SLOT(captureSignal()));
    } else {
        senderHash.insert(signal, remaining);
    }
    lookingFor.insert(sender, senderHash);

    checkAggregationStatus();
}

auto QSimpleSignalAggregator::checkAggregationStatus() -> void {
    // printStatus();
    foreach (const auto sender, lookingFor.keys()) {
        QHash<const QString, int> senderHash = lookingFor.value(sender);
        if (senderHash.size() == 0) {
            emitGatedSignal();
        }
    }
}
