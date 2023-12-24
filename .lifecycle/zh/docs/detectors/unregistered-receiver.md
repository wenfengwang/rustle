## NEP-141 转账在未注册的接收方账户上不会引发恐慌

### 配置

* 检测器 ID： `unregistered-receiver`
* 严重性：中等

### 描述

根据 [NEP-141](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/fungible_token/core_impl.rs#L58) 的[实现](https://github.com/near/NEPs/blob/master/neps/nep-0141.md)，未注册的转账接收方不应该导致恐慌。

开发者可能会尝试为接收方注册一个新账户，而不支付存储费用，这可能导致 DoS 攻击。账户注册的一个可能的实现在 [storage_impl.rs](https://github.com/near/near-sdk-rs/blob/1859ce4c201d2a85fbe921fdada1df59b00d2d8c/near-contract-standards/src/fungible_token/storage_impl.rs#L45) 中。

### 示例代码

下面的代码段展示了两种解开账户余额（即接收方）的方法。安全的方法会在账户未注册时引发恐慌，而不安全的方法会返回默认余额 0 而不引发恐慌。在不安全的情况下，将会向 `accounts` 映射中插入一个新的键，其 `AccountId == account_id`，其存储费用由 `Contract` 的赞助商支付。

有关完整的示例代码，请参阅 [examples/unregistered-receiver](/examples/unregistered-receiver)。
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