
## 未指定取整方式时的不恰当舍入

### 配置

* 检测器ID：round
* 严重程度：中

### 描述

查找在算术运算中是否存在使用了未指定舍入方向的取整操作。在DeFi中，如果不明确指定取整方向可能会被利用。更多细节请参考[《如何一次赚取0.000001 BTC成为百万富翁》](https://blog.neodyme.io/posts/lending_disclosure/)(neodyme.io)。

注意：**Rustle**不会上报开发者为特定目的实现的取整函数。

### 示例代码

```rust
let fee = (amount * fee_rate).round();
```

在这个例子中，合约开发者不应使用round函数来计算费用。他们应当使用ceil或者floor函数来明确指定取整的方向。
