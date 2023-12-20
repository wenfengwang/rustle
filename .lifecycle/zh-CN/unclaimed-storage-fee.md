
## 在尝试注销存储前未进行存储费用检查

### 配置信息

* 检测器ID：未领取的存储费
* 严重性：低

### 描述

依据[NEP-145](https://github.com/near/NEPs/blob/master/neps/nep-0145.md#5-account-gracefully-closes-registration)，如果账户所有者试图关闭账户，他需要在账户余额为零的情况下注销存储，除非设定了`force`标志。因此，NEP-145的实现应当遵循此规则。

### 示例代码

这里有一个错误的storage_unregister示例：

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
        log!("The account {} is not registered", &account_id);
    }
    false
}
```

该操作会在不检查余额的情况下，直接从账户列表中移除账户。因此，正确的版本应该是：

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
                "Can't unregister the account with the positive balance without force",
            )
        }
    } else {
        log!("The account {} is not registered", &account_id);
        false
    }
}
```
