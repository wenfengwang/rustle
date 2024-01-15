
## Utilisation d'un type JSON incorrect

### Configuration

* identifiant du détecteur : `incorrect-json-type`
* gravité : élevée

### Description

N'utilisez pas les types `i64`, `i128`, `u64` ou `u128` comme paramètres ou valeurs de retour des interfaces publiques (fonctions publiques sans la macro `#[private]` dans une structure `#[near_bindgen]`).

Cela est dû au fait que le plus grand entier que JSON peut supporter est 2^53-1.

Consultez [https://2ality.com/2012/04/number-encoding.html](https://2ality.com/2012/04/number-encoding.html) pour plus de détails.

Les types `I64`, `I128`, `U64` et `U128` dans le Near SDK sont recommandés pour les développeurs.

### Exemple de code

```rust
// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/views.rs#L15
pub struct ContractMetadata {
    pub version: String,
    pub owner: AccountId,
    pub guardians: Vec<AccountId>,
    pub pool_count: u64,  // devrait utiliser `U64`
    pub state: RunningState,
    pub exchange_fee: u32,
    pub referral_fee: u32,
}

// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/views.rs#L171
#[near_bindgen]
impl Contract {
    pub fn metadata(&self) -> ContractMetadata {  // `u64` dans le type de retour
        // ...
    }
}
```

Dans cet exemple, la fonction `metadata` utilise la structure `ContractMetadata` qui contient `pool_count: u64` dans sa valeur de retour. Puisque les valeurs de retour des fonctions publiques sont envoyées au front-end en utilisant JSON et que la valeur de `pool_count` peut excéder 2^53-1, le type `U64` du Near SDK devrait être utilisé à la place.
