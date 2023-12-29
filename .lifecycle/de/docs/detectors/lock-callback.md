
## Panik in der Callback-Funktion kann den Vertrag blockieren

### Konfiguration

* Detektor-ID: `lock-callback`
* Schweregrad: mittel

### Beschreibung

Es wird nicht empfohlen, `assert`, `require` oder ähnliche Anweisungen, die zu einer Panik führen können, in einer Callback-Funktion zu verwenden.

In NEAR muss die Callback-Funktion einige Zustandsänderungen rückgängig machen, die durch ein fehlgeschlagenes Promise verursacht wurden. Wenn die Callback-Funktion in Panik gerät, wird der Zustand möglicherweise nicht vollständig wiederhergestellt, was zu unerwarteten Ergebnissen führt.

### Beispielcode

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

In diesem Beispiel löscht der Vertrag zuerst die Bestellung und führt dann die Token-Übertragung durch. Wenn die Übertragung fehlschlägt, sollte die Bestellung in `callback_transfer` wiederhergestellt werden.

Allerdings gibt es ein `assert` in der Callback-Funktion; wenn dieses fehlschlägt, wird die Bestellung nicht wiederhergestellt.
