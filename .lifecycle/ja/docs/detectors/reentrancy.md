
## Reentrancy

### Configuration

* detector id: `reentrancy`
* severity: 高

### Description

リエントランシー攻撃に対して脆弱な関数を検出します。

コントラクトは、クロスコントラクト呼び出しを行う前に常に状態を変更し、その呼び出しが失敗した場合にはコールバック関数で変更をロールバックするべきです。

### Sample code

以下はリエントランシー攻撃の一例です。被害者コントラクトは、`ft_resolve_transfer` 関数内で状態（つまり、`attacker_balance`）を更新しますが、これは攻撃者への転送が成功した後のみです。

被害者コントラクトは `ft_token::ft_transfer_call` を呼び出してトークンを転送し、内部転送後に攻撃者の `ft_on_transfer` を呼び出します。

しかし、攻撃者の `ft_on_transfer` が被害者の `withdraw` を再度呼び出すと、状態（つまり、`attacker_balance`）がまだ変更されていないため、被害者は攻撃者に再度転送することになります。

コールグラフは以下の通りです。

```mermaid
graph LR

0[victim::withdraw]
1[ft_token::ft_transfer_call]
2[attacker::ft_on_transfer]
3[victim::ft_resolve_transfer]
4[victim::withdraw]
5[ft_token::ft_transfer_call]
6[attacker::ft_on_transfer]
7[victim::ft_resolve_transfer]

0 --> 1 & 3
1 --> 2 --> 4
4 --> 5 & 7
5 --> 6
```

攻撃者コントラクト:

```rust
#[near_bindgen]
impl MaliciousContract {
    pub fn ft_on_transfer(&mut self, amount: u128) {
        if self.reentered == false {
            ext_victim::withdraw(
                amount.into(),
                &VICTIM,
                0,
                env::prepaid_gas() - GAS_FOR_SINGLE_CALL,
            );
        }
        self.reentered = true;
    }
}

```

FTコントラクト:

```rust
#[near_bindgen]
impl FungibleToken {
    pub fn ft_transfer_call(&mut self, amount: u128) -> PromiseOrValue<U128> {
        // internal transfer
        self.attacker_balance += amount;
        self.victim_balance -= amount;

        ext_fungible_token_receiver::ft_on_transfer(
            amount.into(),
            &ATTACKER,
            0,
            env::prepaid_gas() - GAS_FOR_SINGLE_CALL,
        )
        .into()
    }
}
```

被害者コントラクト:

```rust
#[near_bindgen]
impl VictimContract {
    pub fn withdraw(&mut self, amount: u128) -> Promise {
        assert!(self.attacker_balance >= amount);
        ext_ft_token::ft_transfer_call(
            amount.into(),
            &FT_TOKEN,
            0,
            env::prepaid_gas() - GAS_FOR_SINGLE_CALL * 2,
        ).then(ext_self::ft_resolve_transfer(
            amount.into(),
            &env::current_account_id(),
            0,
            GAS_FOR_SINGLE_CALL,
        ))
    }

    #[private]
    pub fn ft_resolve_transfer(&mut self, amount: u128) {
        match env::promise_result(0) {
            PromiseResult::NotReady => unreachable!(),
            PromiseResult::Successful(_) => {
                self.attacker_balance -= amount;
            }
            PromiseResult::Failed => {}
        };
    }
}
```

正しい実装では、外部関数を呼び出す前に状態を変更し、Promise が失敗した場合のみ状態を復元します。

```rust
#[near_bindgen]
impl VictimContract {
    pub fn withdraw(&mut self, amount: u128) -> Promise {
        assert!(self.attacker_balance >= amount);
        self.attacker_balance -= amount;
        ext_ft_token::ft_transfer_call(
            amount.into(),
            &FT_TOKEN,
            0,
            env::prepaid_gas() - GAS_FOR_SINGLE_CALL * 2,
        ).then(ext_self::ft_resolve_transfer(
            amount.into(),
            &env::current_account_id(),
            0,
            GAS_FOR_SINGLE_CALL,
        ))
    }

    #[private]
    pub fn ft_resolve_transfer(&mut self, amount: u128) {
        match env::promise_result(0) {
            PromiseResult::NotReady => unreachable!(),
            PromiseResult::Successful(_) => {}
            PromiseResult::Failed => {
                self.attacker_balance += amount;
            }
        };
    }
}
```
