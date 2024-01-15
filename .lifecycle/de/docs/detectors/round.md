
## Unzulässige Rundung ohne Angabe von `ceil` oder `floor`

### Konfiguration

* Detektor-ID: `round`
* Schweregrad: mittel

### Beschreibung

Es wird überprüft, ob bei arithmetischen Operationen Rundungen verwendet werden. Rundungen ohne Richtungsangabe können im DeFi-Bereich ausgenutzt werden. Weitere Details finden Sie unter [Wie man Millionär wird, 0,000001 BTC auf einmal (neodyme.io)](https://blog.neodyme.io/posts/lending_disclosure/).

Hinweis: **Rustle** wird keine Rundungsfunktionen melden, die von Entwicklern für spezifische Zwecke implementiert wurden.

### Beispielcode

```rust
let fee = (amount * fee_rate).round();
```

In diesem Beispiel sollten Vertragsentwickler nicht `round` zur Berechnung der Gebühr verwenden. Sie sollten stattdessen `ceil` oder `floor` nutzen, um die Rundungsrichtung festzulegen.
