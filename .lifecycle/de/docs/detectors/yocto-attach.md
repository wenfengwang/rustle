
## Fehlen der Zwei-Faktor-Authentifizierung

### Konfiguration

* Detektor-ID: `yocto-attach`
* Schweregrad: mittel

### Beschreibung

Privilegierte Funktionen sollten überprüfen, ob ein Yocto NEAR angehängt ist. Dies ermöglicht die Aktivierung der 2FA in der NEAR-Wallet aus Sicherheitsgründen.

Dies kann im Vertrag durch Hinzufügen von `assert_one_yocto` implementiert werden, was für alle privilegierten Funktionen empfohlen wird.

Hinweis: Es ist schwierig, alle privilegierten Funktionen ohne semantische Informationen zu lokalisieren. Derzeit betrachtet **Rustle** alle Funktionen, die `predecessor_account_id` in Vergleichen verwenden, als privilegierte.

### Beispielcode

```rust
pub(crate) fn assert_owner(&self) {
    assert_eq!(
        env::predecessor_account_id(),
        self.owner_id,
        "{}", ERR100_NOT_ALLOWED
    );
}

// https://github.com/ref-finance/ref-contracts/blob/536a60c842e018a535b478c874c747bde82390dd/ref-exchange/src/owner.rs#L16
#[payable]
pub fn set_owner(&mut self, owner_id: ValidAccountId) {
    assert_one_yocto();
    self.assert_owner();
    self.owner_id = owner_id.as_ref().clone();
}
```

In diesem Beispiel ist `set_owner` eine privilegierte Funktion und sollte nur vom Vertragseigentümer aufgerufen werden. Die Funktion `assert_owner` stellt die Berechtigung sicher, indem sie ihre `predecessor_account_id` überprüft. Diese Funktion sollte aus Sicherheitsgründen eine 2FA haben, und dies kann durch Hinzufügen eines Aufrufs von `assert_one_yocto` in der Funktion implementiert werden.
