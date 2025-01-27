
## NFT転送時の承認IDチェックの欠如

### Configuration

* detector id: `nft-approval-check`
* severity: 高

### Description

NFT転送（例えば、`nft_transfer`や`nft_transfer_call`）時に、転送を行う送信者がNFTの所有者でない場合、送信者がこの転送を行う権限があるかどうかを確認するために`approval_id`をチェックする必要があります。このチェックがないと、承認なしに任意のユーザーがNFTを他のアカウントに転送することが可能になります。

### サンプルコード

[near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L212)にあるコードは、正しい実装を示しています。

```rust
// https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L215
let app_acc_ids =
    approved_account_ids.as_ref().unwrap_or_else(|| env::panic_str("Unauthorized"));

// 承認拡張機能が使用されています。送信者のためのapproval_idを取得します。
let actual_approval_id = app_acc_ids.get(sender_id);

// 送信者が全く承認されていない場合はパニックします
if actual_approval_id.is_none() {
    env::panic_str("Sender not approved");
}

// approval_idが含まれている場合、それが一致するかどうかをチェックします
require!(
    approval_id.is_none() || actual_approval_id == approval_id.as_ref(),
    format!(
        "実際のapproval_id {:?} が指定されたapproval_id {:?} と異なります",
        actual_approval_id, approval_id
    )
);
```
