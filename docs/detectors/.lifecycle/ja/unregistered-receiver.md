
## NEP-141 トランスファーは未登録の受信者アカウントに対してパニックを起こさない

### Configuration

* detector id: `unregistered-receiver`
* severity: medium

### Description

[NEP-141](https://github.com/near/NEPs/blob/master/neps/nep-0141.md)の[実装](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/fungible_token/core_impl.rs#L58)によると、未登録のトランスファー受信者にはパニックが発生するべきです。

開発者はストレージ料金を要求せずに受信者の新しいアカウントを登録しようとすることがあり、これがDoS攻撃につながる可能性があります。アカウント登録の一つの実装例は[storage_impl.rs](https://github.com/near/near-sdk-rs/blob/1859ce4c201d2a85fbe921fdada1df59b00d2d8c/near-contract-standards/src/fungible_token/storage_impl.rs#L45)にあります。

### サンプルコード

以下のコードセグメントは、アカウント（つまり、受信者）の残高をアンラップする2つの方法を示しています。安全な方法はアカウントが未登録の場合にパニックを起こしますが、安全でない方法はパニックせずにデフォルト残高0を返します。安全でない場合、`AccountId == account_id`を持つ新しいキーが`accounts`マップに挿入され、そのストレージ料金は`Contract`のスポンサーが支払います。

完全なサンプルコードについては、[examples/unregistered-receiver](/examples/unregistered-receiver)を参照してください。

```rust
#[near_bindgen]
#[derive(BorshDeserialize, BorshSerialize)]
pub struct Contract {
    accounts: UnorderedMap<AccountId, Balance>,
    total_supply: Balance,
}

impl Contract {
    pub fn internal_unwrap_balance_safe(&self, account_id: &AccountId) -> Balance {
        self.accounts
            .get(account_id)
            .unwrap_or_else(|| env::panic_str("Account is not registered"))
    }
    pub fn internal_unwrap_balance_unsafe(&self, account_id: &AccountId) -> Balance {
        self.accounts.get(account_id).unwrap_or(0)
    }
}
```
