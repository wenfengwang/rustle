
## Fehlende Überprüfung bei Speichererweiterung

### Konfiguration

* Detektor-ID: `storage-gas`
* Schweregrad: niedrig

### Beschreibung

Jedes Mal, wenn der Zustand wächst, sollte sichergestellt werden, dass genügend Guthaben vorhanden ist, um die Erweiterung zu decken.

### Beispielcode

Im folgenden Code erweitert sich die Speichernutzung nach dem Einfügen in `self.banks`. Die Differenz sollte überprüft werden, um sicherzustellen, dass die vom Aufrufer angehängte Speicher-Gebühr ausreichend ist.

```rust
let prev_storage = env::storage_usage();

self.banks.insert(&Bank {
    owner: bank.owner,
    balance: bank.balance.0,
});

assert!(
    env::attached_deposit() > ((env::storage_usage() - prev_storage) as u128 * env::storage_byte_cost()),
    "nicht genügend Speicher-Gas"
);
```
