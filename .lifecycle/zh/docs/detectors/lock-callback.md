## 在回调中出现恐慌可能会锁定合约

### 配置

* 检测器 ID： `lock-callback`
* 严重性：中

### 描述

不建议在回调函数中使用 `assert`、`require` 或任何可能导致程序崩溃的操作。

在 Near 中，回调函数需要恢复因失败的 promise 而产生的一些状态变更。如果回调函数出现恐慌，状态可能无法完全恢复，这将导致不预期的结果。

### 示例代码

```rust
fn process_order(&mut self, order_id: u32) -> Promise {
    let receiver = self.get_receiver(order_id);
    let amount = self.get_amount(order_id);
    self.delete_order(order_id);
    ext_contract::do_transfer(receiver, amount).then(ext_self::callback_transfer(order_id))
}

// ext_self::callback_transfer
#[private]
pub fn callback_transfer(&mut self, order_id: u32) {
    assert!(order_id > 0);

    match env::promise_result(0) {
        PromiseResult::NotReady => unreachable!(),
        PromiseResult::Successful(_) => {}
        PromiseResult::Failed => {
            self.recover_order(order_id);
        }
    };
}
```

在此示例中，合约首先删除订单，然后转移代币。如果转账失败，则应在 `callback_transfer` 中恢复订单。

然而，回调函数中有一个`assert`断言，如果它失败了，订单将不会被恢复。