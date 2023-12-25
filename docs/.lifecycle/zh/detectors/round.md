## 未指定 ceil 或 floor 的不当四舍五入

### 配置

* 检测器 ID： `round`
* 严重性：中等

### 描述

查找算术运算中是否使用了四舍五入。在DeFi中，未指定方向的四舍五入可能会被利用。有关详细信息，请参阅 [如何成为百万富翁，一次 0.000001 BTC (neodyme.io)](https://blog.neodyme.io/posts/lending_disclosure/)。

注意：**Rustle** 不会报告开发人员为特定目的实现的四舍五入函数。

### 示例代码

```rust
let fee = (amount * fee_rate).round();
```

在此示例中，合约开发人员不应使用 `round` 来计算费用。相反，他们应该使用 `ceil` 或 `floor` 来指定四舍五入的方向。
