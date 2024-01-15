## 除法在乘法之前

### 配置

* 检测器 ID： `div-before-mul`
* 严重性：中

### 描述

在乘法之前先进行除法，如 `3 / 2 * 6 == 6`，其结果与 `3 * 6 / 2 == 9` 不同。这可能会导致精度损失。

建议在除法前进行乘法。

### 示例代码

下面展示了一个例子。公式 `farm.amount / (farm.end_date - farm.start_date) as u128` 将会向下取整，这可能会导致精度损失。

```rust
// https://github.com/linear-protocol/LiNEAR/blob/fdbacc68c98205cba9f42c130d464ab3114257b6/contracts/linear/src/farm.rs#L125
let reward_per_session =
    farm.amount / (farm.end_date - farm.start_date) as u128 * SESSION_INTERVAL as u128;
```

建议在乘法后使用除法来减少精度损失：

```rust
let reward_per_session =
    farm.amount * SESSION_INTERVAL as u128 / (farm.end_date - farm.start_date) as u128;
```