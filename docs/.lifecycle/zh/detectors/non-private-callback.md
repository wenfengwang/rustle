## 回调函数中缺少 `#[private]` 宏

### 配置

* 检测器 ID：`non-private-callback`
* 严重性：高

### 描述

回调函数应该用 `#[private]` 宏修饰，以确保它只能被合约本身调用。

没有这个宏，任何人都能调用回调函数，这违背了原始设计意图。

### 示例代码

```rust
pub fn callback_stake(&mut self) { // 这是一个回调函数
    // ...
}
```

函数 `callback_stake` 应该用 `#[private]` 宏修饰：

```rust
#[private]
pub fn callback_stake(&mut self) { // 这是一个回调函数
    // ...
}
```

有了这个宏，只有合约本身才能调用 `callback_stake`。
