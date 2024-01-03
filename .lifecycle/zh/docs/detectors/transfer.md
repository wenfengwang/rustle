
## 转账操作

### 配置

* 检测器 ID：`transfer`
* 严重级别：info

### 描述

查找所有转账操作。

此检测器可以帮助定位所有本地代币和 NEP-141 代币的转账操作。

### 示例代码

```rust
// Promise::transfer
Promise::new(env::predecessor_account_id()).transfer(amount);
```

```rust
// NEP-141 ft_transfer
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

在这些示例中，无论是本地代币转账还是 NEP-141 代币转账都可以被 **Rustle** 检测到。
