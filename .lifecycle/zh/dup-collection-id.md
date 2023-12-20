
## 集合中的重复 id 使用

### 配置

* 检测器 id：`dup-collection-id`
* 严重程度：中等

### 描述

NEAR SDK 中的集合使用 `new` 函数来初始化自身。

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
            users: UnorderedSet::new(StorageKey::Orders), // 这里应该使用 `StorageKey::Users`
        }
    }
}
```

在这个示例中，`orders` 和 `users` 共享了相同的 id，这可能会导致意外的行为。