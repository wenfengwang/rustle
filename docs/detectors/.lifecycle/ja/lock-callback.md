
## コールバック内のパニックがコントラクトをロックする可能性がある

### Configuration

* detector id: `lock-callback`
* severity: medium

### Description

コールバック関数内で`assert`や`require`など、パニックを引き起こす可能性のある操作を使用することは推奨されません。

NEARでは、コールバック関数は失敗したプロミスによって行われた状態変更の一部を復元する必要があります。コールバック関数がパニックを起こすと、状態が完全に復元されない可能性があり、予期しない結果を招くことがあります。

### サンプルコード

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

この例では、コントラクトは最初に注文を削除し、その後トークンを転送します。転送が失敗した場合、`callback_transfer`で注文を復元する必要があります。

しかし、コールバック関数内に`assert`があるため、これが失敗すると注文は復元されません。
