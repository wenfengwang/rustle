
## Änderungen an Sammlungen werden nicht gespeichert

### Konfiguration

* Detektor-ID: `unsaved-changes`
* Schweregrad: hoch

### Beschreibung

Das [NEAR SDK](https://crates.io/crates/near-sdk) bietet verschiedene Map-Sammlungen, die Schlüssel-Wert-Zuordnungen speichern können. Sie können `get` verwenden, um einen Wert über seinen Schlüssel abzurufen und den Wert durch Aufrufen von `insert` mit einem spezifizierten Schlüssel einzufügen oder zu überschreiben. Die Sammlungen nutzen Borsh für die Serialisierung und Deserialisierung. Wenn Sie Änderungen an einer Sammlung vornehmen möchten, müssen Sie einen vorhandenen Wert mit `get` abrufen, Änderungen daran vornehmen und ihn dann mit `insert` wieder in die Sammlung einfügen. Ohne die Funktion `insert` werden die Änderungen nicht im Smart Contract gespeichert.

Beachten Sie, dass Entwickler seit der Version [4.1.0](https://docs.rs/near-sdk/4.1.0/near_sdk/index.html) des NEAR SDK Maps in [`near_sdk::store`](https://docs.rs/near-sdk/4.1.0/near_sdk/store/index.html) verwenden können, die Änderungen automatisch zurückschreiben, um dieses durch `near_sdk::collections` eingeführte Problem zu vermeiden.

### Beispielcode

```rust
#[allow(unused)]
pub fn modify(&mut self, change: I128) {
    let mut balance = self
        .accounts
        .get(&env::predecessor_account_id())
        .unwrap_or_else(|| env::panic_str("Konto ist nicht registriert"));

    balance = balance
        .checked_add(change.0)
        .unwrap_or_else(|| env::panic_str("Überlauf"));

    // self.accounts
    //     .insert(&env::predecessor_account_id(), &balance);
}
```

In diesem Beispiel ist `balance` ein Wert aus `self.accounts`, der über die Konto-ID des Aufrufers indiziert wird. Der Vertrag führt einige Änderungen daran durch, indem er `checked_add` aufruft. Die Änderungen werden jedoch nicht gespeichert, ohne die Funktion `insert` aufzurufen.
