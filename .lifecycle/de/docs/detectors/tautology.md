
## Verwendung von Tautologie in Verzweigungsbedingungen

### Konfiguration

* Detektor-ID: `tautology`
* Schweregrad: niedrig

### Beschreibung

Finden Sie einfache Tautologien (`true` oder `false` in der Bedingung), die einen Zweig deterministisch machen.

### Beispielcode

```rust
let ok: bool = check_state();
if true || ok {
    // ...
} else {
    // ...
}
```

In diesem Beispiel wird der Code im `else`-Zweig niemals ausgeführt. Der Grund dafür ist, dass `true || ok` eine Tautologie ist.
