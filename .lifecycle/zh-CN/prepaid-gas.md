
## ft_transfer_call 中缺少对预付燃料的检查

### 配置信息

* 检测器编号：prepaid-gas
* 严重级别：低

### 描述

在执行 ft_transfer_call 时，合约应在发起跨合约调用之前，检查预付的燃料是否足够完成 ft_on_transfer 和 ft_resolve_transfer。

### 示例代码

此示例取自 [near-contract-standards](https://github.com/near/near-sdk-rs/tree/master/near-contract-standards)，在 `ft_transfer_call` 中执行跨合约调用之前，应先验证预付燃料是否充足。

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
