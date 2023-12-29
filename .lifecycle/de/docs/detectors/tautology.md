
## Verwendung von Tautologie in Verzweigungsbedingungen

### Konfiguration

* Detektor-ID: `tautology`
* Schweregrad: niedrig

### Beschreibung

Finden Sie eine einfache Tautologie (`true` oder `false` in der Bedingung), die einen Zweig deterministisch macht.

### Beispielcode

```rust
let ok: bool = check_state();
if true || ok {
    // ...
} else {
    // ...
}
```

In diesem Beispiel wird der Code im `else`-Zweig niemals ausgeführt. Dies liegt daran, dass `true || ok` eine Tautologie ist.
