
## 转账操作

### 配置项

* 探测器编号：转账
* 重要性级别：信息

### 描述

查找所有的转账操作。

这个探测器能够帮助追踪本地代币和 NEP-141 代币的所有转账行为。

### 示例代码

```rust
// Promise::transfer
Promise::new(env::predecessor_account_id()).transfer(amount);
```

```rust
// NPE141 ft_transfer
// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/account_deposit.rs#L446
ext_fungible_token::ft_transfer(
    sender_id.clone(),
    U128(amount),
    None,
    token_id,
    1,
    GAS_FOR_FT_TRANSFER,
)
.then(ext_self::exchange_callback_post_withdraw(
    token_id.clone(),
    sender_id.clone(),
    U128(amount),
    &env::current_account_id(),
    0,
    GAS_FOR_RESOLVE_TRANSFER,
))
```

在这些示例中，**Rustle** 能够侦测到本地代币的转账和 NEP-141 代币的转账。
