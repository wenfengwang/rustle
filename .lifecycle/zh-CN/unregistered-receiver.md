
## NEP-141 转账不会因未注册的接收账户而出现异常

### 配置

* 检测器编号：未注册接收者
* 严重级别：中等

### 描述

根据[NEP-141](https://github.com/near/NEPs/blob/master/neps/nep-0141.md)的[实现](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/fungible_token/core_impl.rs#L58)，一个未注册的转账接收账户应该导致恐慌。

开发者可能会尝试为接收者注册新账户，而不需支付存储费用，这可能会导致服务拒绝攻击（DoS）。一个可能的账户注册实现可在 [storage_impl.rs](https://github.com/near/near-sdk-rs/blob/1859ce4c201d2a85fbe921fdada1df59b00d2d8c/near-contract-standards/src/fungible_token/storage_impl.rs#L45) 中找到。

### 示例代码

下面的代码段展示了两种获取账户（即接收者）余额的方法。安全的方法在账户未注册时会触发异常，而不安全的方法则会在不触发异常的情况下返回默认余额0。在不安全的情况下，一个AccountId 等于 account_id 的新键将被插入到 accounts 映射中，其存储费用由合约的赞助者支付。

完整示例代码请参考 [examples/unregistered-receiver](/examples/unregistered-receiver)。

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
