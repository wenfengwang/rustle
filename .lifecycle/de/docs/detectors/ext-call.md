
## Vertragsübergreifende Aufrufe

### Konfiguration

* Detektor-ID: `ext-call`
* Schweregrad: info

### Beschreibung

Finden Sie alle vertragsübergreifenden Aufrufe.

Wir stellen diesen Detektor zur Verfügung, um Benutzern das schnelle Auffinden aller vertragsübergreifenden Aufrufe zur weiteren Analyse zu erleichtern.

### Beispielcode

```rust
// https://docs.near.org/sdk/rust/cross-contract/callbacks#calculator-example
#[ext_contract(ext_calculator)]
trait Calculator {
    fn sum(&self, a: U128, b: U128) -> U128;
}

#[near_bindgen]
impl Contract {
    pub fn sum_a_b(&mut self, a: U128, b: U128) -> Promise {
        let calculator_account_id: AccountId = "calc.near".parse().unwrap();
        ext_calculator::ext(calculator_account_id).sum(a, b)  // führe sum(a, b) auf entferntem Vertrag aus
    }
}
```

> Das Makro `#[ext_contract(...)]` konvertiert ein Rust-Trait in ein Modul mit statischen Methoden, das es Benutzern ermöglicht, vertragsübergreifende Aufrufe durchzuführen. Jede dieser statischen Methoden nimmt Positionsargumente an, die durch das Trait definiert sind, gefolgt von der `receiver_id`, dem angehängten Deposit und der Gasmenge und gibt ein neues `Promise` zurück.

In diesem Beispiel kann der Vertrag die Summe von `a` und `b` mit dem vertragsübergreifenden Aufruf erhalten (d. h. `ext_calculator::ext(calculator_account_id).sum(a, b)`).
