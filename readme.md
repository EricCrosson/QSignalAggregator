# QSignalAggregator

> Barrier for Qt signals.

## Usage

```bash
QSimpleSignalAggregator *aggregator = new QSimpleSignalAggregator(this);
QObject::connect(aggregator, SIGNAL(done()), this, SLOT(allSignalsInvoked()));
aggregator->aggregate(foo, SIGNAL(done()));
aggregator->aggregate(bar, SIGNAL(done()));
```

As soon as `foo::done()` *and* `bar::done()` are emitted,
`aggregator::done()` is emitted.

## API

### aggregate(sender, signal)

Add the sender's specified signal to the list of monitored signals.

### gate(sender, signal)

Emit the specified object's signal when all monitored signals have
been witnessed (rather than the default `done()` from the
`QSignalAggregator` object).

### reset()

Forget about witnessed signals and start monitoring for all
`aggregated` signals again.

## Make targets

### all

Compile into a static library, placed in `build/lib`.

### test

Build tests, placed in `build/test/bin`.

### doc

Build doxygen documentation, placed in `doc`.

## License

MIT © Eric Crosson
