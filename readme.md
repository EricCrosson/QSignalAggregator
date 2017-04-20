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
`QSignalAggregator` object.

## License

MIT © Eric Crosson
