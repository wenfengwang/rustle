
## Division avant multiplication

### Configuration

* identifiant du détecteur : `div-before-mul`
* gravité : moyenne

### Description

Trouvez les cas de division avant multiplication comme `3 / 2 * 6 == 6`, qui donnent un résultat différent de `3 * 6 / 2 == 9`. Cela peut entraîner une perte de précision.

Il est conseillé d'effectuer la multiplication avant la division.

### Exemple de code

Voici un exemple. La formule `farm.amount / (farm.end_date - farm.start_date) as u128` sera arrondie à l'inférieur et peut entraîner une perte de précision.

```rust
// https://github.com/linear-protocol/LiNEAR/blob/fdbacc68c98205cba9f42c130d464ab3114257b6/contracts/linear/src/farm.rs#L125
let reward_per_session =
    farm.amount / (farm.end_date - farm.start_date) as u128 * SESSION_INTERVAL as u128;
```

Il est recommandé d'utiliser la division après la multiplication pour réduire la perte de précision :

```rust
let reward_per_session =
    farm.amount * SESSION_INTERVAL as u128 / (farm.end_date - farm.start_date) as u128;
```
