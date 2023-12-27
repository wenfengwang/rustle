
## Unbehandeltes Promise-Ergebnis

### Konfiguration

* Detektor-ID: `unhandled-promise`
* Schweregrad: hoch

### Beschreibung

Promise-Ergebnisse sollten immer von einer Callback-Funktion oder einem weiteren Promise verarbeitet werden. Es wird nicht empfohlen, Promises in Verträgen unbehandelt zu lassen. Andernfalls kann der geänderte Zustand nicht zurückgesetzt werden, wenn das Promise fehlschlägt.

### Beispielcode

```rust
token.ft_transfer_call(receiver, U128(amount), None, "".to_string());
```

In diesem Beispiel ruft der Vertrag `ft_transfer_call` auf, behandelt jedoch das Ergebnis des Promises nicht mit einer spezifizierten Callback-Funktion (z.B. `resolve_transfer`). Daher weiß der Vertrag nicht, ob die Übertragung erfolgreich war. Und wenn die Übertragung fehlschlägt, werden die Vertragszustände nicht zurückgesetzt.
