
## Résultat d'une promesse non traitée

### Configuration

* identifiant du détecteur : `unhandled-promise`
* gravité : élevée

### Description

Les résultats des promesses doivent toujours être traités par une fonction de rappel ou une autre promesse. Il n'est pas recommandé de laisser des promesses non traitées dans les contrats. Autrement, l'état modifié ne peut pas être révoqué si la promesse échoue.

### Exemple de code

```rust
token.ft_transfer_call(receiver, U128(amount), None, "".to_string());
```

Dans cet exemple, le contrat invoque `ft_transfer_call` mais ne traite pas le résultat de sa promesse avec une fonction de rappel spécifiée (par exemple, `resolve_transfer`). Par conséquent, le contrat ne pourra pas savoir si le transfert a été réussi. Et si le transfert échoue, les états du contrat ne seront pas révoqués.
