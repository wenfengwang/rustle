
## Mathématiques non sécurisées sans vérification de débordement

### Configuration

* identifiant du détecteur : `unsafe-math`
* gravité : élevée

### Description

Activez les vérifications de débordement pour toutes les opérations arithmétiques. Sinon, un débordement peut se produire, entraînant des résultats incorrects.

Les vérifications de débordement dans les contrats NEAR peuvent être implémentées avec deux méthodes différentes.

1. \[Recommandé\] Activez l'option `overflow-checks` dans le manifeste cargo. Dans ce cas, il est acceptable d'utiliser `+`, `-` et `*` pour les opérations arithmétiques.
2. Utilisez des fonctions de mathématiques sécurisées (par exemple, `checked_xxx()`) pour réaliser des opérations arithmétiques.

### Exemple de code

Dans cet exemple, puisque le drapeau `overflow-checks` est désactivé dans le manifeste cargo, l'utilisation de `+` peut conduire à un débordement.

```toml
[profile.xxx]  # `xxx` équivaut à `dev` ou `release`
overflow-checks = false
```

```rust
let a = b + c;
```

Le code suivant est recommandé pour réaliser l'opération d'addition avec `overflow-checks=false`

```rust
let a = b.checked_add(c);
```
