## 分支条件中的重言式使用

### 配置

* 检测器 ID： `tautology`
* 严重性：低

### 描述

查找简单的重言式（条件中涉及 `true` 或 `false`），这会导致分支的结果是确定的。

### 示例代码

```rust
let ok: bool = check_state();
if true || ok {
    // ...
} else {
    // ...
}
```

在这个示例中，`else` 分支内的代码将永远不会被执行。这是因为 `true || ok` 构成了一个重言式。
