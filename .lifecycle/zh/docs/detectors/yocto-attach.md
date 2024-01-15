## 缺少双因素认证

### 配置

* 探测器ID：`yocto-attach`
* 严重性：中

### 描述

特权函数应检查是否附加了一 yocto NEAR。这将为了安全考虑在 NEAR 钱包中启用 2FA 功能。

这可以通过在合约中添加 `assert_one_yocto` 来实现，推荐用于所有的特权函数。

注意：如果没有语义信息，很难定位所有的特权函数。目前，**Rustle** 认为所有涉及 `predecessor_account_id` 进行比较的函数都是特权函数。

### 示例代码

```rust
pub(crate) fn assert_owner(&self) {
    assert_eq!(
        env::predecessor_account_id(),
        self.owner_id,
        "{}", ERR100_NOT_ALLOWED
    );
}

// https://github.com/ref-finance/ref-contracts/blob/536a60c842e018a535b478c874c747bde82390dd/ref-exchange/src/owner.rs#L16
#[payable]
pub fn set_owner(&mut self, owner_id: ValidAccountId) {
    assert_one_yocto();
    self.assert_owner();
    self.owner_id = owner_id.as_ref().clone();
}
```

在此示例中，`set_owner` 是一个特权函数，只能由合约所有者调用。函数 `assert_owner` 通过检查其 `predecessor_account_id` 来确保特权。出于安全考虑，此函数应具有双因素认证（2FA），可以通过在函数中添加 `assert_one_yocto` 调用来实现。