## 缺乏存储扩展的检查

### 配置

* 检测器 ID： `storage-gas`
* 严重性：低

### 描述

每次状态增长时，都应确保有足够的余额来覆盖扩展。

### 示例代码

在下面的代码中，插入到 `self.banks` 后，存储使用量会扩展，应检查差值，以确保调用者附加的存储费足够。

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