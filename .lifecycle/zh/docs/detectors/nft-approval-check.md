## 在 NFT 转移期间缺少检查批准的 ID

### 配置

* 检测器 ID： `nft-approval-check`
* 严重性：高

### 描述

在 NFT 转移期间（即 `nft_transfer` 和 `nft_transfer_call`），如果转移的发起者不是 NFT 的所有者，则应检查转移的 `approval_id` 以确保发起者有权发起这次转移。没有这项检查，任何人都可以在未经批准的情况下将 NFT 转移给其他账户。

### 示例代码

[near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L212) 中的代码展示了正确的实现。

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