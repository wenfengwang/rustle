
## Fehlen des `#[private]`-Makros in Rückruffunktionen

### Konfiguration

* Detektor-ID: `non-private-callback`
* Schweregrad: hoch

### Beschreibung

Die Rückruffunktion sollte mit dem `#[private]`-Makro dekoriert werden, um sicherzustellen, dass sie nur vom Vertrag selbst aufgerufen werden kann.

Ohne dieses Makro kann jeder die Rückruffunktion aufrufen, was gegen das ursprüngliche Design verstößt.

### Beispielcode

```rust
pub fn callback_stake(&mut self) { // dies ist eine Rückruffunktion
    // ...
}
```

Die Funktion `callback_stake` sollte mit `#[private]` dekoriert werden:

```rust
#[private]
pub fn callback_stake(&mut self) { // dies ist eine Rückruffunktion
    // ...
}
```

Mit diesem Makro kann nur der Vertrag selbst `callback_stake` aufrufen.
