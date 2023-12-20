
## NFT转账过程中缺少检查批准ID

### 配置

* 探测器ID：nft-approval-check
* 严重性：高

### 描述

在进行NFT转账（即使用nft_transfer和nft_transfer_call函数）时，如果转账发起者并非NFT的所有者，那么应该检查该转账的approval_id，以确保发起者有权进行此次转账。没有这个检查，任何人都能在未获得批准的情况下，将NFT转移给其他账户。

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
