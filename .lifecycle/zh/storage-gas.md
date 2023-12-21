
## 缺乏对存储扩展的检查

### 配置

* 探测器 ID：`storage-gas`
* 严重程度：低

### 描述

每次状态增长时，都应确保有足够的余额（Balance）来覆盖扩展。

### 示例代码

在以下代码中，向 `self.banks` 插入数据后存储使用量会增加，应检查差额以确保调用者附加的存储费用足够。

```rust
let prev_storage = env::storage_usage();

self.banks.insert(&Bank {
    owner: bank.owner,
    balance: bank.balance.0,
});

assert!(
    env::attached_deposit() > ((env::storage_usage() - prev_storage) as u128 * env::storage_byte_cost()),
    "存储费用不足"
);
```
