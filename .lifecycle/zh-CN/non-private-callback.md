
## 回调函数中应包含 #[private] 宏

### 配置

* 检测器标识：non-private-callback
* 严重等级：高

### 描述

为了确保回调函数仅能被合约本身调用，它应当被 #[private] 宏修饰。

缺少该宏，任何人都可能调用回调函数，这与原始设计相悖。

### 示例代码

```rust
pub fn callback_stake(&mut self) { // this is a callback function
    // ...
}
```

回调函数 callback_stake 应当添加 #[private] 宏修饰：

```rust
#[private]
pub fn callback_stake(&mut self) { // this is a callback function
    // ...
}
```

有了这个宏，只有合约本身才能够调用 callback_stake 函数。
