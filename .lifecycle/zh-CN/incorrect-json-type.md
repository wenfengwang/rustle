
## 使用不正确的 JSON 类型

### 配置信息

* 检测器 ID：incorrect-json-type
* 严重等级：高

### 描述

请勿在公共接口（位于 #[near_bindgen] 结构体中，且未使用 #[private] 宏的公共函数）中使用 i64、i128、u64 或 u128 类型作为参数或返回值。

这是因为 JSON 能支持的最大整数仅为 2^53-1。

欲了解更多详情，请查阅[相关文档](https://2ality.com/2012/04/number-encoding.html)。

建议开发者在 Near SDK 中使用 I64、I128、U64、U128 类型。

### 示例代码

```rust
// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/views.rs#L15
pub struct ContractMetadata {
    pub version: String,
    pub owner: AccountId,
    pub guardians: Vec<AccountId>,
    pub pool_count: u64,  // should use `U64`
    pub state: RunningState,
    pub exchange_fee: u32,
    pub referral_fee: u32,
}

// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/views.rs#L171
#[near_bindgen]
impl Contract {
    pub fn metadata(&self) -> ContractMetadata {  // `u64` in return type
        // ...
    }
}
```

在这个示例中，元数据通过使用结构体 ContractMetadata 返回了包含 pool_count: u64 的数据。考虑到公共函数的返回值通过 JSON 发送至前端，并且 pool_count 的值可能超出 2^53-1，因此应当使用 Near SDK 提供的字符串类型 U64。
