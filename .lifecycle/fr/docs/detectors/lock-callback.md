
## Un panic dans une fonction de rappel peut verrouiller le contrat

### Configuration

* identifiant du détecteur : `lock-callback`
* gravité : moyenne

### Description

Il n'est pas recommandé d'utiliser `assert`, `require` ou tout autre élément qui pourrait provoquer un panic dans une fonction de rappel.

Dans Near, la fonction de rappel doit restaurer certains changements d'état effectués par une promesse échouée. Si la fonction de rappel panique, l'état peut ne pas être complètement restauré, ce qui entraîne des résultats inattendus.

### Exemple de code

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

Dans cet exemple, le contrat supprime d'abord l'ordre, puis effectue le transfert du token. Si le transfert échoue, l'ordre devrait être restauré dans `callback_transfer`.

Cependant, il y a un `assert` dans la fonction de rappel, et si celui-ci échoue, l'ordre ne sera pas restauré.
