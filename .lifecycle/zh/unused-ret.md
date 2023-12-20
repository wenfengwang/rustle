
## 非 void 函数的未使用返回值

### 配置

* 检测器 ID：`unused-ret`
* 严重程度：低

### 描述

应该使用函数的返回值。否则，可能会丢失某些信息或未经检查。

### 示例代码

```rust
// https://github.com/ref-finance/ref-contracts/blob/117b044280053661fda217057560c8e35111856f/ref-exchange/src/lib.rs#L98
#[near_bindgen]
#[derive(BorshSerialize, BorshDeserialize, PanicOnDefault)]
pub struct Contract {
    // ...
    guardians: UnorderedSet<AccountId>,
    // ...
}

// https://github.com/ref-finance/ref-contracts/blob/536a60c842e018a535b478c874c747bde82390dd/ref-exchange/src/owner.rs#L65
#[near_bindgen]
impl Contract {
    #[payable]
    pub fn remove_guardians(&mut self, guardians: Vec<ValidAccountId>) {
        assert_one_yocto();
        self.assert_owner();
        for guardian in guardians {
            // pub fn remove(&mut self, element: &T) -> bool
            // 从集合中移除一个值。返回该值是否存在于集合中。
            self.guardians.remove(guardian.as_ref());
        }
    }
}
```

在此示例中，合约没有检查 `remove` 的返回值以确保 `guardian` 存在于 `self.guardians` 中。如果 `guardian` 不存在，程序不会产生panic，这可能会带来意想不到的影响。

一个可能的修正版本如下：

```rust
#[payable]
pub fn remove_guardians(&mut self, guardians: Vec<ValidAccountId>) -> Vec<ValidAccountId> {
    assert_one_yocto();
    self.assert_owner();
    let mut guardians_left = vec![];
    for guardian in guardians {
        if !self.guardians.remove(guardian.as_ref()) {
            guardians_left.push(guardian);
        }
    }
    guardians_left
}
```

在这个版本中，`remove_guardians` 将返回所有不在 `self.guardians` 中的 `guardians` 的向量。