
## void 以外の関数の未使用戻り値

### Configuration

* detector id: `unused-ret`
* severity: low

### Description

関数の戻り値は使用されるべきです。そうでない場合、情報が失われたり、チェックされないことがあります。

### サンプルコード

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
            // セットから値を削除します。セットに値が存在していたかどうかを返します。
            self.guardians.remove(guardian.as_ref());
        }
    }
}
```

このサンプルでは、コントラクトは `remove` の戻り値をチェックして `guardian` が `self.guardians` に存在するかどうかを確認していません。`guardian` が存在しない場合、プログラムはパニックにならず、予期せぬ影響を及ぼす可能性があります。

修正されたバージョンの例は以下の通りです：

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

このバージョンでは、`remove_guardians` は `self.guardians` に含まれていない全ての `guardians` のベクトルを返します。
