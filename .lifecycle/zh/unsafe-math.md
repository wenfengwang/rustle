
## 未经溢出检查的不安全数学运算

### 配置

* 检测器 ID：`unsafe-math`
* 严重程度：高

### 描述

为所有算术运算启用溢出检查。否则，可能会发生溢出，导致结果不正确。

在 NEAR 合约中，可以用两种不同的方法实现溢出检查。

1. \[推荐\] 在 Cargo 清单中开启 `overflow-checks`。在这种情况下，使用 `+`、`-` 和 `*` 进行算术运算是可以的。
2. 使用安全数学函数（例如，`checked_xxx()`）来进行算术运算。

### 示例代码

在此示例中，由于 Cargo 清单中关闭了 `overflow-checks` 标志，使用 `+` 可能会导致溢出。

```toml
[profile.xxx]  # `xxx` 等于 `dev` 或 `release`
overflow-checks = false
```

```rust
let a = b + c;
```

以下代码建议在 `overflow-checks=false` 的情况下进行加法操作

```rust
let a = b.checked_add(c);
```
