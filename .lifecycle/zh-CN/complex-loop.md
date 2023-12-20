
## 循环中的复杂逻辑

### 配置

* 检测器ID：complex-loop
* 严重性：信息

### 描述

找出包含复杂逻辑的循环，这可能导致DoS（拒绝服务）问题。

建议限制循环迭代次数以防止DoS问题。

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

在这个示例中，用户可以免费注册，因此用户列表的长度可能非常长。

假设函数complex_calc包含许多复杂运算，可能会耗费大量gas。

在update_all_users函数中，一个循环正在迭代用户列表，并调用complex_calc函数。这可能耗尽所有的gas。

恶意用户可以通过注册大量不需要支付存储费用的用户来发起攻击。
