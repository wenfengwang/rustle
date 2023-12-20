
## 先除法后乘法

### 配置

* 检测器ID：div-before-mul
* 严重等级：中等

### 描述

像3 / 2 * 6 == 6这样的表达式，先进行除法再进行乘法，其结果与3 * 6 / 2 == 9不同，可能会导致精度丢失。

建议进行运算时先乘法后除法。

### 示例代码

以下是一个示例。表达式farm.amount / (farm.end_date - farm.start_date)转换为u128时会向下取整，可能会导致精度丢失。

```rust
// https://github.com/linear-protocol/LiNEAR/blob/fdbacc68c98205cba9f42c130d464ab3114257b6/contracts/linear/src/farm.rs#L125
let reward_per_session =
    farm.amount / (farm.end_date - farm.start_date) as u128 * SESSION_INTERVAL as u128;
```

推荐在进行乘法之后再进行除法，以此减少精度损失：

```rust
let reward_per_session =
    farm.amount * SESSION_INTERVAL as u128 / (farm.end_date - farm.start_date) as u128;
```
