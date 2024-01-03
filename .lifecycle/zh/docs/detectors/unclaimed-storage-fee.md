
## 在尝试注销存储之前缺少存储费检查

### 配置

* 检测器 ID：`unclaimed-storage-fee`
* 严重程度：低

### 描述

根据 [NEP-145](https://github.com/near/NEPs/blob/master/neps/nep-0145.md#5-account-gracefully-closes-registration)，如果账户所有者尝试关闭账户，他需要在账户余额为零的情况下注销存储，除非设置了`force`标志。因此，NEP-145的实现应遵循此规则。

### 示例代码

以下是 `storage_unregister` 的错误示例：

```rust
fn storage_unregister(&mut self, force: Option<bool>) -> bool {
    assert_one_yocto();
    let account_id = env::predecessor_account_id();
    if let Some(balance) = self.accounts.get(&account_id) {
        self.accounts.remove(&account_id);
        self.total_supply -= balance;
        Promise::new(account_id.clone()).transfer(self.storage_balance_bounds().min.0 + 1);
        return true;
    } else {
        log!("账户 {} 未注册", &account_id);
    }
    false
}
```

这段代码将从 `accounts` 中移除账户，而不检查 `balance`。因此，正确的版本是：

```rust
fn storage_unregister(&mut self, force: Option<bool>) -> bool {
    assert_one_yocto();
    let account_id = env::predecessor_account_id();
    let force = force.unwrap_or(false);
    if let Some(balance) = self.accounts.get(&account_id) {
        if balance == 0 || force {
            self.accounts.remove(&account_id);
            self.total_supply -= balance;
            Promise::new(account_id.clone()).transfer(self.storage_balance_bounds().min.0 + 1);
            true
        } else {
            env::panic_str(
                "无法在没有强制的情况下注销余额为正的账户",
            )
        }
    } else {
        log!("账户 {} 未注册", &account_id);
        false
    }
}
```
