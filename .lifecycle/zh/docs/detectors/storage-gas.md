## 存储扩展的缺乏检查

### 配置

* 检测器 ID： `storage-gas`
* 严重性：低

### 描述

每次状态增长时，都应确保有足够的余额来覆盖扩展。

### 示例代码

在下面的代码中，在向 `self.banks` 插入数据后，存储使用量会扩展，应当检查差额，以确保调用者附加的存储费足够。

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