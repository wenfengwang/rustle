
## Vérifier l'intégrité des interfaces NEP

### Configuration

* identifiant du détecteur : `nep${id}-interface` (`${id}` est l'ID NEP)
* gravité : moyenne

### Description

Les [NEPs](https://github.com/near/NEPs) représentent les Near Enhancement Proposals, qui sont des propositions d'amélioration du protocole NEAR. Actuellement, il existe des NEPs pour les FT, NFT, MT et la gestion du stockage, listés dans un [tableau](https://github.com/near/NEPs#neps).

Pour utiliser ce détecteur, vous devez spécifier l'ID NEP dans l'identifiant du détecteur, par exemple :

```bash
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep141-interface  # Standard de Token Fongible
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep145-interface  # Gestion du Stockage
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep171-interface  # Standard de Token Non Fongible
```

### Exemple de code

L'[exemple](/examples/nep-interface/) du détecteur `nep-interface` est adapté des standards de contrat NEAR.
