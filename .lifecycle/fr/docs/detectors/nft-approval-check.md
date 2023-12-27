
## Absence de vérification de l'identifiant d'approbation lors du transfert de NFT

### Configuration

* identifiant du détecteur : `nft-approval-check`
* gravité : élevée

### Description

Lors d'un transfert de NFT (c'est-à-dire, `nft_transfer` et `nft_transfer_call`), si l'expéditeur du transfert n'est pas le propriétaire du NFT, l'`approval_id` du transfert doit être vérifié pour s'assurer que l'expéditeur a l'autorité nécessaire pour initier ce transfert. Sans cette vérification, n'importe qui pourrait transférer un NFT vers d'autres comptes sans approbation.

### Exemple de code

Le code dans [near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L212) montre l'implémentation correcte.

```rust
// https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L215
let app_acc_ids =
    approved_account_ids.as_ref().unwrap_or_else(|| env::panic_str("Non autorisé"));

// L'extension d'approbation est utilisée ; obtenir l'approval_id pour l'expéditeur.
let actual_approval_id = app_acc_ids.get(sender_id);

// Panique si l'expéditeur n'est pas du tout approuvé
if actual_approval_id.is_none() {
    env::panic_str("Expéditeur non approuvé");
}

// Si un approval_id est inclus, vérifier qu'il correspond
require!(
    approval_id.is_none() || actual_approval_id == approval_id.as_ref(),
    format!(
        "L'approval_id actuel {:?} est différent de l'approval_id fourni {:?}",
        actual_approval_id, approval_id
    )
);
```
