
## Absence de vérification du gaz prépayé dans `ft_transfer_call`

### Configuration

* identifiant du détecteur : `prepaid-gas`
* gravité : faible

### Description

Dans `ft_transfer_call`, le contrat doit vérifier si le `prepaid_gas` est suffisant pour `ft_on_transfer` et `ft_resolve_transfer` avant de lancer une invocation inter-contrats.

### Exemple de code

Cet exemple provient des [standards de contrat NEAR](https://github.com/near/near-sdk-rs/tree/master/near-contract-standards), le gaz prépayé devrait être vérifié avant de réaliser une invocation inter-contrats dans `ft_transfer_call`.

```rust
// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L136
fn ft_transfer_call(
    &mut self,
    receiver_id: AccountId,
    amount: U128,
    memo: Option<String>,
    msg: String,
) -> PromiseOrValue<U128> {
    require!(env::prepaid_gas() > GAS_FOR_FT_TRANSFER_CALL, "Plus de gaz est nécessaire");
    // ...
}
```
