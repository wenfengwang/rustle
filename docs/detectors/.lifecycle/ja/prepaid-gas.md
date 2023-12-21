
## `ft_transfer_call`におけるプリペイドガスのチェック不足

### Configuration

* detector id: `prepaid-gas`
* severity: low

### Description

`ft_transfer_call`では、クロスコントラクト呼び出しを開始する前に、`prepaid_gas`が`ft_on_transfer`および`ft_resolve_transfer`に対して十分であるかどうかをコントラクトがチェックするべきです。

### サンプルコード

このサンプルは[near-contract-standards](https://github.com/near/near-sdk-rs/tree/master/near-contract-standards)から取得されており、`ft_transfer_call`でクロスコントラクト呼び出しを行う前にプリペイドガスをチェックすべきです。

```rust
// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L136
fn ft_transfer_call(
    &mut self,
    receiver_id: AccountId,
    amount: U128,
    memo: Option<String>,
    msg: String,
) -> PromiseOrValue<U128> {
    require!(env::prepaid_gas() > GAS_FOR_FT_TRANSFER_CALL, "More gas is required");
    // ...
}
```
