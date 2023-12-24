## 回调函数缺少`#[private]`宏

### 配置

* 检测器 ID: `non-private-callback`
* 严重性: 高

### 描述

回调函数应该使用`#[private]`修饰，以确保只有合约本身才能调用。

没有这个宏，任何人都可以调用回调函数，这与最初的设计相违背。

### 示例代码

```rust
pub fn callback_stake(&mut self) { // 这是一个回调函数
    // ...
}
```

函数 `callback_stake` 应该被标记为`#[private]`：

```rust
#[private]
pub fn callback_stake(&mut self) { // 这是一个回调函数
    // ...
}
```

有了这个宏，只有合约本身才能调用`callback_stake`。