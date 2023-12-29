
## 集合的更改不会被保存

### 配置

* 检测器 ID：`unsaved-changes`
* 严重程度：高

### 描述

[NEAR SDK](https://crates.io/crates/near-sdk) 提供了一些可以存储键值映射的映射集合。你可以使用 `get` 通过键来获取值，并通过调用 `insert` 来插入或覆盖某个键的值。这些集合使用 borsh 进行序列化和反序列化，当你想对一个集合进行更改时，你需要先用 `get` 获取一个现有的值并对其进行更改，然后用 `insert` 将其重新插入集合。如果没有使用 `insert` 函数，更改将不会被保存到合约中。

请注意，从 NEAR SDK [v4.1.0](https://docs.rs/near-sdk/4.1.0/near_sdk/index.html) 版本开始，开发者可以使用 [`near_sdk::store`](https://docs.rs/near-sdk/4.1.0/near_sdk/store/index.html) 中的映射，这些映射会自动将更改写回，从而避免了 `near_sdk::collections` 引入的问题。

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

在这个示例中，`balance` 是 `self.accounts` 中的一个值，通过调用者的账户 ID 索引得到，合约通过调用 `checked_add` 对其进行了一些更改。然而，如果不调用 `insert` 函数，这些更改将不会被保存。
