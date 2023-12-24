## 循环中的复杂逻辑

### 配置

* 检测器 ID： `complex-loop`
* 严重性：信息

### 描述

查找包含复杂逻辑的循环，这可能会导致 DoS 问题。

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

在这个示例中，用户可以免费注册，因此 `users` 列表可能会非常长。

假设 `complex_calc` 函数包含许多复杂的计算，可能会消耗大量 gas。

在 `update_all_users` 中，循环遍历 `users` 并调用 `complex_calc` 函数。这可能会耗尽所有 gas。

恶意用户可以注册大量用户而不支付任何存储费用，从而发起攻击。