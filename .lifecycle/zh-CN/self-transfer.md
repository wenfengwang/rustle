
## 自助转账缺乏校验

### 配置

* 检测器ID：自我转账
* 严重性：高

### 描述

在向接收方转账之前，合约应当检查接收方是否就是发送方本人。否则，攻击者可能会利用这一漏洞无限制地铸造代币。

请查阅[Stader\_\_NEAR Incident Report — 2022年8月16日 | 由Stader Labs撰写 | Medium](https://blog.staderlabs.com/stader-near-incident-report-08-16-2022-afe077ffd549)和[Ensure that sender and receiver are not the same in ft_transfer · stader-labs/near-liquid-token@04480ab (github.com)](https://github.com/stader-labs/near-liquid-token/commit/04480abe4585b75a663e1d7fae673da7d7fe7ea3)以获取更多详细信息。

### 示例代码

在[near-contract-standards](https://github.com/near/near-sdk-rs/tree/master/near-contract-standards)中的代码显示了正确的实现，接收方不应该是发送方。

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
