
## 回调函数中缺少 `#[private]` 宏

### 配置

* 检测器 ID：`non-private-callback`
* 严重程度：高

### 描述

回调函数应该用 `#[private]` 修饰，以确保它只能由合约本身调用。

如果没有这个宏，任何人都可以调用回调函数，这违背了最初的设计。

### 示例代码

```rust
pub fn callback_stake(&mut self) { // 这是一个回调函数
    // ...
}
```

函数 `callback_stake` 应该用 `#[private]` 修饰：

```rust
#[private]
pub fn callback_stake(&mut self) { // 这是一个回调函数
    // ...
}
```

有了这个宏，只有合约本身才能调用 `callback_stake`。
