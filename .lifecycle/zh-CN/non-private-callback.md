
## 回调函数中缺少 #[private] 宏

### 配置：

* 检测器ID：non-private-callback
* 严重性：高

### 描述：

回调函数应当使用 #[private] 进行修饰，以确保只有合约本身能够调用它。

若无此宏，任何人都能够调用回调函数，这与原始设计相悖。

### 示例代码：

```rust
pub fn callback_stake(&mut self) { // this is a callback function
    // ...
}
```

函数 callback_stake 应当被 #[private] 修饰：

```rust
#[private]
pub fn callback_stake(&mut self) { // this is a callback function
    // ...
}
```

有了这个宏，仅有合约本身能够调用 callback_stake。
