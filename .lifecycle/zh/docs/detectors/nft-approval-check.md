## NFT 转移期间缺少批准 ID 检查

### 配置

* 检测器 ID： `nft-approval-check`
* 严重程度：高

### 描述

在 NFT 转移期间（即 `nft_transfer` 和 `nft_transfer_call`），如果转移的发送者不是 NFT 的所有者，则应检查转移的批准 ID，以确保发送者有权启动此转移。如果没有进行这一检查，任何人都可以在未经批准的情况下将 NFT 转移到其他帐户。

### 示例代码

在 [near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L212) 中的代码展示了正确的实现。

```rust
// https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/core/core_impl.rs#L215
let app_acc_ids =
    approved_account_ids.as_ref().unwrap_or_else(|| env::panic_str("Unauthorized"));

// 正在使用批准扩展；获取发送者的批准 ID。
let actual_approval_id = app_acc_ids.get(sender_id);

// 如果发送者根本没有批准，则出现紧急情况
if actual_approval_id.is_none() {
    env::panic_str("发送者未经批准");
}

// 如果包括批准 ID，请检查其是否匹配
require!(
    approval_id.is_none() || actual_approval_id == approval_id.as_ref(),
    format!(
        "实际批准 ID {:?} 与给定的批准 ID {:?} 不同",
        actual_approval_id, approval_id
    )
);