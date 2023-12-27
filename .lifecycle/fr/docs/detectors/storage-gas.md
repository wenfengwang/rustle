
## Absence de vérification pour l'expansion du stockage

### Configuration

* identifiant du détecteur : `storage-gas`
* gravité : faible

### Description

À chaque fois que l'état s'agrandit, il faut s'assurer qu'il y a suffisamment de Balance pour couvrir l'expansion.

### Exemple de code

Dans le code suivant, l'utilisation du stockage s'accroît après l'insertion dans `self.banks`. Il est nécessaire de vérifier la différence pour s'assurer que les frais de stockage attachés par l'appelant sont suffisants.

```rust
let prev_storage = env::storage_usage();

self.banks.insert(&Bank {
    owner: bank.owner,
    balance: bank.balance.0,
});

assert!(
    env::attached_deposit() > ((env::storage_usage() - prev_storage) as u128 * env::storage_byte_cost()),
    "insufficient storage gas"
);
```
