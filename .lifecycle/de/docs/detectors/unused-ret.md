
## Unbenutzte Rückgabewerte von Nicht-Void-Funktionen

### Konfiguration

* Detektor-ID: `unused-ret`
* Schweregrad: niedrig

### Beschreibung

Der Rückgabewert von Funktionen sollte genutzt werden. Andernfalls können Informationen verloren gehen oder nicht überprüft werden.

### Beispielcode

```rust
// https://github.com/ref-finance/ref-contracts/blob/117b044280053661fda217057560c8e35111856f/ref-exchange/src/lib.rs#L98
#[near_bindgen]
#[derive(BorshSerialize, BorshDeserialize, PanicOnDefault)]
pub struct Contract {
    // ...
    guardians: UnorderedSet<AccountId>,
    // ...
}

// https://github.com/ref-finance/ref-contracts/blob/536a60c842e018a535b478c874c747bde82390dd/ref-exchange/src/owner.rs#L65
#[near_bindgen]
impl Contract {
    #[payable]
    pub fn remove_guardians(&mut self, guardians: Vec<ValidAccountId>) {
        assert_one_yocto();
        self.assert_owner();
        for guardian in guardians {
            // pub fn remove(&mut self, element: &T) -> bool
            // Entfernt einen Wert aus dem Set. Gibt zurück, ob der Wert im Set vorhanden war.
            self.guardians.remove(guardian.as_ref());
        }
    }
}
```

In diesem Beispiel überprüft der Vertrag nicht den Rückgabewert von `remove`, um sicherzustellen, dass der `guardian` in `self.guardians` vorhanden ist. Wenn der `guardian` nicht existiert, wird das Programm nicht in einen Fehlerzustand versetzt, was unerwartete Auswirkungen haben kann.

Eine mögliche korrigierte Version ist wie folgt:

```rust
#[payable]
pub fn remove_guardians(&mut self, guardians: Vec<ValidAccountId>) -> Vec<ValidAccountId> {
    assert_one_yocto();
    self.assert_owner();
    let mut verbleibende_guardians = vec![];
    for guardian in guardians {
        if !self.guardians.remove(guardian.as_ref()) {
            verbleibende_guardians.push(guardian);
        }
    }
    verbleibende_guardians
}
```

In dieser Version gibt `remove_guardians` einen Vektor aller `guardians` zurück, die nicht in `self.guardians` enthalten sind.
