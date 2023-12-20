
## 跨合约调用

### 配置

* 检测器ID：ext-call
* 严重级别：信息

### 描述

查找所有跨合约调用。

我们提供这个检测器，以帮助用户快速定位所有跨合约调用，以便进行进一步的分析。

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
        ext_calculator::ext(calculator_account_id).sum(a, b)  // run sum(a, b) on remote
    }
}
```

> 宏 #[ext_contract(...)] 会将Rust特质转换成一个包含静态方法的模块，这使得用户能够执行跨合约调用。这些静态方法接受由特质定义的位置参数，随后是接收者ID（receiver_id）、附加的存款额以及Gas用量，并返回一个新的Promise对象。

在这个示例中，合约可以通过跨合约调用（即，ext_calculator::ext(calculator_account_id).sum(a, b)）来获取a和b的和。
