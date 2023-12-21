
## 在回调中的恐慌可能导致合约锁定

### 配置

* 检测器 ID：`lock-callback`
* 严重程度：中等

### 描述

不建议在回调函数中使用 `assert`、`require` 或任何可能导致恐慌的操作。

在 Near 中，回调函数需要恢复因失败的 Promise 而做出的一些状态更改。如果回调函数发生恐慌，状态可能无法完全恢复，这会导致意外的结果。

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

在这个示例中，合约首先删除订单，然后进行代币转移。如果转移失败，应该在 `callback_transfer` 中恢复订单。

然而，如果回调函数中的 `assert` 失败了，订单就不会被恢复。
