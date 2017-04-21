#include <QtTest/QtTest>

#include "qsimplesignalaggregator.h"

class TestQSimpleSignalAggregator : public QObject {
    Q_OBJECT

public:
    TestQSimpleSignalAggregator() { }

signals:
    void trigger();

    void dummySignal1();
    void dummySignal2();
    void dummySignal3(int);

private slots:
    void init();
    void cleanup();

    /**
     * Test QSimpleSignalAggregator
     */
    void aggregateOneSignal();
    void aggregatedSignalShouldNotFireMultipleTimesWithMultipleStimuliWithoutReset();
    void resetShouldAllowAggregatorToFireMultipleTimesWithMultipleStimuli();
    void resetClearsPreviouslyWitnessedSignals();
    void clientCodeIsReadable();
    void canAggregateSignalsWithParameters();
    void canGateCustomSignal();
    // void canGateSignalsWithParameters();
    void testClientCodeWithoutPointer();
    void testSuperfluousSignalsAreIgnored();

private:
    QSimpleSignalAggregator *aggie;
    QSignalSpy *spyTriggered;
};


void TestQSimpleSignalAggregator::init() {
    aggie = new QSimpleSignalAggregator(this);
    spyTriggered = new QSignalSpy(aggie, SIGNAL(done()));
}

void TestQSimpleSignalAggregator::cleanup() {
    delete spyTriggered;
    delete aggie;
}

void TestQSimpleSignalAggregator::testSuperfluousSignalsAreIgnored() {
    QCOMPARE(spyTriggered->count(), 0);
    aggie->aggregate(this, SIGNAL(dummySignal1()));
    aggie->aggregate(this, SIGNAL(dummySignal2()));
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 0);
    emit dummySignal1();
    emit dummySignal1();
    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 0);
    emit dummySignal2();
    QCOMPARE(spyTriggered->count(), 1);
}

void TestQSimpleSignalAggregator::testClientCodeWithoutPointer() {
    QCOMPARE(spyTriggered->count(), 0);
    QSimpleSignalAggregator aggregator(this);
    delete spyTriggered;
    spyTriggered = new QSignalSpy(&aggregator, SIGNAL(done()));
    aggregator.aggregate(this, SIGNAL(dummySignal1()));
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 1);
}

void TestQSimpleSignalAggregator::canAggregateSignalsWithParameters() {
    QCOMPARE(spyTriggered->count(), 0);
    aggie->aggregate(this, SIGNAL(dummySignal1()));
    aggie->aggregate(this, SIGNAL(dummySignal3(int)));
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal3(42);
    QCOMPARE(spyTriggered->count(), 1);
}

void TestQSimpleSignalAggregator::resetShouldAllowAggregatorToFireMultipleTimesWithMultipleStimuli() {
    QCOMPARE(spyTriggered->count(), 0);
    aggie->aggregate(this, SIGNAL(dummySignal1()));
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 1);

    aggie->reset();
    QCOMPARE(spyTriggered->count(), 1);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 2);
}

void TestQSimpleSignalAggregator::aggregatedSignalShouldNotFireMultipleTimesWithMultipleStimuliWithoutReset() {
    QCOMPARE(spyTriggered->count(), 0);
    aggie->aggregate(this, SIGNAL(dummySignal1()));
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 1);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 1);
}

void TestQSimpleSignalAggregator::aggregateOneSignal() {
    QCOMPARE(spyTriggered->count(), 0);
    aggie->aggregate(this, SIGNAL(dummySignal1()));
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 1);
}

void TestQSimpleSignalAggregator::clientCodeIsReadable() {
    QCOMPARE(spyTriggered->count(), 0);
    aggie->aggregate(this, SIGNAL(dummySignal1()));
    aggie->aggregate(this, SIGNAL(dummySignal2()));
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal2();
    QCOMPARE(spyTriggered->count(), 1);
}

void TestQSimpleSignalAggregator::resetClearsPreviouslyWitnessedSignals() {
    QCOMPARE(spyTriggered->count(), 0);
    aggie->aggregate(this, SIGNAL(dummySignal1()));
    aggie->aggregate(this, SIGNAL(dummySignal2()));
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 0);

    aggie->reset();

    emit dummySignal2();
    QCOMPARE(spyTriggered->count(), 0);

    aggie->reset();
    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 0);
    emit dummySignal2();
    QCOMPARE(spyTriggered->count(), 1);
}

void TestQSimpleSignalAggregator::canGateCustomSignal() {
    delete spyTriggered;
    spyTriggered = new QSignalSpy(this, SIGNAL(trigger()));

    QCOMPARE(spyTriggered->count(), 0);
    aggie->gate(this, SIGNAL(trigger()));
    aggie->aggregate(this, SIGNAL(dummySignal1()));
    aggie->aggregate(this, SIGNAL(dummySignal2()));
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal1();
    QCOMPARE(spyTriggered->count(), 0);

    emit dummySignal2();
    QCOMPARE(spyTriggered->count(), 1);
}

QTEST_MAIN(TestQSimpleSignalAggregator)
#include "test-qsimplesignalaggregator.moc"
