
## 使用不正确的 json 类型

### 配置

* 检测器 ID：`incorrect-json-type`
* 严重程度：高

### 描述

不要在公共接口（在 `#[near_bindgen]` 结构体中没有 `#[private]` 宏的公共函数）中使用 `i64`、`i128`、`u64` 或 `u128` 类型作为参数或返回值。

这是因为 json 能支持的最大整数是 2\^53-1。

查看[更多详细信息](https://2ality.com/2012/04/number-encoding.html)。

推荐开发者使用 Near SDK 中的 `I64`、`I128`、`U64`、`U128` 类型。

### 示例代码

```rust
// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/views.rs#L15
pub struct ContractMetadata {
    pub version: String,
    pub owner: AccountId,
    pub guardians: Vec<AccountId>,
    pub pool_count: u64,  // 应使用 `U64`
    pub state: RunningState,
    pub exchange_fee: u32,
    pub referral_fee: u32,
}

// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/views.rs#L171
#[near_bindgen]
impl Contract {
    pub fn metadata(&self) -> ContractMetadata {  // 返回类型中的 `u64`
        // ...
    }
}
```

在这个示例中，`metadata` 函数使用了包含 `pool_count: u64` 的 `ContractMetadata` 结构体作为其返回值。由于公共函数的返回值通过 json 发送回前端，`pool_count` 的值可能会超过 2\^53-1。因此，应使用 Near SDK 中的字符串类型 `U64`。
