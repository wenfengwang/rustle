## 缺乏检查存储扩容的机制

### 配置

* 检测器 ID： `storage-gas`
* 严重性：低

### 描述

每次状态增长时，都应确保有足够的 Balance 来覆盖扩容。

### 示例代码

在以下代码中，`self.banks` 插入操作后存储使用量增加，应检查增加的差值，以确保调用者附加的存储费用是否足够。

```rust
let prev_storage = env::storage_usage();

self.banks.insert(&Bank {
    owner: bank.owner,
    balance: bank.balance.0,
});

assert!(
    env::attached_deposit() > ((env::storage_usage() - prev_storage) as u128 * env::storage_byte_cost()),
    "存储 gas 不足"
);
```
