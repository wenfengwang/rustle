
## 先除法后乘法

### 配置

* 检测器 ID：`div-before-mul`
* 严重程度：中等

### 描述

找出像 `3 / 2 * 6 == 6` 这样的先除法后乘法情况，与 `3 * 6 / 2 == 9` 相比，其结果不同。这可能会导致精度损失。

建议进行乘法前先进行除法。

### 示例代码

下面展示了一个例子。公式 `farm.amount / (farm.end_date - farm.start_date) as u128` 会被向下取整，可能导致精度损失。

```rust
// https://github.com/linear-protocol/LiNEAR/blob/fdbacc68c98205cba9f42c130d464ab3114257b6/contracts/linear/src/farm.rs#L125
let reward_per_session =
    farm.amount / (farm.end_date - farm.start_date) as u128 * SESSION_INTERVAL as u128;
```

推荐使用乘法后再除法以减少精度损失：

```rust
let reward_per_session =
    farm.amount * SESSION_INTERVAL as u128 / (farm.end_date - farm.start_date) as u128;
```