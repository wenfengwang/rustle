
## 在非回调函数中不当使用#[private]

### 配置

* 检测器ID：非回调-私有
* 严重性：低

### 描述

通常，宏#[private]用于回调函数中，以确保current_account_id与predecessor_account_id相等。它不应被用于非回调函数。否则，原本的公共函数将变成内部函数。

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

get_tokens应当是一个公共接口（一个未用#[private]宏装饰的公共函数），以便所有人能够查询池中的所有代币类型。它不应被#[private]修饰。
