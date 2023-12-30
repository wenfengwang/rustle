
## 自己送金のチェック不足

### 設定

* 検出器ID: `self-transfer`
* 重大度: 高

### 説明

トークンを受信者に転送する前に、コントラクトは受信者が送信者自身でないことを確認する必要があります。そうでない場合、攻撃者はこの脆弱性を悪用して無限にトークンを生成する可能性があります。

詳細については、[Stader\_\_NEAR Incident Report — 08/16/2022 | by Stader Labs | Medium](https://blog.staderlabs.com/stader-near-incident-report-08-16-2022-afe077ffd549) および [Ensure that sender and receiver are not the same in ft_transfer · stader-labs/near-liquid-token@04480ab (github.com)](https://github.com/stader-labs/near-liquid-token/commit/04480abe4585b75a663e1d7fae673da7d7fe7ea3) をご覧ください。

### サンプルコード

[near-contract-standards](https://github.com/near/near-sdk-rs/tree/master/near-contract-standards) にあるコードは、受信者が送信者と異なるべきであるという正しい実装を示しています。

```rust
// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L121
fn ft_transfer(&mut self, receiver_id: AccountId, amount: U128, memo: Option<String>) {
    // ...
    let sender_id = env::predecessor_account_id();
    let amount: Balance = amount.into();
    self.internal_transfer(&sender_id, &receiver_id, amount, memo);
}

// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L93
pub fn internal_transfer(&mut self, sender_id: &AccountId, receiver_id: &AccountId, amount: Balance, memo: Option<String>) {
    require!(sender_id != receiver_id, "Sender and receiver should be different");
    // ...
}
```
