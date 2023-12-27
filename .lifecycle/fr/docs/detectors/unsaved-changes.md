
## Les modifications apportées aux collections ne sont pas sauvegardées

### Configuration

* identifiant du détecteur : `unsaved-changes`
* gravité : élevée

### Description

[NEAR SDK](https://crates.io/crates/near-sdk) fournit des collections de type map qui peuvent stocker des associations clé-valeur. Vous pouvez utiliser `get` pour obtenir une valeur par sa clé et insérer ou remplacer la valeur en appelant `insert` avec une clé spécifiée. Les collections utilisent borsh pour la sérialisation et la désérialisation. Lorsque vous souhaitez apporter des modifications à une collection, vous devez utiliser `get` pour récupérer une valeur existante et la modifier, puis la réinsérer dans la collection avec `insert`. Sans l'utilisation de la fonction `insert`, les modifications ne seront pas sauvegardées dans le contrat.

Notez que depuis la version [v4.1.0](https://docs.rs/near-sdk/4.1.0/near_sdk/index.html) du NEAR SDK, les développeurs peuvent utiliser les maps dans [`near_sdk::store`](https://docs.rs/near-sdk/4.1.0/near_sdk/store/index.html) qui enregistrent automatiquement les modifications, évitant ainsi le problème introduit par `near_sdk::collections`.

### Exemple de code

```rust
#[allow(unused)]
pub fn modify(&mut self, change: I128) {
    let mut balance = self
        .accounts
        .get(&env::predecessor_account_id())
        .unwrap_or_else(|| env::panic_str("Le compte n'est pas enregistré"));

    balance = balance
        .checked_add(change.0)
        .unwrap_or_else(|| env::panic_str("Dépassement de capacité"));

    // self.accounts
    //     .insert(&env::predecessor_account_id(), &balance);
}
```

Dans cet exemple, `balance` est une valeur de `self.accounts` indexée par l'identifiant de compte de l'appelant. Le contrat apporte des modifications en utilisant `checked_add`. Cependant, les modifications ne sont pas sauvegardées sans l'appel de la fonction `insert`.
