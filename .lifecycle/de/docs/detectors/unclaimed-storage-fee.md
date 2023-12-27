
## Fehlende Überprüfung der Speichergebühr vor dem Versuch, die Speicherregistrierung aufzuheben

### Konfiguration

* Detektor-ID: `unclaimed-storage-fee`
* Schweregrad: niedrig

### Beschreibung

Gemäß [NEP-145](https://github.com/near/NEPs/blob/master/neps/nep-0145.md#5-account-gracefully-closes-registration) muss der Inhaber eines Kontos, wenn er das Konto schließen möchte, die Speicherregistrierung mit einem Saldo von Null aufheben, es sei denn, das `force`-Flag ist gesetzt. Daher sollte die Implementierung von NEP-145 dieser Regel entsprechen.

### Beispielcode

Hier ist ein falsches Beispiel für `storage_unregister`:

```rust
fn storage_unregister(&mut self, force: Option<bool>) -> bool {
    assert_one_yocto();
    let account_id = env::predecessor_account_id();
    if let Some(balance) = self.accounts.get(&account_id) {
        self.accounts.remove(&account_id);
        self.total_supply -= balance;
        Promise::new(account_id.clone()).transfer(self.storage_balance_bounds().min.0 + 1);
        return true;
    } else {
        log!("Das Konto {} ist nicht registriert", &account_id);
    }
    false
}
```

Dieses entfernt das Konto aus `accounts`, ohne den `balance` zu überprüfen. Die korrekte Version ist also:

```rust
fn storage_unregister(&mut self, force: Option<bool>) -> bool {
    assert_one_yocto();
    let account_id = env::predecessor_account_id();
    let force = force.unwrap_or(false);
    if let Some(balance) = self.accounts.get(&account_id) {
        if balance == 0 || force {
            self.accounts.remove(&account_id);
            self.total_supply -= balance;
            Promise::new(account_id.clone()).transfer(self.storage_balance_bounds().min.0 + 1);
            true
        } else {
            env::panic_str(
                "Kann das Konto mit positivem Saldo nicht ohne 'force' abmelden",
            )
        }
    } else {
        log!("Das Konto {} ist nicht registriert", &account_id);
        false
    }
}
```
