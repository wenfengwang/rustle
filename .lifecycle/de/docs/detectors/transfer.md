
## Transferaktion

### Konfiguration

* Detektor-ID: `transfer`
* Schweregrad: info

### Beschreibung

Finden Sie alle Transferaktionen.

Dieser Detektor kann dabei helfen, alle Transferaktionen sowohl für native Token als auch für NEP-141-Token zu lokalisieren.

### Beispielcode

```rust
// Promise::transfer
Promise::new(env::predecessor_account_id()).transfer(amount);
```

```rust
// NEP141 ft_transfer
// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/account_deposit.rs#L446
ext_fungible_token::ft_transfer(
    sender_id.clone(),
    U128(amount),
    None,
    token_id,
    1,
    GAS_FOR_FT_TRANSFER,
)
.then(ext_self::exchange_callback_post_withdraw(
    token_id.clone(),
    sender_id.clone(),
    U128(amount),
    &env::current_account_id(),
    0,
    GAS_FOR_RESOLVE_TRANSFER,
))
```

In diesen Beispielen können sowohl der native Token-Transfer als auch der NEP-141-Token-Transfer von **Rustle** erkannt werden.
