## 集合中使用重复的 ID

### 配置

* 检测器 ID： `dup-collection-id`
* 严重性：中等

### 描述

NEAR SDK 中的集合使用函数 `new` 来初始化自身。

```rust
pub fn new<S>(prefix: S) -> Self
where
    S: IntoStorageKey,
```

参数 `prefix` 是集合的标识符。每个集合的 ID 都应该与其他集合的 ID 不同。

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
            users: UnorderedSet::new(StorageKey::Users), // 这里应该使用 `StorageKey::Users`
        }
    }
}
```

在此示例中，`orders` 和 `users` 共享相同的 ID，这可能会导致意外行为。