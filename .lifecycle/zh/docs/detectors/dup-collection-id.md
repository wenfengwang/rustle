## 集合中使用了重复的 id

### 配置

* 检测器 ID： `dup-collection-id`
* 严重性：中

### 描述

NEAR SDK 中的集合使用函数 `new` 来初始化自身。

```rust
pub fn new<S>(prefix: S) -> Self
where
    S: IntoStorageKey,
```

参数 `prefix` 是集合的标识符。每个集合都应该有一个与其他集合不同的 id。

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

在此示例中，`orders` 和 `users` 共享相同的 id，这可能会导致意外行为。