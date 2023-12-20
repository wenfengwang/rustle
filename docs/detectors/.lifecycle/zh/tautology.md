
## 在分支条件中使用重复逻辑

### 配置

* 检测器 id：`tautology`
* 严重程度：低

### 描述

查找简单的重复逻辑（条件中包含 `true` 或 `false`），这会使得分支的结果变得确定。

### 示例代码

```rust
let ok: bool = check_state();
if true || ok {
    // ...
} else {
    // ...
}
```

在这个示例中，`else` 分支内的代码永远不会被执行。这是因为 `true || ok` 构成了一个重复逻辑。