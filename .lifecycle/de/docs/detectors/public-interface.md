
## Finden Sie alle öffentlichen Schnittstellen

### Konfiguration

* Detektor-ID: `public-interface`
* Schweregrad: info

### Beschreibung

Öffentliche Schnittstellen sind Funktionen, die von anderen aufgerufen werden können. Speziell sind es öffentliche Funktionen ohne das `#[private]`-Makro einer `#[near_bindgen]`-Struktur.

### Beispielcode

```rust
#[near_bindgen]
impl Contract {
    pub fn withdraw(&mut self, amount: U128) -> Promise {
        unimplemented!()
    }

    pub fn check_balance(&self) -> U128 {
        unimplemented!()
    }

    #[private]
    pub fn callback_withdraw(&mut self, amount: U128) {
        unimplemented!()
    }

    fn sub_balance(&mut self, amount: u128) {
        unimplemented!()
    }
}
```

In diesem Beispielcode sind alle vier Funktionen Methoden einer `#[near_bindgen]`-Struktur `Contract`. Aber nur `withdraw` und `check_balance` sind öffentliche Schnittstellen. `callback_withdraw` ist eine öffentliche Funktion, die mit `#[private]` dekoriert ist, und somit eine interne Funktion. `sub_balance` ist eine private Funktion von `Contract`.
