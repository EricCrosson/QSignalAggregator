# QSignalAggregator

> Monitor multiple signals to aggregate them into one signal-based
> event.

## Usage

```bash
QSimpleSignalAggregator *aggie = new QSimpleSignalAggregator(this);
QObject::connect(aggie, SIGNAL(done()), this, SLOT(allSignalsInvoked()));
aggie->aggregate(voicemailProvider, SIGNAL(done()));
aggie->aggregate(wallpaperProvider, SIGNAL(done()));
```

As soon as `voicemailProvider::done()` *and*
`wallpaperProvider::done()` are emitted, `aggie::done()` is emitted.

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

### test

Build tests, placed in `build/test/bin`.

### doc

Build doxygen documentation, placed in `doc`.

## License

MIT © Eric Crosson
