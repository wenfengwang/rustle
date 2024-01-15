
## Division vor Multiplikation

### Konfiguration

* Detektor-ID: `div-before-mul`
* Schweregrad: mittel

### Beschreibung

Finden Sie Divisionen vor Multiplikationen wie `3 / 2 * 6 == 6`, was zu einem anderen Ergebnis führt als `3 * 6 / 2 == 9`. Dies kann zu einem Genauigkeitsverlust führen.

Es wird empfohlen, Multiplikationen vor Divisionen durchzuführen.

### Beispielcode

Unten sehen Sie ein Beispiel. Die Formel `farm.amount / (farm.end_date - farm.start_date) as u128` wird abgerundet und kann zu Präzisionsverlusten führen.

```rust
// https://github.com/linear-protocol/LiNEAR/blob/fdbacc68c98205cba9f42c130d464ab3114257b6/contracts/linear/src/farm.rs#L125
let reward_per_session =
    farm.amount / (farm.end_date - farm.start_date) as u128 * SESSION_INTERVAL as u128;
```

Es wird empfohlen, die Division nach der Multiplikation zu verwenden, um Präzisionsverluste zu vermeiden:

```rust
let reward_per_session =
    farm.amount * SESSION_INTERVAL as u128 / (farm.end_date - farm.start_date) as u128;
```
