
## Fehlende Prüfung auf Selbstüberweisung

### Konfiguration

* Detektor-ID: `self-transfer`
* Schweregrad: hoch

### Beschreibung

Bevor Token an den Empfänger übertragen werden, sollte der Vertrag prüfen, ob der Empfänger nicht der Sender selbst ist. Andernfalls könnten Angreifer diese Schwachstelle ausnutzen, um unendlich viele Token zu erzeugen.

Überprüfen Sie den [Stader\_\_NEAR Vorfallsbericht — 16.08.2022 | von Stader Labs | Medium](https://blog.staderlabs.com/stader-near-incident-report-08-16-2022-afe077ffd549) und [Stellen Sie sicher, dass Sender und Empfänger in ft_transfer nicht identisch sind · stader-labs/near-liquid-token@04480ab (github.com)](https://github.com/stader-labs/near-liquid-token/commit/04480abe4585b75a663e1d7fae673da7d7fe7ea3) für weitere Details.

### Beispielcode

Der Code in [near-contract-standards](https://github.com/near/near-sdk-rs/tree/master/near-contract-standards) zeigt die korrekte Implementierung, dass der Empfänger nicht der Sender sein sollte.

```rust
// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L121
fn ft_transfer(&mut self, receiver_id: AccountId, amount: U128, memo: Option<String>) {
    // ...
    let sender_id = env::predecessor_account_id();
    let amount: Balance = amount.into();
    self.internal_transfer(&sender_id, &receiver_id, amount, memo);
}

// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L93
pub fn internal_transfer(&mut self, sender_id: &AccountId, receiver_id: &AccountId, amount: Balance, memo: Option<String>) {
    require!(sender_id != receiver_id, "Sender und Empfänger sollten unterschiedlich sein");
    // ...
}
```
