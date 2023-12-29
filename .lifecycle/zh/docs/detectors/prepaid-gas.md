
## `ft_transfer_call`中缺乏对预付Gas的检查

### 配置

* 检测器ID：`prepaid-gas`
* 严重性：低

### 描述

在`ft_transfer_call`中，合约应在发起跨合约调用之前检查`prepaid_gas`是否足够用于`ft_on_transfer`和`ft_resolve_transfer`。

### 示例代码

此示例来自[near-contract-standards](https://github.com/near/near-sdk-rs/tree/master/near-contract-standards)，在`ft_transfer_call`中进行跨合约调用前应检查预付Gas。

```rust
// https://github.com/near/near-sdk-rs/blob/770cbce018a1b6c49d58276a075ace3da96d6dc1/near-contract-standards/src/fungible_token/core_impl.rs#L136
fn ft_transfer_call(
    &mut self,
    receiver_id: AccountId,
    amount: U128,
    memo: Option<String>,
    msg: String,
) -> PromiseOrValue<U128> {
    require!(env::prepaid_gas() > GAS_FOR_FT_TRANSFER_CALL, "需要更多的Gas");
    // ...
}
```
