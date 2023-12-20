
## 存储扩展检查不足

### 配置信息

* 检测器编号：storage-gas
* 严重性：低

### 描述

每次状态增长时，都应确保有足够的余额来支付扩展费用。

### 示例代码

在以下代码中，向self.banks插入数据后会增加存储使用量，应检查增量以确保调用方支付的存储费用是否充足。

```rust
let prev_storage = env::storage_usage();

self.banks.insert(&Bank {
    owner: bank.owner,
    balance: bank.balance.0,
});

assert!(
    env::attached_deposit() > ((env::storage_usage() - prev_storage) as u128 * env::storage_byte_cost()),
    "insufficient storage gas"
);
```
