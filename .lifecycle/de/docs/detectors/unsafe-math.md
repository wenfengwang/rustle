
## Unsichere Mathematik ohne Überlaufprüfung

### Konfiguration

* Detektor-ID: `unsafe-math`
* Schweregrad: hoch

### Beschreibung

Aktivieren Sie Überlaufprüfungen für alle arithmetischen Operationen. Andernfalls kann es zu einem Überlauf kommen, der zu falschen Ergebnissen führt.

Überlaufprüfungen in NEAR-Verträgen können mit zwei verschiedenen Methoden implementiert werden.

1. \[Empfohlen\] Schalten Sie die `overflow-checks` im Cargo-Manifest ein. In diesem Fall ist es in Ordnung, `+`, `-` und `*` für arithmetische Operationen zu verwenden.
2. Verwenden Sie sichere mathematische Funktionen (z. B. `checked_xxx()`) für arithmetische Operationen.

### Beispielcode

In diesem Beispiel ist das `overflow-checks`-Flag im Cargo-Manifest deaktiviert, daher kann die Verwendung von `+` zu einem Überlauf führen.

```toml
[profile.xxx]  # `xxx` entspricht `dev` oder `release`
overflow-checks = false
```

```rust
let a = b + c;
```

Der folgende Code wird empfohlen, um die Additionsoperation mit `overflow-checks=false` durchzuführen

```rust
let a = b.checked_add(c);
```
