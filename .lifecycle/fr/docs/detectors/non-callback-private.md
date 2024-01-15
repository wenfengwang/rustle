
## Utilisation incorrecte de `#[private]` dans une fonction non-callback

### Configuration

* identifiant du détecteur : `non-callback-private`
* gravité : faible

### Description

La macro `#[private]` est habituellement utilisée dans une fonction de callback pour s'assurer que `current_account_id` est égal à `predecessor_account_id`. Elle ne devrait pas être utilisée dans des fonctions non-callback. Sinon, une fonction publique deviendrait interne.

### Exemple de code

```rust
#[near_bindgen]
impl Pool {
    #[private]
    pub fn get_tokens(&self) -> &[AccountId] {
        &self.token_account_ids
    }
}
```

`get_tokens` devrait être une interface publique (une fonction publique sans la décoration de la macro `#[private]`) afin que tout le monde puisse vérifier tous les types de jetons dans un pool. Elle ne devrait pas être décorée avec `#[private]`.
