
## 先除法后乘法

### 配置

* 检测器 ID：`div-before-mul`
* 严重程度：中等

### 描述

如 `3 / 2 * 6 == 6`，先进行除法再进行乘法，其结果与 `3 * 6 / 2 == 9` 不同。这可能导致精度损失。

建议先进行乘法再进行除法。

### 示例代码

下面的示例展示了一个公式 `farm.amount / (farm.end_date - farm.start_date) as u128`，该公式的结果会向下取整，可能导致精度损失。

```rust
// https://github.com/linear-protocol/LiNEAR/blob/fdbacc68c98205cba9f42c130d464ab3114257b6/contracts/linear/src/farm.rs#L125
let reward_per_session =
    farm.amount / (farm.end_date - farm.start_date) as u128 * SESSION_INTERVAL as u128;
```

为了减少精度损失，建议使用乘法后跟除法：

```rust
let reward_per_session =
    farm.amount * SESSION_INTERVAL as u128 / (farm.end_date - farm.start_date) as u128;
```