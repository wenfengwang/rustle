
## 在不检查溢出的情况下进行不安全的数学运算

### 配置信息

* 检测器标识：不安全-数学
* 严重等级：高

### 描述

为所有算术操作启用溢出检查。否则，可能会发生溢出，从而导致结果不正确。

在NEAR合约中，可以采用两种不同的方法来实现溢出检查。

1. \[推荐\] 在Cargo配置文件中开启溢出检查。这样的话，使用+、-和*进行算术运算是安全的。
2. 使用安全数学函数（比如，checked_xxx()）来执行算术运算。

### 示例代码

在这个例子中，由于Cargo配置文件中关闭了溢出检查标志，使用+运算可能会引发溢出。

```toml
[profile.xxx]  # `xxx` equals `dev` or `release`
overflow-checks = false
```

```rust
let a = b + c;
```

建议在overflow-checks设为false时，使用以下代码来进行加法操作。

```rust
let a = b.checked_add(c);
```
