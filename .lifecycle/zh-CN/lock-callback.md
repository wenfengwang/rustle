
## 在回调中的恐慌可能会锁定合约

### 配置信息

* 检测器编号：lock-callback
* 严重级别：中等

### 说明

建议不要在回调函数中使用 assert、require 或任何可能引发恐慌的操作。

在 Near 平台上，回调函数需要恢复因失败的承诺（promise）而改变的状态。如果回调函数触发了恐慌，那么状态可能无法完全恢复，这会导致出现意料之外的结果。

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

在这个示例中，合约首先删除了一个订单，随后进行代币转移。如果代币转移失败，应在 callback_transfer 函数中恢复订单。

但是，如果回调函数中的 assert 断言失败了，那么订单就无法被恢复。
