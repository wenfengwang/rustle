
## Utilisation de la tautologie dans la condition d'une branche

### Configuration

* identifiant du détecteur : `tautology`
* gravité : faible

### Description

Recherchez une tautologie simple (impliquant `true` ou `false`) qui rend une branche déterministe.

### Exemple de code

```rust
let ok: bool = check_state();
if true || ok {
    // ...
} else {
    // ...
}
```

Dans cet exemple, le code à l'intérieur de la branche `else` ne sera jamais exécuté. Cela est dû au fait que `true || ok` est une tautologie.
