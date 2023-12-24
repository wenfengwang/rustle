## 跨合约调用

### 配置

* 检测器 ID： `ext-call`
* 严重性：信息

### 描述

查找所有跨合约调用。

我们提供此检测器，以帮助用户快速定位所有跨合约调用，以便进行进一步分析。

### 示例代码

```rust
// https://docs.near.org/sdk/rust/cross-contract/callbacks#calculator-example
#[ext_contract(ext_calculator)]
trait Calculator {
    fn sum(&self, a: U128, b: U128) -> U128;
}

#[near_bindgen]
impl Contract {
    pub fn sum_a_b(&mut self, a: U128, b: U128) -> Promise {
        let calculator_account_id: AccountId = "calc.near".parse().unwrap();
        ext_calculator::ext(calculator_account_id).sum(a, b)  // 在远程运行 sum(a, b)
    }
}
```

> 宏 `#[ext_contract(...)]` 将 Rust 特征转换为具有静态方法的模块，允许用户进行跨合约调用。这些静态方法接受由 Trait 定义的位置参数，然后是 `receiver_id`、附加存款和 gas 量，并返回一个新的 `Promise`。

在此示例中，合约可以通过跨合约调用（即 `ext_calculator::ext(calculator_account_id).sum(a, b)`）获取 `a` 和 `b` 的总和。