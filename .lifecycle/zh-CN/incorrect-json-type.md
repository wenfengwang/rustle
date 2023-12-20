
## 使用不正确的 JSON 类型

### 配置项

* 检测器ID：incorrect-json-type
* 严重级别：高

### 描述

请勿在公共接口（#[near_bindgen] 结构体中未使用 #[private] 宏的公共函数）中使用 i64、i128、u64 或 u128 类型作为参数或返回值。

这是因为 JSON 支持的最大整数值为 2^53-1。

查阅[更多详情](https://2ality.com/2012/04/number-encoding.html)。

推荐开发者在 Near SDK 中使用 I64、I128、U64、U128 类型。

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

在这个示例中，元数据使用了包含 pool_count: u64 返回值的 struct ContractMetadata。由于公共函数的返回值通过 JSON 发送至前端，而 pool_count 的值可能会超出 2^53-1，因此应使用 Near SDK 中的字符串类型 U64。
