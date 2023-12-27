
## Doppelte ID-Verwendung in Kollektionen

### Konfiguration

* Detektor-ID: `dup-collection-id`
* Schweregrad: mittel

### Beschreibung

Kollektionen im NEAR SDK verwenden die Funktion `new`, um sich zu initialisieren.

```rust
pub fn new<S>(prefix: S) -> Self
where
    S: IntoStorageKey,
```

Das Argument `prefix` ist ein Identifikator für die Kollektion. Jede Kollektion sollte eine ID haben, die sich von der ID anderer Kollektionen unterscheidet.

### Beispielcode

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
            users: UnorderedSet::new(StorageKey::Users), // Hier sollte `StorageKey::Users` verwendet werden
        }
    }
}
```

In diesem Beispiel teilen sich `orders` und `users` dieselbe ID, was zu unerwartetem Verhalten führen kann.
