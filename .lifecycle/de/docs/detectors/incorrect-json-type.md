
## Verwendung eines falschen JSON-Typs

### Konfiguration

* Detektor-ID: `incorrect-json-type`
* Schweregrad: hoch

### Beschreibung

Verwenden Sie nicht die Typen `i64`, `i128`, `u64` oder `u128` als Parameter oder Rückgabewerte öffentlicher Schnittstellen (öffentliche Funktionen ohne `#[private]`-Makro in einer `#[near_bindgen]`-Struktur).

Der Grund dafür ist, dass die größte Ganzzahl, die JSON unterstützen kann, 2\^53-1 beträgt.

Weitere Details finden Sie unter https://2ality.com/2012/04/number-encoding.html.

Die Typen `I64`, `I128`, `U64` und `U128` im Near SDK werden für Entwickler empfohlen.

### Beispielcode

```rust
// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/views.rs#L15
pub struct ContractMetadata {
    pub version: String,
    pub owner: AccountId,
    pub guardians: Vec<AccountId>,
    pub pool_count: u64,  // sollte `U64` verwenden
    pub state: RunningState,
    pub exchange_fee: u32,
    pub referral_fee: u32,
}

// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/views.rs#L171
#[near_bindgen]
impl Contract {
    pub fn metadata(&self) -> ContractMetadata {  // `u64` im Rückgabetyp
        // ...
    }
}
```

In diesem Beispiel verwendet die `metadata`-Funktion die Struktur `ContractMetadata`, welche `pool_count: u64` in ihrem Rückgabewert enthält. Da Rückgabewerte öffentlicher Funktionen mithilfe von JSON an das Frontend gesendet werden und der Wert von `pool_count` 2\^53-1 überschreiten kann, sollte stattdessen der String-Typ `U64` aus dem Near SDK verwendet werden.
