## 对集合的更改不会被保存

### 配置

* 检测器 ID： `unsaved-changes`
* 严重性：高

### 描述

[NEAR SDK](https://crates.io/crates/near-sdk) 提供了一些可以存储键值映射的映射集合。您可以使用 `get` 通过其键来获取值，并通过调用 `insert` 并指定键来插入或覆盖值。这些集合使用borsh进行序列化和反序列化，当您想对一个集合进行更改时，您需要先用 `get` 取得现有的值并对其进行修改，然后用 `insert` 将其再次放入集合中。如果没有使用 `insert` 函数，这些更改将不会被保存到合约中。

注意，自 [NEAR SDK v4.1.0](https://docs.rs/near-sdk/4.1.0/near_sdk/index.html) 起，开发者可以在 [`near_sdk::store`](https://docs.rs/near-sdk/4.1.0/near_sdk/store/index.html) 中使用映射（maps），这将自动回写更改，以避免由 `near_sdk::collections` 引入的问题。

### 示例代码

```rust
#[allow(unused)]
pub fn modify(&mut self, change: I128) {
    let mut balance = self
        .accounts
        .get(&env::predecessor_account_id())
        .unwrap_or_else(|| env::panic_str("Account is not registered"));

    balance = balance
        .checked_add(change.0)
        .unwrap_or_else(|| env::panic_str("Overflow"));

    // self.accounts
    //     .insert(&env::predecessor_account_id(), &balance);
}
```

在此示例中，`balance` 是通过调用者的账户 ID 从 `self.accounts` 索引得到的值，合约通过调用 `checked_add` 对其进行一些更改。然而，如果不调用 `insert` 函数，这些更改将不会被保存。