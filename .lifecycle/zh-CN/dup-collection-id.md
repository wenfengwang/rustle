
## 集合中的重复 ID 使用

### 配置

* 检测器编号：dup-collection-id
* 严重性：中

### 描述

NEAR SDK 中的集合通过 new 函数进行初始化。

```rust
pub fn new<S>(prefix: S) -> Self
where
    S: IntoStorageKey,
```

参数 prefix 是集合的唯一标识符。每个集合的 ID 都应该与其他集合的 ID 不同。

### 示例代码

```rust
#[near_bindgen]
#[derive(BorshDeserialize, BorshSerialize)]
pub struct Contract {
    orders: UnorderedMap<u16, Order>,
    users: UnorderedSet<AccountId>,
}

#[near_bindgen]
impl Contract {
    #[init]
    pub fn new() -> Self {
        Self {
            orders: UnorderedMap::new(StorageKey::Orders),
            users: UnorderedSet::new(StorageKey::Orders), // Should use `StorageKey::Users` here
        }
    }
}
```

在这个示例中，订单和用户使用了相同的 ID，这可能导致意外的行为。
