
## Inkonsistente Symbole

### Konfiguration

* Detektor-ID: `inconsistency`
* Schweregrad: info

### Beschreibung

Symbole mit ähnlichen, aber leicht unterschiedlichen Namen können fälschlicherweise verwendet werden. Ein solcher Fehler ist manuell schwer zu erkennen, kann jedoch zu kritischen Ergebnissen führen.

### Beispielcode

```rust
ext::ft_transfer(
    receiver_id,
    U128(amount),
    None,
    token_id,
    1,
    GAS_FOR_NFT_TRANSFER  // hier sollte GAS_FOR_FT_TRANSFER verwendet werden
)
```

In diesem Beispiel sollte der Vertrag `GAS_FOR_FT_TRANSFER` statt `GAS_FOR_NFT_TRANSFER` verwenden. Diese beiden Konstanten können stark im Wert variieren, und das Gas für den `ft_transfer` könnte unzureichend sein.
