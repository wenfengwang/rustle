## NEP-141 转账不会在未注册的接收者账户上引发panic

### 配置

* 探测器 ID：`unregistered-receiver`
* 严重性：中

### 描述

根据 [NEP-141](https://github.com/near/NEPs/blob/master/neps/nep-0141.md) 的[实现](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/fungible_token/core_impl.rs#L58)，未注册的转账接收者应该会导致程序崩溃。

开发者可能会尝试在不要求存储费的情况下为接收者注册一个新账户，这可能导致DoS攻击。一个可能的账户注册实现可参考[storage_impl.rs](https://github.com/near/near-sdk-rs/blob/1859ce4c201d2a85fbe921fdada1df59b00d2d8c/near-contract-standards/src/fungible_token/storage_impl.rs#L45)

### 示例代码

下面的代码段展示了两种展开账户余额的方式（即接收者）。安全的方式在账户未注册时会触发panic，而不安全的方式会在不触发panic的情况下返回默认余额0。在不安全的情况下，一个新的键值对`AccountId == account_id`会被插入到`accounts`映射中，其存储费用由`Contract`的发起人支付。

有关完整的示例代码，请参阅 [示例/未注册的接收器](/examples/unregistered-receiver)。

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