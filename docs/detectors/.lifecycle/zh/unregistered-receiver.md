
## NEP-141 转账不会因未注册的接收账户而panic

### 配置

* 检测器ID：`unregistered-receiver`
* 严重程度：中等

### 描述

根据[NEP-141](https://github.com/near/NEPs/blob/master/neps/nep-0141.md)的[实现](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/fungible_token/core_impl.rs#L58)，如果转账接收者未被注册，应该会触发panic。

开发者可能尝试为接收者注册新账户而不询问存储费，这可能导致DoS攻击。账户注册的可能实现在[storage_impl.rs](https://github.com/near/near-sdk-rs/blob/1859ce4c201d2a85fbe921fdada1df59b00d2d8c/near-contract-standards/src/fungible_token/storage_impl.rs#L45)

### 示例代码

下面的代码段展示了两种解包账户（即接收者）余额的方法。安全的方法在账户未注册时会panic，而不安全的方法会在不panic的情况下返回默认余额0。在不安全的情况下，一个新的键（AccountId等于account_id）会被插入到`accounts`映射中，其存储费用由`Contract`的赞助者支付。

完整的示例代码，请参考[examples/unregistered-receiver](/examples/unregistered-receiver)。

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