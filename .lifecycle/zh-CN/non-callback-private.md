
## 在非回调函数中不当使用#[private]

### 配置

* 检测器标识：非回调-私有
* 严重程度：低

### 描述

通常，宏#[private]被用于回调函数中，以确保current_account_id与predecessor_account_id相等。它不应该被用在非回调函数中。否则，一个原本是公开的函数就会变成内部函数。

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

get_tokens应该是一个公共接口（一个未用#[private]宏装饰的公共函数），以便所有人可以查询池中的所有代币类型。它不应该被#[private]宏修饰。
