
## Fehlende Überprüfung von Prepaid-Gas in `ft_transfer_call`

### Konfiguration

* Detektor-ID: `prepaid-gas`
* Schweregrad: niedrig

### Beschreibung

In `ft_transfer_call` sollte der Vertrag prüfen, ob das Prepaid-Gas für `ft_on_transfer` und `ft_resolve_transfer` ausreichend ist, bevor ein Cross-Contract-Aufruf initiiert wird.

### Beispielcode

Dieses Beispiel stammt aus den [near-contract-standards](https://github.com/near/near-sdk-rs/tree/master/near-contract-standards). Prepaid-Gas sollte vor der Durchführung eines Cross-Contract-Aufrufs in `ft_transfer_call` überprüft werden.

```rust
// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L136
fn ft_transfer_call(
    &mut self,
    receiver_id: AccountId,
    amount: U128,
    memo: Option<String>,
    msg: String,
) -> PromiseOrValue<U128> {
    require!(env::prepaid_gas() > GAS_FOR_FT_TRANSFER_CALL, "Es wird mehr Gas benötigt");
    // ...
}
```
