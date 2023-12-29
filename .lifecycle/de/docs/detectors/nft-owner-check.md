
## Fehlen der Überprüfung der Genehmigungs-ID bei NFT-Übertragung

### Konfiguration

* Detektor-ID: `nft-owner-check`
* Schweregrad: hoch

### Beschreibung

Im Design des [NEP-178](https://github.com/near/NEPs/blob/master/neps/nep-0178.md) kann der Besitzer des NFTs Genehmigungen erteilen oder widerrufen, indem er die spezifizierten Schnittstellen (d.h. `nft_approve`, `nft_revoke` und `nft_revoke_all`) nutzt. Eine Überprüfung des Eigentümers sollte für diese Schnittstellen implementiert werden, um sicherzustellen, dass sie nur vom Eigentümer aufgerufen werden können. Andernfalls könnte jeder die Genehmigungen des NFTs ändern.

### Beispielcode

Der Code in [near-contract-standards](https://github.com/near/near-sdk-rs/blob/a903f8c44a7be363d960838d92afdb22d1ce8b87/near-contract-standards/src/non_fungible_token/approval/approval_impl.rs) zeigt die korrekte Implementierung.

```rust
// sollte für `nft_approve`, `nft_revoke` und `nft_revoke_all` implementiert werden
let owner_id = expect_token_found(self.owner_by_id.get(&token_id));
let predecessor_account_id = env::predecessor_account_id();

require!(predecessor_account_id == owner_id, "Vorgänger muss Token-Besitzer sein.");
```
