
## 非void函数的返回值未被使用

### 配置

* 检测器ID：unused-ret
* 严重性：低

### 描述

应当使用函数的返回值。否则，可能会丢失某些信息或遗漏检查。

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
            // Removes a value from the set. Returns whether the value was present in the set.
            self.guardians.remove(guardian.as_ref());
        }
    }
}
```

在这个示例中，合约没有检查 remove 函数的返回值以确认监护人是否存在于 self.guardians 中。如果监护人不存在，程序将不会产生panic，这可能导致意外的后果。

一个可能的修正版本如下所示：

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

在这个版本中，remove_guardians 函数将返回一个包含所有不在 self.guardians 中的监护人的向量。
