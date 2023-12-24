## 在尝试注销存储之前缺少存储费用检查

### 配置

* 检测器 ID： `unclaimed-storage-fee`
* 严重性：低

### 描述

根据 [NEP-145](https://github.com/near/NEPs/blob/master/neps/nep-0145.md#5-account-gracefully-closes-registration)，如果一个账户的所有者试图关闭该账户，除非设置了 `force` 标志，否则他需要以零余额注销存储。因此，NEP-145的实施应遵守这个规则。

### 示例代码

这是一个错误的 `storage_unregister` 示例：

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

这个示例将会在不检查 `balance` 的情况下从 `accounts` 中移除账户。因此，正确的版本应该是：

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
                "无法在没有设置 force 的情况下注销带有正余额的账户",
            )
        }
    } else {
        log!("账户 {} 未注册", &account_id);
        false
    }
}