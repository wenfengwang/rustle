
## 在回调中的恐慌可能会导致合约锁定

### 配置信息

* 检测器编号：lock-callback
* 严重级别：中等

### 说明

我们不推荐在回调函数中使用 assert、require 或任何可能引起恐慌的操作。

在 Near 平台上，回调函数需要恢复因为失败的 promise 而改变的某些状态。如果回调函数触发了恐慌，可能会导致状态无法完全恢复，进而出现意料之外的结果。

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

在这个示例中，合约首先删除订单，然后进行代币转移。如果代币转移失败，应当在 callback_transfer 函数中恢复订单。

然而，如果回调函数中的 assert 断言失败，将导致订单无法被恢复。
