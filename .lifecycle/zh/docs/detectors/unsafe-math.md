## 不安全的数学运算，未进行溢出检查

### 配置

* 检测器 ID： `unsafe-math`
* 严重性：高

### 描述

为所有算术运算启用溢出检查。否则，可能会发生溢出，从而导致不正确的结果。

NEAR 合约中的溢出检查可以使用两种不同的方法来实现。

1. [推荐] 在 Cargo 清单中开启 `overflow-checks` 功能。在这种情况下，可以使用 `+`、`-` 和 `*` 进行算术运算。
2. 使用安全的数学函数（例如，`checked_xxx()`）来进行算术运算。

### 示例代码

在这个例子中，由于在 Cargo 清单中关闭了 `overflow-checks` 标志，使用 `+` 可能会导致溢出。

```toml
[profile.xxx]  # `xxx` equals `dev` or `release`
overflow-checks = false
```

```rust
let a = b + c;
```

推荐使用以下代码进行加法运算，设置 `overflow-checks=false`

```rust
let a = b.checked_add(c);
```