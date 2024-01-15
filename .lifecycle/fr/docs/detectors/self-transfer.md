
## Absence de vérification pour l'auto-transfert

### Configuration

* identifiant du détecteur : `self-transfer`
* gravité : élevée

### Description

Avant de transférer des tokens au destinataire, le contrat doit vérifier si le destinataire n'est pas l'expéditeur lui-même. Sinon, les attaquants pourraient générer une quantité infinie de tokens en exploitant cette faille.

Consultez le [Stader\_\_NEAR Incident Report — 08/16/2022 | by Stader Labs | Medium](https://blog.staderlabs.com/stader-near-incident-report-08-16-2022-afe077ffd549) et [Ensure that sender and receiver are not the same in ft_transfer · stader-labs/near-liquid-token@04480ab (github.com)](https://github.com/stader-labs/near-liquid-token/commit/04480abe4585b75a663e1d7fae673da7d7fe7ea3) pour plus de détails.

### Exemple de code

Le code dans [near-contract-standards](https://github.com/near/near-sdk-rs/tree/master/near-contract-standards) illustre l'implémentation correcte où le destinataire ne doit pas être l'expéditeur.

```rust
// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L121
fn ft_transfer(&mut self, receiver_id: AccountId, amount: U128, memo: Option<String>) {
    // ...
    let sender_id = env::predecessor_account_id();
    let amount: Balance = amount.into();
    self.internal_transfer(&sender_id, &receiver_id, amount, memo);
}

// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L93
pub fn internal_transfer(&mut self, sender_id: &AccountId, receiver_id: &AccountId, amount: Balance, memo: Option<String>) {
    require!(sender_id != receiver_id, "L'expéditeur et le destinataire doivent être différents");
    // ...
}
```
