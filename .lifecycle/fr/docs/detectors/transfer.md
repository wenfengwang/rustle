
## Action de transfert

### Configuration

* identifiant du détecteur : `transfer`
* gravité : info

### Description

Trouvez toutes les actions de transfert.

Ce détecteur peut aider à localiser toutes les actions de transfert pour les tokens natifs et les tokens NEP-141.

### Exemple de code

```rust
// Promise::transfer
Promise::new(env::predecessor_account_id()).transfer(amount);
```

```rust
// NEP-141 ft_transfer
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

Dans ces exemples, le transfert de token natif et le transfert de token NEP-141 peuvent être détectés par **Rustle**.
