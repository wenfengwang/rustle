
## Promise-Ergebnis

### Konfiguration

* Detektor-ID: `promise-result`
* Schweregrad: info

### Beschreibung

Finden Sie alle Verwendungen von `env::promise_result`, welches das Ergebnis der Promise-Ausführung liefert.

Dieser Detektor hilft dabei, die Logik der Verarbeitung von Promise-Ergebnissen schnell zu lokalisieren.

### Beispielcode

```rust
// https://github.com/ref-finance/ref-contracts/blob/b33c3a488b18f9cff82a3fdd53bf65d6aac09e15/ref-exchange/src/lib.rs#L434
let cross_call_result = match env::promise_result(0) {
    PromiseResult::Successful(result) => result,
    _ => env::panic(ERR124_CROSS_CALL_FAILED.as_bytes()),
};
```

In diesem Beispiel wird das Promise-Ergebnis je nach seinem Zustand (erfolgreich oder nicht) behandelt.
