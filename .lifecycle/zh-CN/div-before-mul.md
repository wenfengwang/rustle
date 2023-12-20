
## 先乘后除

### 配置

* 检测器编号：div-before-mul
* 严重性：中等

### 描述

如3 / 2 * 6 == 6所示，先进行除法再进行乘法会导致与3 * 6 / 2 == 9的结果不同，这可能会引起精度上的损失。

建议先进行乘法后进行除法。

### 示例代码

以下示例展示了问题所在。表达式 farm.amount / (farm.end_date - farm.start_date) as u128 会向下取整，可能会造成精度损失。

```rust
// https://github.com/linear-protocol/LiNEAR/blob/fdbacc68c98205cba9f42c130d464ab3114257b6/contracts/linear/src/farm.rs#L125
let reward_per_session =
    farm.amount / (farm.end_date - farm.start_date) as u128 * SESSION_INTERVAL as u128;
```

推荐先进行乘法再进行除法，以减少精度损失：

```rust
let reward_per_session =
    farm.amount * SESSION_INTERVAL as u128 / (farm.end_date - farm.start_date) as u128;
```
