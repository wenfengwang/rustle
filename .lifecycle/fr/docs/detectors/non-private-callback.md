
## Absence de la macro `#[private]` dans les fonctions de rappel

### Configuration

* identifiant du détecteur : `non-private-callback`
* gravité : élevée

### Description

La fonction de rappel devrait être décorée avec `#[private]` pour assurer qu'elle ne puisse être invoquée que par le contrat lui-même.

Sans cette macro, n'importe qui peut invoquer la fonction de rappel, ce qui est contraire à la conception initiale.

### Exemple de code

```rust
pub fn callback_stake(&mut self) { // ceci est une fonction de rappel
    // ...
}
```

La fonction `callback_stake` devrait être décorée avec `#[private]` :

```rust
#[private]
pub fn callback_stake(&mut self) { // ceci est une fonction de rappel
    // ...
}
```

Avec cette macro, seul le contrat lui-même peut invoquer `callback_stake`.
