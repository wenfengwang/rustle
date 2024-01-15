
## Symboles incohérents

### Configuration

* identifiant du détecteur : `inconsistency`
* gravité : info

### Description

Les symboles ayant des noms similaires mais légèrement différents peuvent être mal utilisés. Une telle erreur est difficile à détecter manuellement mais peut entraîner des conséquences critiques.

### Exemple de code

```rust
ext::ft_transfer(
    receiver_id,
    U128(amount),
    None,
    token_id,
    1,
    GAS_FOR_NFT_TRANSFER  // devrait utiliser GAS_FOR_FT_TRANSFER ici
)
```

Dans cet exemple, le contrat devrait utiliser `GAS_FOR_FT_TRANSFER` au lieu de `GAS_FOR_NFT_TRANSFER`. Ces deux constantes peuvent avoir des valeurs très différentes, et le gaz pour le `ft_transfer` pourrait être insuffisant.
