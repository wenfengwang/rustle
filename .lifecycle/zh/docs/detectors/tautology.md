## 在分支条件中使用同义反复（重言式）

### 配置

* 检测器 ID： `tautology`
* 严重性：低

### 描述

找到简单的重言式（条件中涉及`true`或`false`），这使得分支具有确定性。

### 示例代码

```rust
let ok: bool = check_state();
if true || ok {
    // ...
} else {
    // ...
}
```

在这个演示中，`else` 分支内的代码永远不会被执行。这是因为 `true || ok` 是个恒真式。