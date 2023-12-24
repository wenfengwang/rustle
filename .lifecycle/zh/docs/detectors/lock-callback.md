## 回调中的恐慌可能会锁定合约

### 配置

* 检测器 ID： `lock-callback`
* 严重性：中等

### 描述

不建议在回调函数中使用 `assert`、`require` 或任何可能导致恐慌的内容。

在 Near 中，回调函数需要恢复由失败的 promise 所做的一些状态更改。如果回调函数发生恐慌，可能无法完全恢复状态，从而导致意外结果。

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

在此示例中，合约首先删除订单，然后转移代币。如果转移失败，则应在 `callback_transfer` 中恢复订单。

然而，在回调函数中存在一个 `assert`，如果失败，订单将无法恢复。