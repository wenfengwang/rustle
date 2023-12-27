
## Unkorrekte Rundung ohne Angabe von `ceil` oder `floor`

### Konfiguration

* Detektor-ID: `round`
* Schweregrad: mittel

### Beschreibung

Es wird überprüft, ob bei arithmetischen Operationen Rundungen verwendet werden. Rundungen ohne Richtungsangabe können im DeFi-Bereich ausgenutzt werden. Siehe [How to Become a Millionaire, 0.000001 BTC at a Time (neodyme.io)](https://blog.neodyme.io/posts/lending_disclosure/) für weitere Details.

Hinweis: **Rustle** wird keine Rundungsfunktionen melden, die von Entwicklern für spezifische Zwecke implementiert wurden.

### Beispielcode

```rust
let fee = (amount * fee_rate).round();
```

In diesem Beispiel sollten Vertragsentwickler nicht `round` zur Berechnung der Gebühr verwenden. Sie sollten stattdessen `ceil` oder `floor` verwenden, um die Rundungsrichtung festzulegen.
