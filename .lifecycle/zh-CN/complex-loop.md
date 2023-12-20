
## 循环中的复杂逻辑

### 配置

* 检测器标识：复杂循环
* 严重等级：信息

### 描述

找出包含复杂逻辑的循环，这可能导致DoS（拒绝服务）问题。

建议限制循环迭代次数以防止DoS问题发生。

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

在这个示例中，用户可以免存储费注册，因此用户列表可能会非常长。

假设函数complex_calc包含许多复杂运算，可能会消耗大量的gas（执行费用）。

在update_all_users函数中，通过调用complex_calc函数来迭代用户列表。这可能耗尽所有的gas。

恶意用户可以通过注册大量不需支付存储费的用户来进行攻击。
