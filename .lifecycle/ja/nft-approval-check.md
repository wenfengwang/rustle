
## NFT転送時の承認IDチェックの欠如

### Configuration

* detector id: `nft-approval-check`
* severity: 高

### Description

NFT転送（例えば、`nft_transfer`や`nft_transfer_call`）を行う際、転送の送信者がNFTの所有者でない場合、送信者がこの転送を行う権限があるかどうかを確認するために`approval_id`をチェックする必要があります。このチェックがないと、承認なしでNFTを他のアカウントに転送することが可能になってしまいます。

### サンプルコード

[near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L212)のコードは正しい実装を示しています。

```rust
// https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L215
let app_acc_ids =
    approved_account_ids.as_ref().unwrap_or_else(|| env::panic_str("Unauthorized"));

// Approval extension is being used; get approval_id for sender.
let actual_approval_id = app_acc_ids.get(sender_id);

// Panic if sender not approved at all
if actual_approval_id.is_none() {
    env::panic_str("Sender not approved");
}

// If approval_id included, check that it matches
require!(
    approval_id.is_none() || actual_approval_id == approval_id.as_ref(),
    format!(
        "The actual approval_id {:?} is different from the given approval_id {:?}",
        actual_approval_id, approval_id
    )
);
```
