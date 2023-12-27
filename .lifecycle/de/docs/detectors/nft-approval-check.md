
## Fehlende Überprüfung der Genehmigungs-ID bei NFT-Übertragungen

### Konfiguration

* Detektor-ID: `nft-approval-check`
* Schweregrad: hoch

### Beschreibung

Während einer NFT-Übertragung (d. h. `nft_transfer` und `nft_transfer_call`), sollte, falls der Absender der Übertragung nicht der Eigentümer des NFT ist, die `approval_id` überprüft werden, um sicherzustellen, dass der Absender die Autorität für diese Übertragung besitzt. Ohne diese Überprüfung könnte jeder ein NFT ohne Genehmigung auf andere Konten übertragen.

### Beispielcode

Der Code in [near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L212) zeigt die korrekte Implementierung.

```rust
// https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L215
let app_acc_ids =
    approved_account_ids.as_ref().unwrap_or_else(|| env::panic_str("Nicht autorisiert"));

// Die Approval-Erweiterung wird verwendet; hole `approval_id` für den Sender.
let actual_approval_id = app_acc_ids.get(sender_id);

// Panik, wenn der Sender überhaupt nicht genehmigt ist
if actual_approval_id.is_none() {
    env::panic_str("Sender nicht genehmigt");
}

// Wenn eine `approval_id` enthalten ist, überprüfe, ob sie übereinstimmt
require!(
    approval_id.is_none() || actual_approval_id == approval_id.as_ref(),
    format!(
        "Die tatsächliche `approval_id` {:?} unterscheidet sich von der angegebenen `approval_id` {:?}",
        actual_approval_id, approval_id
    )
);
```
