## 乘法前的除法

### 配置

* 检测器 ID： `div-before-mul`
* 严重性：中等

### 描述

查找类似 `3 / 2 * 6 == 6` 这样的乘法前有除法的情况，与 `3 * 6 / 2 == 9` 相比，结果不同。这可能会导致精度损失。

建议先进行乘法，再进行除法。

### 示例代码

以下是一个示例。 公式 `farm.amount / (farm.end_date - farm.start_date) as u128` 将被取整，可能导致精度损失。

```rust
// https://github.com/linear-protocol/LiNEAR/blob/fdbacc68c98205cba9f42c130d464ab3114257b6/contracts/linear/src/farm.rs#L125
let reward_per_session =
    farm.amount / (farm.end_date - farm.start_date) as u128 * SESSION_INTERVAL as u128;
```

建议在乘法后使用除法，以减少精度损失：

```rust
let reward_per_session =
    farm.amount * SESSION_INTERVAL as u128 / (farm.end_date - farm.start_date) as u128;
```