## 转移操作

### 配置

* 检测器 ID： `transfer`
* 严重性：信息

### 描述

查找所有的转移操作。

该检测器可以帮助定位所有原生代币和 NEP 141 代币的转移操作。

### 示例代码

```rust
// Promise::transfer
Promise::new(env::predecessor_account_id()).transfer(amount);
```

```rust
// NEP141 ft_transfer
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

在这些示例中，**Rustle** 可以检测到原生代币转移和 NEP 141 代币转移。