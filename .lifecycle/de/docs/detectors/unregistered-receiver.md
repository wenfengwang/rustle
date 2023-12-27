
## NEP-141-Übertragungen lösen keine Panik bei nicht registrierten Empfängerkonten aus

### Konfiguration

* Detektor-ID: `unregistered-receiver`
* Schweregrad: mittel

### Beschreibung

Laut der [Implementierung](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/fungible_token/core_impl.rs#L58) von [NEP-141](https://github.com/near/NEPs/blob/master/neps/nep-0141.md) sollte ein Transfer zu einem nicht registrierten Empfänger zu einer Panik führen.

Entwickler könnten versuchen, ein neues Konto für den Empfänger zu registrieren, ohne eine Speicherplatzgebühr zu verlangen, was zu einem DoS führen kann. Eine mögliche Implementierung der Kontoregistrierung findet sich in [storage_impl.rs](https://github.com/near/near-sdk-rs/blob/1859ce4c201d2a85fbe921fdada1df59b00d2d8c/near-contract-standards/src/fungible_token/storage_impl.rs#L45)

### Beispielcode

Das untenstehende Code-Segment zeigt zwei Methoden, um den Saldo eines Kontos (d. h. des Empfängers) zu ermitteln. Die sichere Methode löst eine Panik aus, wenn das Konto nicht registriert ist, während die unsichere Methode ohne Panik einen Standard-Saldo von 0 zurückgibt. Im unsicheren Fall wird ein neuer Schlüssel mit `AccountId == account_id` in die `accounts`-Map eingefügt, dessen Speicherplatzgebühr vom Sponsor des `Contract` bezahlt wird.

Für den vollständigen Beispielcode siehe [examples/unregistered-receiver](/examples/unregistered-receiver).

```rust
#[near_bindgen]
#[derive(BorshDeserialize, BorshSerialize)]
pub struct Contract {
    accounts: UnorderedMap<AccountId, Balance>,
    total_supply: Balance,
}

impl Contract {
    pub fn internal_unwrap_balance_safe(&self, account_id: &AccountId) -> Balance {
        self.accounts
            .get(account_id)
            .unwrap_or_else(|| env::panic_str("Account is not registered"))
    }
    pub fn internal_unwrap_balance_unsafe(&self, account_id: &AccountId) -> Balance {
        self.accounts.get(account_id).unwrap_or(0)
    }
}
```
