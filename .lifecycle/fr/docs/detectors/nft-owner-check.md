
## Absence de vérification de l'identifiant d'approbation lors du transfert de NFT

### Configuration

* identifiant du détecteur : `nft-owner-check`
* gravité : élevée

### Description

Dans la conception du [NEP-178](https://github.com/near/NEPs/blob/master/neps/nep-0178.md), le propriétaire du NFT peut approuver ou révoquer les approbations en utilisant les interfaces spécifiées (c'est-à-dire, `nft_approve`, `nft_revoke` et `nft_revoke_all`). Une vérification du propriétaire doit être implémentée pour ces interfaces afin de s'assurer qu'elles ne soient appelables que par le propriétaire, sinon, n'importe qui pourrait modifier les approbations du NFT.

### Exemple de code

Le code dans [near-contract-standards](https://github.com/near/near-sdk-rs/blob/a903f8c44a7be363d960838d92afdb22d1ce8b87/near-contract-standards/src/non_fungible_token/approval/approval_impl.rs) illustre l'implémentation correcte.

```rust
// doit être implémenté pour `nft_approve`, `nft_revoke` et `nft_revoke_all`
let owner_id = expect_token_found(self.owner_by_id.get(&token_id));
let predecessor_account_id = env::predecessor_account_id();

require!(predecessor_account_id == owner_id, "Le prédécesseur doit être le propriétaire du jeton.");
```
