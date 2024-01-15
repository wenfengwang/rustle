## 缺少对存储扩展的检查

### 配置

* 探测器ID：`storage-gas`
* 严重性：低

### 描述

每次状态增长时，都应确保有足够的余额来覆盖扩张。

### 示例代码

在以下代码中，存储使用量在插入到 `self.banks` 之后会增加，应检查这一差异，以确保调用者附加的存储费用足够。

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