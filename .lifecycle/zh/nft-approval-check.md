
## 在 NFT 转账时缺少检查批准 ID

### 配置

* 检测器 ID：`nft-approval-check`
* 严重程度：高

### 描述

在进行 NFT 转账（即 `nft_transfer` 和 `nft_transfer_call`）时，如果转账的发起者不是 NFT 的所有者，应检查转账的 `approval_id` 以确保发起者有权进行此次转账。没有这项检查，任何人都可以在未经批准的情况下将 NFT 转移给其他账户。

### 示例代码

在 [near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L212) 中的代码展示了正确的实现方式。

```rust
// https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L215
let app_acc_ids =
    approved_account_ids.as_ref().unwrap_or_else(|| env::panic_str("Unauthorized"));

// 正在使用 Approval 扩展；获取发起者的 approval_id。
let actual_approval_id = app_acc_ids.get(sender_id);

// 如果发起者完全没有被批准，则触发 panic
if actual_approval_id.is_none() {
    env::panic_str("Sender not approved");
}

// 如果包含 approval_id，则检查其是否匹配
require!(
    approval_id.is_none() || actual_approval_id == approval_id.as_ref(),
    format!(
        "实际的 approval_id {:?} 与给定的 approval_id {:?} 不符",
        actual_approval_id, approval_id
    )
);
```
