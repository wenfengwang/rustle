## 缺乏自我转账的检查

### 配置

* 检测器 ID：`self-transfer`
* 严重性：高

### 描述

在将代币转移到接收者之前，合约应检查接收者是否为发送者本身。否则，攻击者可能会利用这一漏洞无限制地铸造代币。

查看 [Stader\_\_NEAR 事件报告 — 2022年8月16日 | 由 Stader Labs 发布 | Medium](https://blog.staderlabs.com/stader-near-incident-report-08-16-2022-afe077ffd549) 和 [确保在 ft_transfer 中发送者和接收者不同 · stader-labs/near-liquid-token@04480ab (github.com)](https://github.com/stader-labs/near-liquid-token/commit/04480abe4585b75a663e1d7fae673da7d7fe7ea3) 以获取更多详情。

### 示例代码

在 [near-contract-standards](https://github.com/near/near-sdk-rs/tree/master/near-contract-standards) 中的代码展示了正确的实现，即接收者不应该是发送者。

```rust
// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L121
fn ft_transfer(&mut self, receiver_id: AccountId, amount: U128, memo: Option<String>) {
    // ...
    let sender_id = env::predecessor_account_id();
    let amount: Balance = amount.into();
    self.internal_transfer(&sender_id, &receiver_id, amount, memo);
}

// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L93
pub fn internal_transfer(&mut self, sender_id: &AccountId, receiver_id: &AccountId, amount: Balance, memo: Option<String>) {
    require!(sender_id != receiver_id, "Sender and receiver should be different");
    // ...
}
```
