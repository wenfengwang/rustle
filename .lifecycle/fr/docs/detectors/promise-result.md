
## Résultat de la promesse

### Configuration

* identifiant du détecteur : `promise-result`
* gravité : info

### Description

Trouvez toutes les utilisations de `env::promise_result`, qui fournit le résultat de l'exécution d'une promesse.

Ce détecteur aide à localiser rapidement la logique de traitement des résultats de promesses.

### Exemple de code

```rust
// https://github.com/ref-finance/ref-contracts/blob/b33c3a488b18f9cff82a3fdd53bf65d6aac09e15/ref-exchange/src/lib.rs#L434
let cross_call_result = match env::promise_result(0) {
    PromiseResult::Successful(result) => result,
    _ => env::panic(ERR124_CROSS_CALL_FAILED.as_bytes()),
};
```

Dans cet exemple, le résultat de la promesse est traité en fonction de son état (réussi ou non).
