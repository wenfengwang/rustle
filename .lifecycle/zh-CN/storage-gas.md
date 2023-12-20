
## 存储扩展检查不足

### 配置信息

* 检测器编号：storage-gas
* 严重级别：低

### 描述

每次状态扩大时，都应确保有充足的余额来支付扩容费用。

### 示例代码

在以下代码中，向self.banks插入数据后，存储使用量会增加，应检查这一差额，以确保调用者支付的存储费用是否充足。

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
