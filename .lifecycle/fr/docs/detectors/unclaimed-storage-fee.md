
## Contrôle manquant pour les frais de stockage avant de tenter de désinscrire le stockage

### Configuration

* identifiant du détecteur : `unclaimed-storage-fee`
* gravité : faible

### Description

Selon [NEP-145](https://github.com/near/NEPs/blob/master/neps/nep-0145.md#5-account-gracefully-closes-registration), si le propriétaire d'un compte essaie de fermer le compte, il doit se désinscrire du stockage avec un solde nul à moins que l'option `force` ne soit définie. Ainsi, l'implémentation de NEP-145 doit se conformer à cette règle.

### Exemple de code

Voici un exemple incorrect de `storage_unregister` :

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
        log!("The account {} is not registered", &account_id);
    }
    false
}
```

Cette version supprime le compte de `accounts` sans vérifier le `balance`. La version correcte est donc :

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
                "Can't unregister the account with a positive balance without force",
            )
        }
    } else {
        log!("The account {} is not registered", &account_id);
        false
    }
}
```
