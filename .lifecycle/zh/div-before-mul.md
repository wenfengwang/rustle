
## 先除后乘

### 配置

* 检测器 ID：`div-before-mul`
* 严重程度：中等

### 描述

如 `3 / 2 * 6 == 6` 这样的先除后乘操作，与 `3 * 6 / 2 == 9` 的结果不同，可能会导致精度损失。

建议进行乘法操作后再执行除法。

### 示例代码

以下是一个示例。表达式 `farm.amount / (farm.end_date - farm.start_date) as u128` 会向下取整，可能导致精度损失。

```rust
// https://github.com/linear-protocol/LiNEAR/blob/fdbacc68c98205cba9f42c130d464ab3114257b6/contracts/linear/src/farm.rs#L125
let reward_per_session =
    farm.amount / (farm.end_date - farm.start_date) as u128 * SESSION_INTERVAL as u128;
```

建议使用乘法后再进行除法，以减少精度损失：

```rust
let reward_per_session =
    farm.amount * SESSION_INTERVAL as u128 / (farm.end_date - farm.start_date) as u128;
```
