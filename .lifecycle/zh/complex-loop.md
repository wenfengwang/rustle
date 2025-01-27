
## 循环内的复杂逻辑

### 配置

* 检测器 ID：`complex-loop`
* 严重性：info

### 描述

查找包含复杂逻辑的循环，这可能会导致 DoS（拒绝服务）问题。

建议限制迭代次数以避免 DoS 问题。

### 示例代码

```rust
impl User {
    pub fn complex_calc(&mut self) {
        // ...
    }
}

#[near_bindgen]
impl Contract {
    pub fn register_users(&mut self, user: User) {
        self.users.push(user);
    }

    pub fn update_all_users(&mut self) {
        for user in self.users.iter_mut() {
            user.complex_calc();
        }
    }
}
```

在此示例中，用户可以在不支付任何存储费用的情况下注册，因此 `users` 列表的 `len()` 可能会非常长。

假设函数 `complex_calc` 包含许多复杂的计算，并可能消耗大量的 gas。

在 `update_all_users` 函数中，一个循环正在迭代 `users`，并调用函数 `complex_calc`。这可能会耗尽所有的 gas。

恶意用户可以通过注册大量用户来进行攻击，而无需支付任何存储费用。
