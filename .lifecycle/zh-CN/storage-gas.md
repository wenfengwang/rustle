
## 存储扩展检查不足

### 配置信息

* 探测器编号：storage-gas
* 严重等级：低

### 描述

每当系统状态发生增长时，都需要确保有充足的余额来支付扩展费用。

### 示例代码

在以下代码片段中，向self.banks中插入数据后，存储使用量将会增加。因此，需要检查两者之间的差异，以确保调用者支付的存储费用是否充足。

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
