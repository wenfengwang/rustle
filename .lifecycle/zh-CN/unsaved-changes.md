
## 集合的更改未被保存

### 配置

* 检测器ID：未保存的更改
* 严重性：高

### 描述

[NEAR SDK](https://crates.io/crates/near-sdk) 提供了一些映射集合，可以存储键值映射。您可以使用 `get` 方法通过键获取值，并使用 `insert` 方法并指定键来插入或覆盖值。这些集合使用 borsh 进行序列化和反序列化。当您想对集合进行一些更改时，需要 `get` 到现有值并对其进行更改，然后再次使用 `insert` 将其插入集合。如果不使用 `insert` 函数，则更改将不会保存到合约中。

请注意，从 NEAR SDK [v4.1.0](https://docs.rs/near-sdk/4.1.0/near_sdk/index.html) 版本开始，开发者可以使用 maps in [`near_sdk::store`](https://docs.rs/near-sdk/4.1.0/near_sdk/store/index.html) 中的映射，这将自动回写更改，从而避免了使用 `near_sdk::collections` 时出现的问题。

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

在这个示例中，balance 是 self.accounts 中的一个值，通过调用者的账户ID进行索引，合约通过调用 checked_add 方法对其进行修改。然而，如果不调用 insert 方法，这些更改将不会被保存。
