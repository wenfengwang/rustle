
## 在循环中的复杂逻辑

### 配置

* 检测器标识：复杂循环
* 严重级别：信息

### 描述

发现包含复杂逻辑的循环，这可能导致服务拒绝（DoS）问题。

推荐限制迭代次数，以避免服务拒绝（DoS）问题。

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

在这个例子中，用户可以免存储费注册，所以用户列表的长度可能会非常长。

假设函数 complex_calc 包含许多复杂计算，并且可能消耗大量的 gas。

在 update_all_users 函数中，通过调用 complex_calc 函数来迭代每个用户。这样可能会耗尽所有的 gas。

恶意用户可以通过注册大量不需支付存储费的用户来实施攻击。
