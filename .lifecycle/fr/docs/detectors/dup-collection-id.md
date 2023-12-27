
## Utilisation d'identifiants en double dans les collections

### Configuration

* identifiant du détecteur : `dup-collection-id`
* gravité : moyenne

### Description

Les collections dans le SDK NEAR utilisent la fonction `new` pour s'initialiser.

```rust
pub fn new<S>(prefix: S) -> Self
where
    S: IntoStorageKey,
```

L'argument `prefix` est un identifiant pour la collection. Chaque collection doit avoir un identifiant différent de celui des autres collections.

### Exemple de code

```rust
#[near_bindgen]
#[derive(BorshDeserialize, BorshSerialize)]
pub struct Contract {
    orders: UnorderedMap<u16, Order>,
    users: UnorderedSet<AccountId>,
}

#[near_bindgen]
impl Contract {
    #[init]
    pub fn new() -> Self {
        Self {
            orders: UnorderedMap::new(StorageKey::Orders),
            users: UnorderedSet::new(StorageKey::Users), // Devrait utiliser `StorageKey::Users` ici
        }
    }
}
```

Dans cet exemple, `orders` et `users` partageaient le même identifiant, ce qui pourrait entraîner un comportement inattendu.
