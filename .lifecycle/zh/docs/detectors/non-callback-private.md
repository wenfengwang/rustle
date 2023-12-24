## 非回调函数中不当使用 `#[private]`

### 配置

* 检测器 ID: `non-callback-private`
* 严重性: 低

### 描述

宏 `#[private]` 通常用于回调函数中，以确保 `current_account_id` 等于 `predecessor_account_id`。它不应该在非回调函数中使用，否则公共函数将变成内部函数。

### 示例代码

```rust
#[near_bindgen]
impl Pool {
    #[private]
    pub fn get_tokens(&self) -> &[AccountId] {
        &self.token_account_ids
    }
}
```

`get_tokens` 应该是一个公共接口（一个没有 `#[private]` 宏修饰的公共函数），供每个人检查池中的所有令牌类型。不应该用 `#[private]` 装饰。