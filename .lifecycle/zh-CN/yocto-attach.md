
## 缺少双因素认证

### 配置信息

* 检测器ID：yocto-attach
* 严重性：中等

### 描述

应当确保特权功能在执行时检查是否绑定了一个yocto NEAR。这样做可以在NEAR钱包中启用双因素认证（2FA），以加强安全性。

在合约中实现这一点，可以通过增加assert_one_yocto函数调用来完成，推荐所有特权功能都应该添加这一断言。

注意：在缺乏语义信息的情况下，很难定位所有的特权功能。目前，**Rustle**默认所有涉及`predecessor_account_id`的函数为特权函数。

### 代码示例

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

在这个例子中，set_owner是一个特权函数，它应当仅被合约所有者调用。函数assert_owner通过检查调用者的前置账户ID来确认调用权限。基于安全考虑，这个函数应该加入双因素认证（2FA），这可以通过在函数中增加assert_one_yocto的调用来实现。
