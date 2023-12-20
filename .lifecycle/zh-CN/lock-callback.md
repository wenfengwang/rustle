
## 在回调中的恐慌可能会导致合约锁定

### 配置信息

* 检测器编号：lock-callback
* 严重等级：中等

### 说明

建议避免在回调函数中使用 assert、require 或任何可能引发恐慌的操作。

在 Near 平台上，回调函数需要恢复因承诺失败而进行的某些状态更改。如果回调函数发生恐慌，可能无法完全恢复状态，这将导致不预期的结果。

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

在这个示例中，合约先删除订单，然后进行代币转移。如果代币转移失败，应在 callback_transfer 中恢复订单。

然而，如果回调函数中的 assert 断言失败了，那么订单就无法被恢复。
