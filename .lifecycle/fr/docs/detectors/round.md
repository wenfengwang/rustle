
## Arrondi incorrect sans spécification de `ceil` ou `floor`

### Configuration

* identifiant du détecteur : `round`
* gravité : moyenne

### Description

Trouvez si un arrondi est utilisé dans les opérations arithmétiques. Un arrondi sans direction spécifiée peut être exploité dans la finance décentralisée (DeFi). Référez-vous à [Comment devenir millionnaire, 0.000001 BTC à la fois (neodyme.io)](https://blog.neodyme.io/posts/lending_disclosure/) pour plus de détails.

Note : **Rustle** ne rapportera pas les fonctions d'arrondi implémentées par les développeurs pour des usages spécifiques.

### Exemple de code

```rust
let fee = (amount * fee_rate).round();
```

Dans cet exemple, les développeurs de contrats ne devraient pas utiliser `round` pour calculer les frais. Ils devraient plutôt utiliser `ceil` ou `floor` pour spécifier la direction de l'arrondi.
