
## Absence d'authentification à deux facteurs

### Configuration

* identifiant du détecteur : `yocto-attach`
* gravité : moyenne

### Description

Les fonctions privilégiées devraient vérifier si un yocto NEAR est attaché. Cela permettrait d'activer le 2FA dans le portefeuille NEAR pour des raisons de sécurité.

Cela peut être implémenté dans le contrat en ajoutant `assert_one_yocto`, ce qui est recommandé pour toutes les fonctions privilégiées.

Remarque : Il est difficile de localiser toutes les fonctions privilégiées sans informations sémantiques. Actuellement, **Rustle** considère toutes les fonctions impliquant `predecessor_account_id` dans des comparaisons comme étant privilégiées.

### Exemple de code

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

Dans cet exemple, `set_owner` est une fonction privilégiée et ne devrait être invoquée que par le propriétaire du contrat. La fonction `assert_owner` assure le privilège en vérifiant `predecessor_account_id`. Cette fonction devrait implémenter un 2FA pour des raisons de sécurité, ce qui peut être réalisé en ajoutant un appel à `assert_one_yocto` dans la fonction.
