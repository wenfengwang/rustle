
## NFT转移过程中缺少检查批准ID

### 配置

* 检测器ID：nft-approval-check
* 严重性：高

### 描述

在进行NFT转移（即nft_transfer和nft_transfer_call）时，如果转移的发起者不是NFT的所有者，应当检查转移时的approval_id，以确保发起者具有执行该转移的权限。没有这项检查，任何人都能在未经授权的情况下将NFT转移到其他账户。

### 示例代码

在[near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L212)中的代码展示了正确的实现方式。

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
