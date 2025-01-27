
## 查找所有公共接口

### 配置

* 检测器 ID：`public-interface`
* 严重性：info

### 描述

公共接口是可以被其他人调用的函数。具体来说，它们是 `#[near_bindgen]` 结构中没有 `#[private]` 宏的公共函数。

### 示例代码

```rust
#[near_bindgen]
impl Contract {
    pub fn withdraw(&mut self, amount: U128) -> Promise {
        unimplemented!()
    }

    pub fn check_balance(&self) -> U128 {
        unimplemented!()
    }

    #[private]
    pub fn callback_withdraw(&mut self, amount: U128) {
        unimplemented!()
    }

    fn sub_balance(&mut self, amount: u128) {
        unimplemented!()
    }
}
```

在此示例代码中，所有四个函数都是 `#[near_bindgen]` 结构 `Contract` 的方法。但只有 `withdraw` 和 `check_balance` 是公共接口。`callback_withdraw` 是一个用 `#[private]` 修饰的公共函数，因此它是一个内部函数。`sub_balance` 是 `Contract` 的私有函数。
