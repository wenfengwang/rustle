
## Trouver toutes les interfaces publiques

### Configuration

* identifiant du détecteur : `public-interface`
* gravité : info

### Description

Les interfaces publiques sont des fonctions qui peuvent être appelées par d'autres. Plus précisément, il s'agit de fonctions publiques sans la macro `#[private]` d'une structure `#[near_bindgen]`.

### Exemple de code

```rust
#[near_bindgen]
impl Contract {
    pub fn withdraw(&mut self, amount: U128) -> Promise {
        unimplemented!()
    }

    pub fn check_balance(&self) -> U128 {
        unimplemented!()
    }

    #[private]
    pub fn callback_withdraw(&mut self, amount: U128) {
        unimplemented!()
    }

    fn sub_balance(&mut self, amount: u128) {
        unimplemented!()
    }
}
```

Dans cet exemple de code, les quatre fonctions sont des méthodes d'une structure `#[near_bindgen]` nommée `Contract`. Mais seulement `withdraw` et `check_balance` sont des interfaces publiques. `callback_withdraw` est une fonction publique décorée avec `#[private]`, donc elle est considérée comme une fonction interne. `sub_balance` est une fonction privée de `Contract`.
