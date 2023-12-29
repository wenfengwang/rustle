
## Unangemessene Verwendung von `#[private]` in Nicht-Callback-Funktionen

### Konfiguration

* Detektor-ID: `non-callback-private`
* Schweregrad: niedrig

### Beschreibung

Das Makro `#[private]` wird üblicherweise in Callback-Funktionen verwendet, um sicherzustellen, dass `current_account_id` gleich `predecessor_account_id` ist. Es sollte nicht in Nicht-Callback-Funktionen verwendet werden. Andernfalls würde eine öffentliche Funktion zu einer internen.

### Beispielcode

```rust
#[near_bindgen]
impl Pool {
    #[private]
    pub fn get_tokens(&self) -> &[AccountId] {
        &self.token_account_ids
    }
}
```

`get_tokens` sollte eine öffentliche Schnittstelle sein (eine öffentliche Funktion ohne das `#[private]`-Makro), damit jeder alle Token-Arten in einem Pool einsehen kann. Sie sollte nicht mit `#[private]` dekoriert werden.
