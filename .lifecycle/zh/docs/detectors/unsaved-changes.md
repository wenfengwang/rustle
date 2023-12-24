## 未保存集合更改

### 配置

* 检测器 ID： `unsaved-changes`
* 严重性：高

### 描述

[NEAR SDK](https://crates.io/crates/near-sdk) 提供了一些地图集合，可以存储键值映射。您可以使用 `get` 通过键获取值，并通过使用指定的键调用 `insert` 来插入或覆盖该值。这些集合使用 borsh 进行序列化和反序列化。当您想对集合进行更改时，需要先 `get` 获取现有值，然后进行更改，最后再通过 `insert` 将其放回集合中。如果没有 `insert` 函数，更改将不会保存到合约中。

需要注意的是，从 [NEAR SDK 的 v4.1.0](https://docs.rs/near-sdk/4.1.0/near_sdk/index.html) 开始，开发者可以在 [`near_sdk::store`](https://docs.rs/near-sdk/4.1.0/near_sdk/store/index.html) 中使用地图，它会自动将更改写回，以避免 `near_sdk::collections` 引入的此问题。

### 示例代码

```rust
#[allow(unused)]
pub fn modify(&mut self, change: I128) {
    let mut balance = self
        .accounts
        .get(&env::predecessor_account_id())
        .unwrap_or_else(|| env::panic_str("帐户未注册"));

    balance = balance
        .checked_add(change.0)
        .unwrap_or_else(|| env::panic_str("溢出"));

    // self.accounts
    //     .insert(&env::predecessor_account_id(), &balance);
}
```

在此示例中，`balance` 是从 `self.accounts` 中以调用者的帐户 ID 为索引的值，合约通过调用 `checked_add` 对其进行一些更改。然而，如果不调用 `insert` 函数，则更改不会被保存。